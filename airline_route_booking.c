
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 50
#define FLIGHT_FILE "flights.dat"
#define BOOKING_FILE "bookings.txt"
#define ADMIN_PASSWORD "admin123"

typedef struct {
    char name[MAX_NAME_LEN];
    int age;
    char gender;
} Passenger;

typedef struct {
    int seatNumber;
    int isBooked;
    Passenger passenger;
} Seat;

typedef struct {
    int flightID;
    char source[30];
    char destination[30];
    char date[15];
    char time[10];
    int totalSeats;
    int isActive;
    Seat* seats;
} Flight;

Flight* flights = NULL;
int flightCount = 0;

// Function declarations
void loadFlights();
void saveFlights();
void adminMenu();
void userMenu();
void addFlight();
void removeFlight();
void viewFlights();
void bookTicketByRoute();
void cancelTicket();
void viewPassengers();
void generateTicket(Flight flight, Seat seat);
void displaySeatMap(Flight *f);
Flight* findFlightByID(int id);

int main() {
    loadFlights();
    int mode;

    while (1) {
        printf("\n========= Airline Reservation System =========\n");
        printf("1. Admin Login\n2. User Mode\n3. Exit\nChoose Mode: ");
        scanf("%d", &mode);

        switch (mode) {
            case 1: {
                char password[20];
                printf("Enter Admin Password: ");
                scanf("%s", password);
                if (strcmp(password, ADMIN_PASSWORD) == 0)
                    adminMenu();
                else
                    printf("Incorrect password!\n");
                break;
            }
            case 2:
                userMenu();
                break;
            case 3:
                saveFlights();
                exit(0);
            default:
                printf("Invalid option.\n");
        }
    }
}

void loadFlights() {
    FILE* file = fopen(FLIGHT_FILE, "rb");
    if (!file) return;
    fread(&flightCount, sizeof(int), 1, file);
    flights = (Flight*)malloc(sizeof(Flight) * flightCount);
    for (int i = 0; i < flightCount; i++) {
        fread(&flights[i], sizeof(Flight) - sizeof(Seat*), 1, file);
        flights[i].seats = (Seat*)malloc(sizeof(Seat) * flights[i].totalSeats);
        fread(flights[i].seats, sizeof(Seat), flights[i].totalSeats, file);
    }
    fclose(file);
}

void saveFlights() {
    FILE* file = fopen(FLIGHT_FILE, "wb");
    if (!file) return;
    fwrite(&flightCount, sizeof(int), 1, file);
    for (int i = 0; i < flightCount; i++) {
        fwrite(&flights[i], sizeof(Flight) - sizeof(Seat*), 1, file);
        fwrite(flights[i].seats, sizeof(Seat), flights[i].totalSeats, file);
    }
    fclose(file);
}

void adminMenu() {
    int choice;
    while (1) {
        printf("\n--- Admin Panel ---\n");
        printf("1. Add Flight\n2. Remove Flight\n3. View All Flights\n4. View Passengers\n5. Back\nChoose: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addFlight(); break;
            case 2: removeFlight(); break;
            case 3: viewFlights(); break;
            case 4: viewPassengers(); break;
            case 5: return;
            default: printf("Invalid choice.\n");
        }
    }
}

void userMenu() {
    int choice;
    while (1) {
        printf("\n--- User Panel ---\n");
        printf("1. View Flights\n2. Book Ticket (by Route)\n3. Cancel Ticket\n4. Back\nChoose: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: viewFlights(); break;
            case 2: bookTicketByRoute(); break;
            case 3: cancelTicket(); break;
            case 4: return;
            default: printf("Invalid choice.\n");
        }
    }
}

void addFlight() {
    flights = (Flight*)realloc(flights, sizeof(Flight) * (flightCount + 1));
    Flight* f = &flights[flightCount];

    printf("Enter Flight ID: ");
    scanf("%d", &f->flightID);
    printf("Source: ");
    scanf("%s", f->source);
    printf("Destination: ");
    scanf("%s", f->destination);
    printf("Date (dd-mm-yyyy): ");
    scanf("%s", f->date);
    printf("Time (e.g., 10:00AM): ");
    scanf("%s", f->time);
    printf("Total Seats (max 100): ");
    scanf("%d", &f->totalSeats);

    f->isActive = 1;
    f->seats = (Seat*)malloc(sizeof(Seat) * f->totalSeats);
    for (int i = 0; i < f->totalSeats; i++) {
        f->seats[i].seatNumber = i + 1;
        f->seats[i].isBooked = 0;
    }

    flightCount++;
    saveFlights();
    printf("Flight added successfully.\n");
}

void removeFlight() {
    int id;
    printf("Enter Flight ID to remove: ");
    scanf("%d", &id);

    Flight *f = findFlightByID(id);
    if (!f || !f->isActive) {
        printf("Flight not found.\n");
        return;
    }

    f->isActive = 0;
    saveFlights();
    printf("Flight removed.\n");
}

void viewFlights() {
    printf("\nAvailable Flights:\n");
    for (int i = 0; i < flightCount; i++) {
        if (flights[i].isActive) {
            printf("ID: %d | %s -> %s | Date: %s | Time: %s | Seats: %d\n",
                   flights[i].flightID, flights[i].source, flights[i].destination,
                   flights[i].date, flights[i].time, flights[i].totalSeats);
        }
    }
}

