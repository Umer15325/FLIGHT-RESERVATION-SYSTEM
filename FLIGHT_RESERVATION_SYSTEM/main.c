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
void main(){
    mainMenu();
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

    fprintf(fp, "%d ,%s ,%s ,%s ,%s ,%d, %d, %.2f\n", f.flight_id, f.source, f.destination, f.date, f.time, f.total_seats,f.available_seats ,f.price);

    fclose(fp);
    printf("Student added successfully!\n");

}


void deleteFlight(){}
void viewFlights(){} 
void bookTicket(){} 
void cancelTicket(){}
void viewReservations(){} 