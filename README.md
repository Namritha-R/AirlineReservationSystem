
Airline Reservation System (C Project)

This is a simple terminal-based airline reservation system written in C. It lets users book flight tickets by entering the source and destination, view a seat map, and save booking history to a file. There's also an admin mode to manage flights and passengers.


Features

- Book flights by source & destination
- Graphical seat map showing available/booked seats
- Admin mode to add/remove flights and view passengers
- Ticket details printed in the terminal
- Booking history saved to `bookings.txt`
- Data saved using file I/O (no database)


Getting Started

1. Compile:
gcc airline_route_booking.c -o airline

2. Run:
./airline

3. Admin password: `admin123`


Files Generated

- `flights.dat`: stores flight & seat info
- `bookings.txt`: stores booking history



Ideas to Improve

- Add login system
- Export data to CSV or JSON
- GUI version in future (maybe using C++ or Python)


About

This project was built to practice C programming, especially structs, file handling, and dynamic memory allocation — and to build something close to a real-world application.
