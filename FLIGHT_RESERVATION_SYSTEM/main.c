// HEADER FILES
#include<stdio.h>

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

// MAIN FUNCTION
int main(){
    mainMenu();
    return 0;
}



// PRINTING MAIN MENU
int mainMenu(){
    int choice;

    while (1)
    {
        printf("\n========== FLIGHT RESERVATION SYSTEM ==========\n");
        printf("1. Admin Login\n");
        printf("2. User Login\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: 
                adminMenu(); 
                break;

            case 2: 
                userMenu(); 
                break;

            case 3: 
                printf("\nThank you for using the system!\n");
                printf("Exited...\n"); 
                return 0;

            default: 
                printf("\nInvalid choice! Try again.\n");
        }
    }
}



// PRINTING ADMIN MENU
void adminMenu(){
    int choice;

    while (1)
    {
        printf("\n------ ADMIN MENU ------\n");
        printf("1. Add Flight\n");
        printf("2. Delete Flight\n");
        printf("3. View All Flights\n");
        printf("4. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: 
                addFlight(); 
                break;

            case 2: 
                deleteFlight();
                break;

            case 3: 
                viewFlights();  
                break;

            case 4:
                return;

            default: 
                printf("\nInvalid choice! Try again.\n");
        }
    }
    
}



// PRINTING USER MENU
void userMenu(){
    int choice;

    while (1)
    {
        printf("\n------ USER MENU ------\n");
        printf("1. View Flights\n");
        printf("2. Book Ticket\n");
        printf("3. Cancel Ticket\n");
        printf("4. View My Reservations\n");
        printf("5. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: 
                viewFlights(); 
                break;

            case 2: 
                bookTicket(); 
                break;

            case 3: 
                cancelTicket(); 
                break;

            case 4: 
                viewReservations(); 
                break;

            case 5:
                return;

            default: 
                printf("\nInvalid choice! Try again.\n");
        }

    }
    
}



// ADDING FLIGHT
void addFlight(){
    struct Flight f;

    FILE *fp = fopen("Flights.txt", "a"); // append mode
    if (fp == NULL) {
        printf("Error opening file!");
        return;
    }

    printf("\nEnter Flight ID: ");
    scanf("%d", &f.flight_id);
    printf("Enter Source: ");
    scanf("%s", f.source);
    printf("Enter Destination: ");
    scanf("%s", f.destination);
    printf("Enter Date (DD/MM/YYYY): ");
    scanf("%s", f.date);
    printf("Enter Time (HH:MM): ");
    scanf("%s", f.time);
    printf("Enter Total Seats: ");
    scanf("%d", &f.total_seats);
    f.available_seats = f.total_seats;
    printf("Enter Ticket Price: ");
    scanf("%f", &f.price);

    fprintf(fp, "%d,%s,%s,%s,%s,%d,%d,%.2f\n", f.flight_id, f.source, f.destination, f.date, f.time, f.total_seats,f.available_seats ,f.price);

    fclose(fp);
    printf("Flight added successfully!\n");

}



// DELETING FLIGHT
void deleteFlight(){
    struct Flight flights[100]; 
    int count = 0, deleteID, found = 0;

    FILE *fp = fopen("Flights.txt", "r");
    if (fp == NULL) {
        printf("\nNo flights found!\n");
        return;
    }

// Read all flights into array
    while (fscanf(fp, "%d,%[^,],%[^,],%[^,],%[^,],%d,%d,%f\n",
        &flights[count].flight_id,
        flights[count].source,
        flights[count].destination,
        flights[count].date,    
        flights[count].time,
        &flights[count].total_seats,
        &flights[count].available_seats,
        &flights[count].price) == 8)
    {
        count++;
    }
        fclose(fp);

// Ask for ID to delete
    printf("\nEnter Flight ID to delete: ");
    scanf("%d", &deleteID);

// Search and delete using ID
    for (int i = 0; i < count; i++) {
        if (flights[i].flight_id == deleteID) {
            found = 1;
            for (int j = i; j < count - 1; j++) {
                flights[j] = flights[j + 1];
            }
            count--;
            break;
        }   
    }

    if (!found) {
        printf("\n Flight ID not found!\n");
        return;
    }

// Rewrite updated flights to file
    fp = fopen("Flights.txt", "w");
    for (int i = 0; i < count; i++) {
        fprintf(fp, "%d,%s,%s,%s,%s,%d,%d,%.2f\n",
            flights[i].flight_id,
            flights[i].source,
            flights[i].destination,
            flights[i].date,
            flights[i].time,
            flights[i].total_seats,
            flights[i].available_seats,
            flights[i].price);
    }
    fclose(fp);

    printf("\n Flight with ID %d deleted successfully!\n", deleteID);
}



// VIEW FLIGHTS
void viewFlights(){
    struct Flight flight;     // use existing struct definition
    FILE *fp = fopen("Flights.txt", "r");

    if (fp == NULL) {
        printf("\nNo flights found!\n");
        return;
    }

    printf("\n---------------------------------------------");
    printf("\n              All Available Flights");
    printf("\n---------------------------------------------\n\n");
    printf("%-10s %-15s %-15s %-12s %-8s %-10s %-10s %-8s\n",
        "ID", "Source", "Destination", "Date", "Time",
        "Seats", "Available", "Price");
    printf("---------------------------------------------------------------------------------------------\n");

    int count = 0;
    while (fscanf(fp, "%d,%[^,],%[^,],%[^,],%[^,],%d,%d,%f\n",
            &flight.flight_id,
            flight.source,
            flight.destination,
            flight.date,
            flight.time,
            &flight.total_seats,
            &flight.available_seats,
            &flight.price) == 8)
    {
    printf("%-10d %-15s %-15s %-12s %-8s %-10d %-10d %-8.2f\n",
           flight.flight_id,
           flight.source,
           flight.destination,
           flight.date,
           flight.time,
           flight.total_seats,
           flight.available_seats,
           flight.price);
    count++;
    }

    if (count == 0) {
        printf("\nNo flight records found.\n");
    }

    fclose(fp);
} 


void bookTicket(){} 
void cancelTicket(){}
void viewReservations(){} 