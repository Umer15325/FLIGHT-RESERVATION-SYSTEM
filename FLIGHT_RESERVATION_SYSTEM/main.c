#include <stdio.h>

// STRUCTS
struct Flight {
    int flight_id;
    char source[30];
    char destination[30];
    char date[15];
    char time[10];
    int total_seats;
    int available_seats;
    float price;
};

struct Reservation {
    int reservation_id;
    int flight_id;
    char passenger_name[50];
    int num_seats;
};

// FUNCTION DECLARATIONS
int mainMenu();
void adminMenu();
void userMenu();
void addFlight();
void deleteFlight();
void viewFlights();
void bookTicket();
void cancelTicket();
void viewReservations();
int adminLogin();
int userLogin();

// MAIN FUNCTION
int main() {
    mainMenu();
    return 0;
}

// ADMIN LOGIN 
int adminLogin() {
    int user, pass, choice;

    printf("\n                    .----------------------.\n");
    printf("                    |       LOGIN BOX      |\n");
    printf("                    '----------------------'\n\n");

    printf("                    Enter Admin Username (number): ");
    scanf("%d", &user);

    printf("                    Enter Admin Password (number): ");
    scanf("%d", &pass);

    printf("                    Show password? (1 = Yes, 2 = No): ");
    scanf("%d", &choice);

    if (choice == 1)
        printf("                    You entered password: %d\n", pass);
    else
        printf("                    You entered password: ******\n");

    if (user == 1 && pass == 1234) {
        printf("                    Login Successful!\n");
        return 1;
    } else {
        printf("                    Invalid username or password!\n");
        return 0;
    }
}

// USER LOGIN 
int userLogin() {
    int user, pass, choice;

    printf("\n                    .----------------------.\n");
    printf("                    |       LOGIN BOX      |\n");
    printf("                    '----------------------'\n\n");

    printf("                    Enter User Username (number): ");
    scanf("%d", &user);

    printf("                    Enter User Password (number): ");
    scanf("%d", &pass);

    printf("                    Show password? (1 = Yes, 2 = No): ");
    scanf("%d", &choice);

    if (choice == 1)
        printf("                    You entered password: %d\n", pass);
    else
        printf("                    You entered password: ******\n");

    if (user == 2 && pass == 5678) {
        printf("                    User Login Successful!\n");
        return 1;
    } else {
        printf("                    Invalid username or password!\n");
        return 0;
    }
}

// MAIN MENU
int mainMenu() {
    int choice;

    while (1) {
        printf("\n                    .------------------------------------.\n");
        printf("                    |      FLIGHT RESERVATION SYSTEM      |\n");
        printf("                    '------------------------------------'\n\n");

        printf("                    (1) Admin Login\n");
        printf("                    (2) User Login\n");
        printf("                    (3) Exit\n");
        printf("                    Enter your choice: ");

        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (adminLogin())
                    adminMenu();
                break;

            case 2:
                if (userLogin())
                    userMenu();
                break;

            case 3:
                printf("                    GOODBYE!\n");
                return 0;

            default:
                printf("                    Invalid choice! Try again.\n");
        }
    }
}

// ADMIN MENU
void adminMenu() {
    int choice;

    while (1) {
        printf("\n                    .----------------------.\n");
        printf("                    |      ADMIN MENU      |\n");
        printf("                    '----------------------'\n\n");

        printf("                    (1) Add Flight\n");
        printf("                    (2) Delete Flight\n");
        printf("                    (3) View All Flights\n");
        printf("                    (4) Back to Main Menu\n");
        printf("                    Enter your choice: ");

        scanf("%d", &choice);

        switch (choice) {
            case 1: addFlight(); break;
            case 2: deleteFlight(); break;
            case 3: viewFlights(); break;
            case 4: return;
            default: printf("                    Invalid choice!\n");
        }
    }
}

