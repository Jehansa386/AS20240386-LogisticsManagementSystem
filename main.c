#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CITIES 30
#define MAX_NAME_LEN 50
#define MAX_VEHICLES 3
#define MAX_DELIVERIES 50
#define FUEL_PRICE 310.0 // LKR per liter
#define INF 999999


//Vehicle data

typedef struct {
    char type[20];
    int capacity;      // in kg
    float rate;        // LKR per km
    float speed;       // km/h
    float efficiency;  // km per liter
} Vehicle;

Vehicle vehicles[MAX_VEHICLES] = {
    {"Van",   1000, 30, 60, 12},
    {"Truck", 5000, 40, 50, 6},
    {"Lorry", 10000, 80, 45, 4}
};

// Delivery data

typedef struct {
    char source[MAX_NAME_LEN];
    char destination[MAX_NAME_LEN];
    float distance;
    float weight;
    Vehicle vehicle;
    float deliveryCost;
    float fuelUsed;
    float fuelCost;
    float totalOperationalCost;
    float profit;
    float customerCharge;
    float time;
} Delivery;

char cities[MAX_CITIES][MAX_NAME_LEN];
int distanceMatrix[MAX_CITIES][MAX_CITIES];
int city_count = 0;
Delivery deliveries[MAX_DELIVERIES];
int deliveryCount = 0;



// Calculations
void calculateDeliveryCost(Delivery *d) {
    float D = d->distance;
    float W = d->weight;
    float R = d->vehicle.rate;
    float S = d->vehicle.speed;
    float E = d->vehicle.efficiency;

// Formulas
    d->deliveryCost = D * R * (1 + (W / 10000.0));
    d->fuelUsed = D / E;
    d->fuelCost = d->fuelUsed * FUEL_PRICE;
    d->totalOperationalCost = d->deliveryCost + d->fuelCost;
    d->profit = d->deliveryCost * 0.25;
    d->customerCharge = d->totalOperationalCost + d->profit;
    d->time = D / S;
}


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

// Distance management
void inputDistance() {
    if (city_count < 2) {
        printf("At least two cities are needed to set distances.\n");
        return;
    }

    printf("\n--- City List ---\n");
    for (int i = 0; i < city_count; i++) {
        printf("%d. %s\n", i + 1, cities[i]);
    }

    int c1, c2, dist;
    printf("Enter first city number: ");
    scanf("%d", &c1);
    printf("Enter second city number: ");
    scanf("%d", &c2);

    if (c1 < 1 || c2 < 1 || c1 > city_count || c2 > city_count || c1 == c2) {
        printf("Invalid city numbers.\n");
        return;
    }

    printf("Enter distance between %s and %s (in km): ", cities[c1 - 1], cities[c2 - 1]);
    scanf("%d", &dist);

    if (dist <= 0) {
        printf("Distance must be positive.\n");
        return;
    }

    distanceMatrix[c1 - 1][c2 - 1] = dist;
    distanceMatrix[c2 - 1][c1 - 1] = dist;
    printf("Distance updated successfully.\n");
}

//Display distance table
void displayDistanceTable() {
    if (city_count == 0) {
        printf("No cities to display distances.\n");
        return;
    }

    printf("\n%-15s", "City");
    for (int i = 0; i < city_count; i++) {
        printf("%-15s", cities[i]);
    }
    printf("\n");

    for (int i = 0; i < city_count; i++) {
        printf("%-15s", cities[i]);
        for (int j = 0; j < city_count; j++) {
            printf("%-15d", distanceMatrix[i][j]);
        }
        printf("\n");
    }
}

