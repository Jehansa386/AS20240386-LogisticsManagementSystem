#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CITIES 30
#define MAX_NAME_LEN 50

char cities[MAX_CITIES][MAX_NAME_LEN];
int city_count = 0;

void addCity() {

    char name[MAX_NAME_LEN];
    printf("Enter city name: ");
    scanf("%s", name);

    strcpy(cities[city_count], name);
    city_count++;
    printf("City '%s' added successfully.\n", name);
}

int main()
{
    int choice;
    do {
        printf("\n----- CITY MANAGEMENT -----\n");
        printf("1.Add City\n");
        printf("2.Rename City\n");
        printf("3.Remove City\n");
        printf("4.Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:addCity();
                break;
            case 2:renameCity();
                break;
            case 3:removeCity();
                break;
            case 4:printf("Exiting program...\n");
                break;
            default:printf("Invalid choice.\n");
        }
    } while (choice != 4);


    return 0;
}
