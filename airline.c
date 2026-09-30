#include <stdio.h>
#include <string.h>

#define ROWS 5
#define COLS 4

struct Passenger
{
    char name[50];
    int age;
    int seat;
    char destination[50];
};

struct Passenger passengers[ROWS * COLS];

int seats[ROWS][COLS] = {0};

void saveData()
{
    FILE *fp = fopen("airline.dat", "wb");

    if (fp == NULL)
    {
        printf("File error!\n");
        return;
    }

    fwrite(seats, sizeof(seats), 1, fp);
    fwrite(passengers, sizeof(passengers), 1, fp);

    fclose(fp);
}

void loadData()
{
    FILE *fp = fopen("airline.dat", "rb");

    if (fp == NULL)
        return;

    fread(seats, sizeof(seats), 1, fp);
    fread(passengers, sizeof(passengers), 1, fp);

    fclose(fp);
}

void displaySeats()
{
    int i, j;

    printf("\n----- SEAT LAYOUT -----\n");

    for (i = 0; i < ROWS; i++)
    {
        for (j = 0; j < COLS; j++)
        {
            int seatNumber = i * COLS + j + 1;

            if (seats[i][j] == 0)
                printf("[%02d: Available] ", seatNumber);
            else
                printf("[%02d: Booked]   ", seatNumber);
        }

        printf("\n");
    }
}

void bookSeat()
{
    int seat, row, col;

    printf("Enter seat number (1-%d): ", ROWS * COLS);
    scanf("%d", &seat);

    if (seat < 1 || seat > ROWS * COLS)
    {
        printf("Invalid seat number!\n");
        return;
    }

    row = (seat - 1) / COLS;
    col = (seat - 1) % COLS;

    if (seats[row][col] == 1)
    {
        printf("Seat already booked!\n");
        return;
    }

    printf("Enter passenger name: ");
    scanf(" %[^\n]", passengers[seat - 1].name);

    printf("Enter passenger age: ");
    scanf("%d", &passengers[seat - 1].age);

    printf("Enter destination: ");
    scanf(" %[^\n]", passengers[seat - 1].destination);

    passengers[seat - 1].seat = seat;
    seats[row][col] = 1;

    saveData();

    printf("\nTicket generated successfully!\n");
    printf("Passenger: %s\n", passengers[seat - 1].name);
    printf("Seat: %d\n", seat);
    printf("Destination: %s\n",
           passengers[seat - 1].destination);
}

void cancelSeat()
{
    int seat, row, col;

    printf("Enter seat number to cancel: ");
    scanf("%d", &seat);

    if (seat < 1 || seat > ROWS * COLS)
    {
        printf("Invalid seat number!\n");
        return;
    }

    row = (seat - 1) / COLS;
    col = (seat - 1) % COLS;

    if (seats[row][col] == 0)
    {
        printf("Seat is already available!\n");
        return;
    }

    seats[row][col] = 0;
    passengers[seat - 1].seat = 0;
    strcpy(passengers[seat - 1].name, "");
    strcpy(passengers[seat - 1].destination, "");

    saveData();

    printf("Booking cancelled successfully!\n");
}

void passengerDetails()
{
    int seat;

    printf("Enter seat number: ");
    scanf("%d", &seat);

    if (seat < 1 || seat > ROWS * COLS)
    {
        printf("Invalid seat!\n");
        return;
    }

    if (seats[(seat - 1) / COLS][(seat - 1) % COLS] == 0)
    {
        printf("Seat is not booked.\n");
        return;
    }

    printf("\nPassenger Name: %s",
           passengers[seat - 1].name);

    printf("\nAge: %d",
           passengers[seat - 1].age);

    printf("\nDestination: %s",
           passengers[seat - 1].destination);

    printf("\nSeat Number: %d\n", seat);
}

int main()
{
    int choice;

    loadData();

    do
    {
        printf("\n==============================");
        printf("\n AIRLINE RESERVATION SYSTEM");
        printf("\n==============================");

        printf("\n1. Display Seats");
        printf("\n2. Book Seat");
        printf("\n3. Cancel Seat");
        printf("\n4. Passenger Details");
        printf("\n5. Exit");

        printf("\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                displaySeats();
                break;

            case 2:
                bookSeat();
                break;

            case 3:
                cancelSeat();
                break;

            case 4:
                passengerDetails();
                break;

            case 5:
                printf("Thank you!\n");
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while (choice != 5);

    return 0;
}