// USER MENU
void userMenu() {
    int choice;

    while (1) {
        printf("\n                    .----------------------.\n");
        printf("                    |       USER MENU      |\n");
        printf("                    '----------------------'\n\n");

        printf("                    (1) View Flights\n");
        printf("                    (2) Book Ticket\n");
        printf("                    (3) Cancel Ticket\n");
        printf("                    (4) View My Reservations\n");
        printf("                    (5) Back to Main Menu\n");
        printf("                    Enter your choice: ");

        scanf("%d", &choice);

        switch (choice) {
            case 1: viewFlights(); break;
            case 2: bookTicket(); break;
            case 3: cancelTicket(); break;
            case 4: viewReservations(); break;
            case 5: return;
            default: printf("                    Invalid choice!\n");
        }
    }
}

// ADD FLIGHT
void addFlight() {
    struct Flight f;
    FILE* fp = fopen("Flights.txt", "a");

    if (!fp) {
        printf("                    Error opening file!\n");
        return;
    }

    printf("\n                    .----------------------.\n");
    printf("                    |      ADD FLIGHT      |\n");
    printf("                    '----------------------'\n\n");

    printf("                    Enter Flight ID: ");
    scanf("%d", &f.flight_id);
    printf("                    Enter Source: ");
    scanf("%s", f.source);
    printf("                    Enter Destination: ");
    scanf("%s", f.destination);
    printf("                    Enter Date (DD/MM/YYYY): ");
    scanf("%s", f.date);
    printf("                    Enter Time (HH:MM): ");
    scanf("%s", f.time);
    printf("                    Enter Total Seats: ");
    scanf("%d", &f.total_seats);
    printf("                    Enter Ticket Price: ");
    scanf("%f", &f.price);

    f.available_seats = f.total_seats;

    fprintf(fp, "%d,%s,%s,%s,%s,%d,%d,%.2f\n",
            f.flight_id, f.source, f.destination, f.date,
            f.time, f.total_seats, f.available_seats, f.price);

    fclose(fp);

    printf("                    Flight Added Successfully!\n");
}

// DELETE FLIGHT
void deleteFlight() {
    struct Flight flights[100];
    int count = 0, deleteID, found = 0;

    FILE* fp = fopen("Flights.txt", "r");
    if (!fp) {
        printf("                    No flights found!\n");
        return;
    }

    while (fscanf(fp, "%d,%[^,],%[^,],%[^,],%[^,],%d,%d,%f\n",
        &flights[count].flight_id, flights[count].source,
        flights[count].destination, flights[count].date,
        flights[count].time, &flights[count].total_seats,
        &flights[count].available_seats, &flights[count].price) == 8)
    {
        count++;
    }
    fclose(fp);

    printf("\n                    .---------------------------.\n");
    printf("                    |      DELETE A FLIGHT      |\n");
    printf("                    '---------------------------'\n\n");

    printf("                    Enter Flight ID to delete: ");
    scanf("%d", &deleteID);

    for (int i = 0; i < count; i++) {
        if (flights[i].flight_id == deleteID) {
            found = 1;
            for (int j = i; j < count - 1; j++)
                flights[j] = flights[j + 1];
            count--;
            break;
        }
    }

    if (!found) {
        printf("                    Flight ID not found!\n");
        return;
    }

    fp = fopen("Flights.txt", "w");
    for (int i = 0; i < count; i++) {
        fprintf(fp, "%d,%s,%s,%s,%s,%d,%d,%.2f\n",
                flights[i].flight_id, flights[i].source,
                flights[i].destination, flights[i].date,
                flights[i].time, flights[i].total_seats,
                flights[i].available_seats, flights[i].price);
    }
    fclose(fp);

    printf("                    Flight Deleted Successfully!\n");
}

