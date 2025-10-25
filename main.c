#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CITIES 30
#define MAX_NAME_LEN 50

char cities[MAX_CITIES][MAX_NAME_LEN];
int city_count = 0;

// Add a new city
void addCity() {

    if (city_count >= MAX_CITIES) {
        printf("You have already added the maximum number of cities.\n");
        return;
    }

    getchar();

    char name[MAX_NAME_LEN];
    printf("Enter city name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';


     for (int i = 0; i < city_count; i++) {
        if (strcmp(cities[i], name) == 0) {
            printf("This city already exists.\n");
            return;
        }
    }

    strcpy(cities[city_count], name);
    city_count++;
    printf("City '%s' added successfully.\n", name);
}

// Rename a city
void renameCity() {
    if (city_count == 0) {
        printf("No cities available to rename.\n");
        return;
    }

     printf("\n--- City List ---\n");
    for (int i = 0; i < city_count; i++) {
        printf("%d. %s\n", i + 1, cities[i]);
    }

    int index;
    printf("Enter city number to rename: ");

    if (scanf("%d", &index) != 1 || index < 1 || index > city_count) {
        printf("Invalid index.\n");
        while (getchar() != '\n');
        return;
    }

    getchar();

    char newName[MAX_NAME_LEN];
    printf("Enter new name: ");
    fgets(newName, sizeof(newName), stdin);
    newName[strcspn(newName, "\n")] = '\0';

    // Checking duplications
    for (int i = 0; i < city_count; i++) {
        if (strcmp(cities[i], newName) == 0) {
            printf("This city already exists.\n");
            return;
        }
    }

    strcpy(cities[index - 1], newName);
    printf("City renamed successfully.\n");
}

// Remove a city
void removeCity() {
    if (city_count == 0) {
        printf("No cities available to remove.\n");
        return;
    }

    printf("\n--- City List ---\n");
    for (int i = 0; i < city_count; i++){
        printf("%d. %s\n", i + 1, cities[i]);
    }


    int index;
    printf("Enter city number to remove: ");

    if (scanf("%d", &index) != 1 || index < 1 || index > city_count) {
        printf("Invalid index.\n");
        while (getchar() != '\n');
        return;
    }

    for (int i = index - 1; i < city_count - 1; i++) {
        strcpy(cities[i], cities[i + 1]);
    }

    city_count--;
    printf("City removed successfully.\n");
}

void cityMenu() {
    int choice;
    do {
        printf("\n----- CITY MANAGEMENT -----\n");
        printf("1.Add City\n");
        printf("2.Rename City\n");
        printf("3.Remove City\n");
        printf("0.Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:addCity();
                break;
            case 2:renameCity();
                break;
            case 3:removeCity();
                break;
            case 0:printf("Exiting program...\n");
                break;
            default:printf("Invalid choice.\n");
        }
    } while (choice != 0);
}




int main()
{
    int main() {
    int mainChoice;

    do {
        printf("\n------ LOGISTICS MANAGEMENT SYSTEM ------\n");
        printf("1. City Management\n");
        printf("2. Distance Management\n");
        printf("0. Exit\n");
        printf("\n---------------------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &mainChoice);

        switch (mainChoice) {
            case 1: cityMenu();
                break;
            case 2: distanceMenu();
                break;
            case 0: printf("Exiting program...\n");
                break;
            default: printf("Invalid choice.\n");
        }

    } while (mainChoice != 0);

    return 0;
}

    return 0;
}