void distanceMenu() {
    int choice;
    do {
        printf("\n----- DISTANCE MANAGEMENT -----\n");
        printf("1. Input/Edit Distance\n");
        printf("2. Display Distance Table\n");
        printf("0. Back to Main Menu\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: inputDistance();
                break;
            case 2: displayDistanceTable();
                break;
            case 0: printf("Returning to main menu...\n");
                break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 0);
}

// Vehicle management

void displayVehicles() {
    printf("\n%-10s %-12s %-12s %-12s %-12s\n",
           "Type", "Capacity(kg)", "Rate/km", "Speed(km/h)", "Efficiency(km/l)");
    printf("------------------------------------------------------------------\n");

    for (int i = 0; i < MAX_VEHICLES; i++) {
        printf("%-10s %-12d %-12.2f %-12.2f %-12.2f\n",
               vehicles[i].type,
               vehicles[i].capacity,
               vehicles[i].rate,
               vehicles[i].speed,
               vehicles[i].efficiency);
    }
}

void vehicleMenu() {
    int choice;
    do {
        printf("\n----- VEHICLE MANAGEMENT -----\n");
        printf("1.Display Vehicle Details\n");
        printf("0.Back to Main Menu\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: displayVehicles();
                break;
            case 0: printf("Return to main menu...\n");
                break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 0);
}

// New delivery
void addDelivery() {
    if (city_count < 2) {
        printf("You need at least 2 cities to create a delivery.\n");
        return;
    }

    if (deliveryCount >= MAX_DELIVERIES) {
        printf("Maximum number of deliveries reached.\n");
        return;
    }

    printf("\n--- City List ---\n");
    for (int i = 0; i < city_count; i++) {
        printf("%d. %s\n", i + 1, cities[i]);
    }

    int src, dest;
    printf("Enter source city number: ");
    scanf("%d", &src);
    printf("Enter destination city number: ");
    scanf("%d", &dest);

    if (src < 1 || dest < 1 || src > city_count || dest > city_count || src == dest) {
        printf("Invalid city selection.\n");
        return;
    }

    float dist = distanceMatrix[src - 1][dest - 1];
    if (dist <= 0) {
        printf("Distance not set between these cities. Please add it first.\n");
        return;
    }

    displayVehicles();
    int vChoice;
    printf("Select vehicle (1=Van, 2=Truck, 3=Lorry): ");
    scanf("%d", &vChoice);

    if (vChoice < 1 || vChoice > MAX_VEHICLES) {
        printf("Invalid vehicle type.\n");
        return;
    }

    float weight;
    printf("Enter package weight (in kg): ");
    scanf("%f", &weight);

    if (weight > vehicles[vChoice - 1].capacity) {
        printf("Weight exceeds vehicle capacity!\n");
        return;
    }

    // Store delivery data
    Delivery d;
    strcpy(d.source, cities[src - 1]);
    strcpy(d.destination, cities[dest - 1]);
    d.distance = dist;
    d.weight = weight;
    d.vehicle = vehicles[vChoice - 1];

    calculateDeliveryCost(&d);
    deliveries[deliveryCount++] = d;

    printf("\n-----------------------------\n");
    printf("DELIVERY COST ESTIMATION\n");
    printf("------------------------------\n");
    printf("From: %s\n", d.source);
    printf("To: %s\n", d.destination);
    printf("Distance: %.2f km\n", d.distance);
    printf("Vehicle: %s\n", d.vehicle.type);
    printf("Weight: %.2f kg\n", d.weight);
    printf("------------------------------\n");
    printf("Base Cost: %.2f LKR\n", d.deliveryCost);
    printf("Fuel Used: %.2f L\n", d.fuelUsed);
    printf("Fuel Cost: %.2f LKR\n", d.fuelCost);
    printf("Operational Cost: %.2f LKR\n", d.totalOperationalCost);
    printf("Profit: %.2f LKR\n", d.profit);
    printf("Customer Charge: %.2f LKR\n", d.customerCharge);
    printf("Estimated Time: %.2f hours\n", d.time);
    printf("------------------------------\n");
}

void viewDeliveries() {
    if (deliveryCount == 0) {
        printf("No deliveries recorded yet.\n");
        return;
    }

    printf("\n----- ALL DELIVERIES -----\n");
    for (int i = 0; i < deliveryCount; i++) {
        printf("%d. %s -> %s | %.2f km | %.2f kg | %s | Charge: %.2f LKR\n",
               i + 1,
               deliveries[i].source,
               deliveries[i].destination,
               deliveries[i].distance,
               deliveries[i].weight,
               deliveries[i].vehicle.type,
               deliveries[i].customerCharge);
    }
}

void deliveryMenu() {
    int choice;
    do {
        printf("\n----- DELIVERY MANAGEMENT -----\n");
        printf("1. Create New Delivery\n");
        printf("2. View All Deliveries\n");
        printf("0. Back to Main Menu\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addDelivery();
                break;
            case 2: viewDeliveries();
                break;
            case 0: printf("Returning to main menu...\n");
                break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 0);
}

// Reports
void generateReports() {
    if (deliveryCount == 0) {
        printf("No deliveries to report.\n");
        return;
    }

    float totalDistance = 0, totalTime = 0, totalRevenue = 0, totalProfit = 0;
    float longestRoute = 0, shortestRoute = deliveries[0].distance;
    int longestIndex = 0, shortestIndex = 0;

    for (int i = 0; i < deliveryCount; i++) {
        totalDistance += deliveries[i].distance;
        totalTime += deliveries[i].time;
        totalRevenue += deliveries[i].customerCharge;
        totalProfit += deliveries[i].profit;

        if (deliveries[i].distance > longestRoute) {
            longestRoute = deliveries[i].distance;
            longestIndex = i;
        }
        if (deliveries[i].distance < shortestRoute) {
            shortestRoute = deliveries[i].distance;
            shortestIndex = i;
        }
    }

    float avgTime = totalTime / deliveryCount;

    printf("\n==============================\n");
    printf("        PERFORMANCE REPORT     \n");
    printf("==============================\n");
    printf("Total Deliveries Completed : %d\n", deliveryCount);
    printf("Total Distance Covered     : %.2f km\n", totalDistance);
    printf("Average Delivery Time      : %.2f hours\n", avgTime);
    printf("Total Revenue (LKR)        : %.2f\n", totalRevenue);
    printf("Total Profit (LKR)         : %.2f\n", totalProfit);
    printf("------------------------------\n");
    printf("Longest Route: %s → %s (%.2f km)\n",
           deliveries[longestIndex].source,
           deliveries[longestIndex].destination,
           deliveries[longestIndex].distance);
    printf("Shortest Route: %s → %s (%.2f km)\n",
           deliveries[shortestIndex].source,
           deliveries[shortestIndex].destination,
           deliveries[shortestIndex].distance);
    printf("==============================\n");
}

void reportsMenu() {
    int choice;
    do {
        printf("\n----- REPORTS MENU -----\n");
        printf("1. Generate Performance Report\n");
        printf("0. Back to Main Menu\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: generateReports();
                break;
            case 0: printf("Returning to main menu...\n");
                break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 0);
}
float calculateRouteDistance(int route[], int routeLength) {
    float total = 0;

    for (int i = 0; i < routeLength - 1; i++) {
        int from = route[i];
        int to = route[i + 1];
        if (distanceMatrix[from][to] == 0) {
            return INF;
        }
        total += distanceMatrix[from][to];
    }

    return total;
}
void findLeastCostRoute() {
    if (city_count < 2) {
        printf("At least two cities are needed.\n");
        return;
    }

    printf("\n--- City List ---\n");
    for (int i = 0; i < city_count; i++) {
        printf("%d. %s\n", i + 1, cities[i]);
    }

    int src, dest;
    printf("Enter source city number: ");
    scanf("%d", &src);
    printf("Enter destination city number: ");
    scanf("%d", &dest);

    if (src < 1 || dest < 1 || src > city_count || dest > city_count || src == dest) {
        printf("Invalid city numbers.\n");
        return;
    }

// Basic direct distance
    float directDistance = distanceMatrix[src - 1][dest - 1];
    float bestDistance = directDistance > 0 ? directDistance : INF;

    int bestRoute[5];
    int route[5];

// Try all 1, 2, and 3 intermediate city routes
    for (int i = 0; i < city_count; i++) {
        if (i == src - 1 || i == dest - 1) continue;

// Route: src → i → dest
        int route2[] = {src - 1, i, dest - 1};
        float dist2 = calculateRouteDistance(route2, 3);
        if (dist2 < bestDistance) {
            bestDistance = dist2;
            memcpy(bestRoute, route2, sizeof(route2));
        }

// Try 2 intermediate cities: src → i → j → dest
        for (int j = 0; j < city_count; j++) {
            if (j == src - 1 || j == dest - 1 || j == i) continue;
            int route3[] = {src - 1, i, j, dest - 1};
            float dist3 = calculateRouteDistance(route3, 4);
            if (dist3 < bestDistance) {
                bestDistance = dist3;
                memcpy(bestRoute, route3, sizeof(route3));
            }
        }
    }

    if (bestDistance == INF) {
        printf("No possible route found between %s and %s.\n",
               cities[src - 1], cities[dest - 1]);
        return;
    }

// Display result
    printf("\n==============================\n");
    printf("LEAST-COST ROUTE SEARCH\n");
    printf("------------------------------\n");
    printf("From: %s\n", cities[src - 1]);
    printf("To: %s\n", cities[dest - 1]);
    printf("Minimum Distance: %.2f km\n", bestDistance);
    printf("Best Route: ");

    for (int k = 0; k < 4; k++) {
        if (bestRoute[k] == dest - 1) {
            printf("%s", cities[bestRoute[k]]);
            break;
        }
        if (bestRoute[k] < city_count)
            printf("%s -> ", cities[bestRoute[k]]);
    }

    printf("\n==============================\n");
}
void leastCostMenu() {
    int choice;
    do {
        printf("\n----- LEAST-COST ROUTE MENU -----\n");
        printf("1. Find Least-Cost Route\n");
        printf("0. Back to Main Menu\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: findLeastCostRoute();
                break;
            case 0: printf("Returning to main menu...\n");
                break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 0);
}

// File handling function

void saveRoutesToFile() {
    FILE *fp = fopen("routes.txt", "w");
    if (!fp) {
        printf("Error saving routes file.\n");
        return;
    }

    fprintf(fp, "%d\n", city_count);
    for (int i = 0; i < city_count; i++) {
        fprintf(fp, "%s\n", cities[i]);
    }

    for (int i = 0; i < city_count; i++) {
        for (int j = 0; j < city_count; j++) {
            fprintf(fp, "%d ", distanceMatrix[i][j]);
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
    printf("Routes saved successfully.\n");
}

// Load city list and distance matrix
void loadRoutesFromFile() {
    FILE *fp = fopen("routes.txt", "r");
    if (!fp) return;

    fscanf(fp, "%d\n", &city_count);
    for (int i = 0; i < city_count; i++) {
        fgets(cities[i], MAX_NAME_LEN, fp);
        cities[i][strcspn(cities[i], "\n")] = '\0';
    }

    for (int i = 0; i < city_count; i++) {
        for (int j = 0; j < city_count; j++) {
            fscanf(fp, "%d", &distanceMatrix[i][j]);
        }
    }

    fclose(fp);
    printf("Routes loaded successfully.\n");
}

// Save deliveries
void saveDeliveriesToFile() {
    FILE *fp = fopen("deliveries.txt", "w");
    if (!fp) {
        printf("Error saving deliveries file.\n");
        return;
    }

    fprintf(fp, "%d\n", deliveryCount);
    for (int i = 0; i < deliveryCount; i++) {
        Delivery d = deliveries[i];
        fprintf(fp, "%s,%s,%.2f,%.2f,%s,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f\n",
                d.source, d.destination, d.distance, d.weight, d.vehicle.type,
                d.deliveryCost, d.fuelUsed, d.fuelCost, d.totalOperationalCost,
                d.profit, d.customerCharge, d.time);
    }

    fclose(fp);
    printf("Deliveries saved successfully.\n");
}

// Load deliveries
void loadDeliveriesFromFile() {
    FILE *fp = fopen("deliveries.txt", "r");
    if (!fp) return;

    fscanf(fp, "%d\n", &deliveryCount);
    for (int i = 0; i < deliveryCount; i++) {
        Delivery d;
        fscanf(fp, "%[^,],%[^,],%f,%f,%[^,],%f,%f,%f,%f,%f,%f,%f\n",
               d.source, d.destination, &d.distance, &d.weight, d.vehicle.type,
               &d.deliveryCost, &d.fuelUsed, &d.fuelCost, &d.totalOperationalCost,
               &d.profit, &d.customerCharge, &d.time);

// Match vehicle details by type
        for (int v = 0; v < MAX_VEHICLES; v++) {
            if (strcmp(d.vehicle.type, vehicles[v].type) == 0) {
                d.vehicle = vehicles[v];
                break;
            }
        }

        deliveries[i] = d;
    }

    fclose(fp);
    printf("Deliveries loaded successfully.\n");
}




int main()
{
    loadRoutesFromFile();
    loadDeliveriesFromFile();

    int mainChoice;

    do {
        printf("\n------ LOGISTICS MANAGEMENT SYSTEM ------\n");
        printf("1. City Management\n");
        printf("2. Distance Management\n");
        printf("3. Vehicle Management\n");
        printf("4. Delivery Management\n");
        printf("5. Reports\n");
        printf("6. Least-Cost Route Finder\n");
        printf("0. Exit\n");
        printf("\n-----------------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &mainChoice);

        switch (mainChoice) {
            case 1: cityMenu();
                break;
            case 2: distanceMenu();
                break;
            case 3: vehicleMenu();
                break;
            case 4: deliveryMenu();
                break;
            case 5: reportsMenu();
                break;
            case 6: leastCostMenu();
                break;
            case 0: printf("Saving data and exiting...\n");
                saveRoutesToFile();
                saveDeliveriesToFile();
                break;
            default: printf("Invalid choice.\n");
        }

    } while (mainChoice != 0);



    return 0;
}