// VIEW FLIGHTS
void viewFlights() {
    struct Flight flight;
    FILE* fp = fopen("Flights.txt", "r");

    if (!fp) {
        printf("                    .----------------------------.\n");
        printf("                    |   NO FLIGHTS AVAILABLE!    |\n");
        printf("                    '----------------------------'\n");
        return;
    }

    printf("\n                    .---------------------------------------------------------------.\n");
    printf("                    |                       AVAILABLE FLIGHTS                       |\n");
    printf("                    '---------------------------------------------------------------'\n\n");

    printf("%-10s %-15s %-15s %-12s %-8s %-10s %-10s %-8s\n",
        "ID", "Source", "Destination", "Date", "Time",
        "Seats", "Available", "Price");
    printf("---------------------------------------------------------------------------------------------\n");

    int count = 0;
    while (fscanf(fp, "%d,%[^,],%[^,],%[^,],%[^,],%d,%d,%f\n",
            &flight.flight_id, flight.source, flight.destination,
            flight.date, flight.time, &flight.total_seats,
            &flight.available_seats, &flight.price) == 8)
    {
        printf("%-10d %-15s %-15s %-12s %-8s %-10d %-10d %-8.2f\n",
               flight.flight_id, flight.source, flight.destination,
               flight.date, flight.time, flight.total_seats,
               flight.available_seats, flight.price);
        count++;
    }

    if (count == 0)
        printf("\nNo flight records found.\n");

    fclose(fp);
}

// BOOK TICKET
void bookTicket() {
    struct Flight flights[100];
    int count = 0;

    FILE* fp = fopen("Flights.txt", "r");
    if (!fp) {
        printf("                    No flights available!\n");
        return;
    }

    while (fscanf(fp, "%d,%[^,],%[^,],%[^,],%[^,],%d,%d,%f\n",
        &flights[count].flight_id, flights[count].source,
        flights[count].destination, flights[count].date,
        flights[count].time, &flights[count].total_seats,
        &flights[count].available_seats, &flights[count].price) == 8)
    {
        count++;
    }
    fclose(fp);

    printf("\n                    .----------------------.\n");
    printf("                    |      BOOK TICKET      |\n");
    printf("                    '----------------------'\n\n");

    int id, seats;
    printf("                    Enter Flight ID to book: ");
    scanf("%d", &id);

    int found = -1;
    for (int i = 0; i < count; i++)
        if (flights[i].flight_id == id)
            found = i;

    if (found == -1) {
        printf("                    Flight not found!\n");
        return;
    }

    printf("                    Available Seats: %d\n", flights[found].available_seats);
    printf("                    How many seats?: ");
    scanf("%d", &seats);

    if (seats <= 0 || seats > flights[found].available_seats) {
        printf("                    Invalid seat number!\n");
        return;
    }

    flights[found].available_seats -= seats;

    char name[50];
    printf("                    Enter Passenger Name: ");
    scanf(" %[^\n]", name);

    int resID = id * 100 + seats;

    FILE* rf = fopen("Reservations.txt", "a");
    fprintf(rf, "%d,%d,%s,%d\n", resID, id, name, seats);
    fclose(rf);

    fp = fopen("Flights.txt", "w");
    for (int i = 0; i < count; i++) {
        fprintf(fp, "%d,%s,%s,%s,%s,%d,%d,%.2f\n",
                flights[i].flight_id, flights[i].source,
                flights[i].destination, flights[i].date,
                flights[i].time, flights[i].total_seats,
                flights[i].available_seats, flights[i].price);
    }
    fclose(fp);

    printf("                    Booking Successful! Reservation ID = %d\n", resID);
}

