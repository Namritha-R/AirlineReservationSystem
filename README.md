# Airline Reservation System ✈️

A robust, terminal-based airline reservation system built in C. This project simulates a real-world booking environment, allowing users to search and book flights, receive a unique Passenger Name Record (PNR), and securely manage their tickets, while providing an administrative backend for flight management.

## 🌟 Features

### Passenger (User Mode)
- **Search & Book:** Find flights by specifying source and destination cities (supports multi-word city names).
- **Interactive Seat Map:** View a graphical layout of the airplane to select available seats.
- **Secure PNR System:** Receive a unique 6-digit PNR upon booking for secure ticket tracking.
- **Secure Cancellations:** Cancel bookings safely using your unique PNR.
- **Digital Tickets:** Generates and prints a detailed ticket to the terminal.

### Administrator (Admin Mode)
- **Flight Management:** Add new flights or remove inactive ones.
- **Passenger Manifests:** View a complete list of passengers and their details for any active flight.

### Architecture
- **Data Persistence:** All flights and bookings are automatically saved to `flights.dat` via binary serialization.
- **Booking Logs:** A human-readable history of all bookings is appended to `bookings.txt`.
- **Memory Safe:** Uses dynamic memory allocation to manage flights efficiently without arbitrary buffer limits.

## 🚀 Getting Started

### Prerequisites
- A C compiler (e.g., GCC or Clang)

### Compilation
Open your terminal and run:
```bash
gcc airline_route_booking.c -o airline
```

### Execution
Run the compiled executable:
- **Windows:** `.\airline.exe`
- **Linux / macOS:** `./airline`

### Default Credentials
- **Admin Password:** `admin123`

## 📁 Project Structure
- `airline_route_booking.c`: The main source code.
- `flights.dat`: Auto-generated binary file storing flight and seating states.
- `bookings.txt`: Auto-generated text log of all successful reservations.

## 🛠️ Built With
- **C** - The programming language used.
- Standard C Libraries: `<stdio.h>`, `<stdlib.h>`, `<string.h>`, `<time.h>`
