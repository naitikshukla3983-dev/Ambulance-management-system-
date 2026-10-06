#include <stdio.h>

#define MAX 10

struct Ambulance {
    int id;
    char driver[30];
    int available;
};

struct Request {
    char patient[30];
    char location[40];
};

int main() {
    struct Ambulance ambulance[MAX];
    struct Request request[MAX];

    int total = 0;
    int front = 0, rear = -1;
    int choice, id, found, i, j;

    do {
        printf("\n========================================\n");
        printf("       AMBULANCE MANAGEMENT SYSTEM\n");
        printf("========================================\n");

        printf("1. Add Ambulance\n");
        printf("2. Display Ambulances\n");
        printf("3. Request Ambulance\n");
        printf("4. Allocate Ambulance\n");
        printf("5. Complete Trip\n");
        printf("6. Search Ambulance\n");
        printf("7. Sort Ambulances\n");
        printf("8. View Waiting Requests\n");
        printf("9. Exit\n");

        printf("\nEnter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            if (total == MAX) {
                printf("Ambulance limit reached.\n");
            } else {
                printf("Enter Ambulance ID: ");
                scanf("%d", &id);

                found = 0;
                for (i = 0; i < total; i++) {
                    if (ambulance[i].id == id) {
                        found = 1;
                        break;
                    }
                }

                if (found) {
                    printf("ID already exists.\n");
                } else {
                    ambulance[total].id = id;

                    printf("Enter Driver Name: ");
                    scanf(" %[^\n]", ambulance[total].driver);

                    ambulance[total].available = 1;
                    total++;

                    printf("Ambulance added.\n");
                }
            }
        }

        else if (choice == 2) {
            if (total == 0) {
                printf("No ambulances available.\n");
            } else {
                printf("\nID\tDriver\t\tStatus\n");

                for (i = 0; i < total; i++) {
                    printf("%d\t%-15s",
                           ambulance[i].id,
                           ambulance[i].driver);

                    if (ambulance[i].available)
                        printf("Available\n");
                    else
                        printf("Busy\n");
                }
            }
        }

        else if (choice == 3) {
            if (rear == MAX - 1) {
                printf("Request queue is full.\n");
            } else {
                rear++;

                printf("Enter Patient Name: ");
                scanf(" %[^\n]", request[rear].patient);

                printf("Enter Location: ");
                scanf(" %[^\n]", request[rear].location);

                printf("Request added to queue.\n");
            }
        }

        else if (choice == 4) {
            if (front > rear) {
                printf("No pending requests.\n");
            } else {
                found = 0;

                for (i = 0; i < total; i++) {
                    if (ambulance[i].available) {
                        ambulance[i].available = 0;

                        printf("\nAmbulance allocated.\n");
                        printf("Patient: %s\n", request[front].patient);
                        printf("Location: %s\n", request[front].location);
                        printf("Ambulance ID: %d\n", ambulance[i].id);
                        printf("Driver: %s\n", ambulance[i].driver);

                        front++;
                        found = 1;
                        break;
                    }
                }

                if (!found) {
                    printf("No ambulance is available.\n");
                }
            }
        }

        else if (choice == 5) {
            printf("Enter Ambulance ID: ");
            scanf("%d", &id);

            found = 0;

            for (i = 0; i < total; i++) {
                if (ambulance[i].id == id) {
                    found = 1;

                    if (ambulance[i].available == 0) {
                        ambulance[i].available = 1;
                        printf("Trip completed. Ambulance is available.\n");
                    } else {
                        printf("Ambulance is already available.\n");
                    }

                    break;
                }
            }

            if (!found) {
                printf("Ambulance not found.\n");
            }
        }

        else if (choice == 6) {
            printf("Enter Ambulance ID: ");
            scanf("%d", &id);

            found = 0;

            for (i = 0; i < total; i++) {
                if (ambulance[i].id == id) {
                    printf("\nAmbulance Found\n");
                    printf("ID: %d\n", ambulance[i].id);
                    printf("Driver: %s\n", ambulance[i].driver);

                    if (ambulance[i].available)
                        printf("Status: Available\n");
                    else
                        printf("Status: Busy\n");

                    found = 1;
                    break;
                }
            }

            if (!found) {
                printf("Ambulance not found.\n");
            }
        }

        else if (choice == 7) {
            for (i = 0; i < total - 1; i++) {
                for (j = 0; j < total - i - 1; j++) {
                    if (ambulance[j].id > ambulance[j + 1].id) {
                        struct Ambulance temp;

                        temp = ambulance[j];
                        ambulance[j] = ambulance[j + 1];
                        ambulance[j + 1] = temp;
                    }
                }
            }

            printf("Ambulances sorted by ID.\n");
        }

        else if (choice == 8) {
            if (front > rear) {
                printf("\nNo patients are waiting.\n");
            } else {
                printf("\n----- WAITING REQUESTS -----\n");
                printf("Patients waiting: %d\n\n", rear - front + 1);

                for (i = front; i <= rear; i++) {
                    printf("%d. %s - %s\n",
                           i - front + 1,
                           request[i].patient,
                           request[i].location);
                }
            }
        }

        else if (choice == 9) {
            printf("Thank you!\n");
        }

        else {
            printf("Invalid choice.\n");
        }

    } while (choice != 9);

    return 0;
}