// CANCEL TICKET
void cancelTicket() {
    struct Reservation reservations[100];
    struct Flight flights[100];
    int resCount = 0, flightCount = 0;
    int cancelResID, foundResIndex = -1, foundFlightIndex = -1;
    int flightID_to_update, seats_to_cancel;

    FILE* fp = fopen("Reservations.txt", "r");
    if (!fp) {
        printf("                    No reservations found!\n");
        return;
    }

    while (fscanf(fp, "%d,%d,%[^,],%d\n",
        &reservations[resCount].reservation_id, 
        &reservations[resCount].flight_id,
        reservations[resCount].passenger_name, 
        &reservations[resCount].num_seats) == 4)
    {
        resCount++;
    }
    fclose(fp);

    printf("\n                    .------------------------.\n");
    printf("                    |      CANCEL TICKET      |\n");
    printf("                    '------------------------'\n\n");

    printf("                    Enter Reservation ID: ");
    scanf("%d", &cancelResID);


    for (int i = 0; i < resCount; i++) {
        if (reservations[i].reservation_id == cancelResID) {
            foundResIndex = i;
            break;
        }
    }

    if (foundResIndex == -1) {
        printf("                    Reservation ID not found!\n");
        return;
    }

    printf("                    You have %d seats reserved.\n", reservations[foundResIndex].num_seats);
    printf("                    How many seats do you want to cancel? ");
    scanf("%d", &seats_to_cancel);


    if (seats_to_cancel <= 0) {
        printf("                    Invalid number of seats!\n");
        return;
    }
    if (seats_to_cancel > reservations[foundResIndex].num_seats) {
        printf("                    You cannot cancel more seats than you booked!\n");
        return;
    }


    flightID_to_update = reservations[foundResIndex].flight_id;

    
    if (seats_to_cancel == reservations[foundResIndex].num_seats) {

        for (int i = foundResIndex; i < resCount - 1; i++) {
            reservations[i] = reservations[i + 1];
        }
        resCount--;
        printf("                    All reservations cancelled.\n");
    } else {

        reservations[foundResIndex].num_seats -= seats_to_cancel;
        printf("                    Reservations cancelled. You still have %d seats.\n", reservations[foundResIndex].num_seats);
    }

    fp = fopen("Reservations.txt", "w");
    for (int i = 0; i < resCount; i++) {
        fprintf(fp, "%d,%d,%s,%d\n",
            reservations[i].reservation_id, 
            reservations[i].flight_id,
            reservations[i].passenger_name, 
            reservations[i].num_seats);
    }
    fclose(fp);


    fp = fopen("Flights.txt", "r");
    if (!fp) {
        printf("                    Error updating flight inventory!\n");
        return;
    }

    while (fscanf(fp, "%d,%[^,],%[^,],%[^,],%[^,],%d,%d,%f\n",
        &flights[flightCount].flight_id, flights[flightCount].source,
        flights[flightCount].destination, flights[flightCount].date,
        flights[flightCount].time, &flights[flightCount].total_seats,
        &flights[flightCount].available_seats, &flights[flightCount].price) == 8)
    {
        flightCount++;
    }
    fclose(fp);

    for (int i = 0; i < flightCount; i++) {
        if (flights[i].flight_id == flightID_to_update) {
            foundFlightIndex = i;
            break;
        }
    }

    if (foundFlightIndex != -1) {
        
        flights[foundFlightIndex].available_seats += seats_to_cancel;

        fp = fopen("Flights.txt", "w");
        for (int i = 0; i < flightCount; i++) {
            fprintf(fp, "%d,%s,%s,%s,%s,%d,%d,%.2f\n",
                    flights[i].flight_id, flights[i].source,
                    flights[i].destination, flights[i].date,
                    flights[i].time, flights[i].total_seats,
                    flights[i].available_seats, flights[i].price);
        }
        fclose(fp);
    }
    
    printf("                    Process Completed Successfully!\n");
}

// VIEW RESERVATIONS
void viewReservations() {
    struct Reservation res;
    FILE* fp = fopen("Reservations.txt", "r");

    if (!fp) {
        printf("                    No reservations found!\n");
        return;
    }

    printf("\n                    .----------------------------.\n");
    printf("                    |      MY RESERVATIONS       |\n");
    printf("                    '----------------------------'\n\n");

    while (fscanf(fp, "%d,%d,%[^,],%d\n",
        &res.reservation_id, &res.flight_id,
        res.passenger_name, &res.num_seats) == 4)
    {
        printf("\n                    Reservation ID: %d\n", res.reservation_id);
        printf("                    Flight ID     : %d\n", res.flight_id);
        printf("                    Passenger Name: %s\n", res.passenger_name);
        printf("                    Seats Booked  : %d\n", res.num_seats);
    }

    fclose(fp);
}