Flight* findFlightByID(int id) {
    for (int i = 0; i < flightCount; i++) {
        if (flights[i].flightID == id && flights[i].isActive)
            return &flights[i];
    }
    return NULL;
}

void displaySeatMap(Flight *f) {
    printf("\n---- Seat Map (Flight %d: %s to %s) ----\n", f->flightID, f->source, f->destination);
    for (int i = 0; i < f->totalSeats; i++) {
        if (f->seats[i].isBooked)
            printf("[X] ");
        else
            printf("[%2d] ", f->seats[i].seatNumber);

        if ((i + 1) % 3 == 0)
            printf("   ");
        if ((i + 1) % 7 == 0)
            printf("\n");
    }
    printf("\n");
}

void bookTicketByRoute() {
    char src[30], dest[30];
    int matched = 0;

    printf("Enter Source City: ");
    scanf("%s", src);
    printf("Enter Destination City: ");
    scanf("%s", dest);

    Flight* options[10];
    for (int i = 0; i < flightCount; i++) {
        if (flights[i].isActive && strcmp(flights[i].source, src) == 0 && strcmp(flights[i].destination, dest) == 0) {
            options[matched++] = &flights[i];
            printf("[%d] Flight ID: %d | Date: %s | Time: %s\n", matched, flights[i].flightID, flights[i].date, flights[i].time);
        }
    }

    if (matched == 0) {
        printf("No flights found.\n");
        return;
    }

    int choice;
    printf("Select a flight [1-%d]: ", matched);
    scanf("%d", &choice);
    if (choice < 1 || choice > matched) {
        printf("Invalid selection.\n");
        return;
    }

    Flight *f = options[choice - 1];
    int booked = 0;
    for (int i = 0; i < f->totalSeats; i++) if (f->seats[i].isBooked) booked++;
    int remaining = f->totalSeats - booked;

    printf("Total Seats: %d | Booked: %d | Remaining: %d\n", f->totalSeats, booked, remaining);
    if (remaining == 0) {
        printf("No available seats.\n");
        return;
    }

    displaySeatMap(f);
    int seatNo;
    while (1) {
        printf("Enter Seat Number (1-%d): ", f->totalSeats);
        scanf("%d", &seatNo);
        if (seatNo < 1 || seatNo > f->totalSeats || f->seats[seatNo - 1].isBooked) {
            printf("Invalid or booked seat. Try again.\n");
            continue;
        }
        break;
    }

    Passenger p;
    getchar();
    printf("Enter Name: ");
    fgets(p.name, MAX_NAME_LEN, stdin);
    p.name[strcspn(p.name, "\n")] = 0;
    printf("Enter Age: ");
    scanf("%d", &p.age);
    printf("Enter Gender (M/F): ");
    scanf(" %c", &p.gender);

    Seat *s = &f->seats[seatNo - 1];
    s->isBooked = 1;
    s->passenger = p;
    saveFlights();

    FILE *log = fopen(BOOKING_FILE, "a");
    if (log) {
        fprintf(log, "Flight %d (%s -> %s), Date: %s, Time: %s\n", f->flightID, f->source, f->destination, f->date, f->time);
        fprintf(log, "Seat: %d, Passenger: %s, Age: %d, Gender: %c\n\n", seatNo, p.name, p.age, p.gender);
        fclose(log);
    }

    printf("Booking successful!\n");
    generateTicket(*f, *s);
}

void cancelTicket() {
    int id, seatNo;
    printf("Enter Flight ID: ");
    scanf("%d", &id);
    Flight *f = findFlightByID(id);
    if (!f) {
        printf("Flight not found.\n");
        return;
    }

    printf("Enter Seat Number to Cancel: ");
    scanf("%d", &seatNo);
    if (seatNo < 1 || seatNo > f->totalSeats || !f->seats[seatNo - 1].isBooked) {
        printf("Invalid seat.\n");
        return;
    }

    f->seats[seatNo - 1].isBooked = 0;
    saveFlights();
    printf("Booking canceled.\n");
}

void viewPassengers() {
    int id;
    printf("Enter Flight ID: ");
    scanf("%d", &id);
    Flight *f = findFlightByID(id);
    if (!f) {
        printf("Flight not found.\n");
        return;
    }

    printf("Passengers on Flight %d:\n", id);
    for (int i = 0; i < f->totalSeats; i++) {
        if (f->seats[i].isBooked) {
            Passenger *p = &f->seats[i].passenger;
            printf("Seat %d: %s, Age: %d, Gender: %c\n", i + 1, p->name, p->age, p->gender);
        }
    }
}

void generateTicket(Flight f, Seat s) {
    printf("\n========= TICKET =========\n");
    printf("Passenger: %s\n", s.passenger.name);
    printf("Age: %d | Gender: %c\n", s.passenger.age, s.passenger.gender);
    printf("Flight: %d (%s -> %s)\n", f.flightID, f.source, f.destination);
    printf("Date: %s | Time: %s\n", f.date, f.time);
    printf("Seat: %d\n", s.seatNumber);
    printf("==========================\n");
}
