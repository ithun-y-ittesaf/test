# airCLI Lite

A trimmed demo that keeps only users, flights, tickets, and banking. It reuses the original implementations with a smaller menu so you can experiment without the baggage/security/admin layers.

## Layout
- `main.cpp` — entry that wires the CLIs together
- `users/`, `flights/`, `tickets/`, `banking/` — domain logic copied from the full project
- `storage/`, `logging/`, `access/`, `utils/` — shared helpers
- `storage/data/` — sample data copied from the main project

## Build
```
./build.sh
```
Produces `./aircli-lite`. Build script assumes `g++` with C++17.

## Run
```
./aircli-lite
```
Use an existing user from `storage/data/users.txt` (e.g. `admin123/admin123`, `ithun/ithun123`), or sign up anew. Admins get an extra menu item to create flights.
# test
