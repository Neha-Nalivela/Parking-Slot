#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_VEHICLE_NUMBER 20
#define HASH_MAP_SIZE 100
#define MAX_FINE_AMOUNT 1000
int i;

typedef struct Node {
    char vehicleNumber[MAX_VEHICLE_NUMBER];
    int slot;
    time_t entryTime;
    struct Node* next;
} Node;

typedef struct {
    char vehicleNumber[MAX_VEHICLE_NUMBER];
    int slot;
    time_t entryTime;
} HashEntry;

typedef struct {
    int* slots;
    int totalSlots;
    char** queue;
    int front, rear, maxQueueSize;
    Node* parkedList;
    HashEntry* hashMap;
} ParkingSystem;

int hashFunction(char* vehicleNumber) {
    int sum = 0;
    for (i = 0; vehicleNumber[i] != '\0'; i++) {
        sum += vehicleNumber[i];
    }
    return sum % HASH_MAP_SIZE;
}

ParkingSystem* initializeSystem(int totalSlots, int maxQueueSize) {
    ParkingSystem* system = (ParkingSystem*)malloc(sizeof(ParkingSystem));
    system->slots = (int*)malloc(totalSlots * sizeof(int));
    system->totalSlots = totalSlots;
    system->queue = (char**)malloc(maxQueueSize * sizeof(char));
    system->front = system->rear = -1;
    system->maxQueueSize = maxQueueSize;
    system->parkedList = NULL;
    system->hashMap = (HashEntry*)malloc(HASH_MAP_SIZE * sizeof(HashEntry));

    for (i = 0; i < totalSlots; i++) {
        system->slots[i] = 1; // All slots are free
    }
    for (i = 0; i < HASH_MAP_SIZE; i++) {
        strcpy(system->hashMap[i].vehicleNumber, "");
        system->hashMap[i].slot = -1;
    }

    return system;
}

void freeSystem(ParkingSystem* system) {
    free(system->slots);
    for (i = 0; i <= system->rear; i++) {
        free(system->queue[i]);
    }
    free(system->queue);
    free(system->hashMap);

    Node* current = system->parkedList;
    while (current) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }

    free(system);
}

void enqueue(ParkingSystem* system, char* vehicleNumber) {
    if ((system->rear + 1) % system->maxQueueSize == system->front) {
        printf("Queue is full! Cannot add vehicle %s.\n", vehicleNumber);
        return;
    }

    if (system->front == -1) {
        system->front = 0;
    }

    system->rear = (system->rear + 1) % system->maxQueueSize;
    system->queue[system->rear] = strdup(vehicleNumber);
    printf("Vehicle %s added to the queue.\n", vehicleNumber);
}

char* dequeue(ParkingSystem* system) {
    if (system->front == -1) {
        printf("Queue is empty!\n");
        return NULL;
    }

    char* vehicleNumber = system->queue[system->front];
    if (system->front == system->rear) {
        system->front = system->rear = -1; // Reset queue
    } else {
        system->front = (system->front + 1) % system->maxQueueSize;
    }

    return vehicleNumber;
}

void parkVehicle(ParkingSystem* system, char* vehicleNumber) {
    int slot = -1;
    for (i = 0; i < system->totalSlots; i++) {
        if (system->slots[i] == 1) {
            slot = i;
            system->slots[i] = 0; // Mark slot as occupied
            break;
        }
    }

    if (slot == -1) {
        printf("No available slots. Adding vehicle %s to the waiting queue.\n", vehicleNumber);
        enqueue(system, vehicleNumber);
        return;
    }

    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->vehicleNumber, vehicleNumber);
    newNode->slot = slot + 1; // Slot numbers are 1-based
    newNode->entryTime = time(NULL);
    newNode->next = system->parkedList;
    system->parkedList = newNode;

    int hashIndex = hashFunction(vehicleNumber);
    strcpy(system->hashMap[hashIndex].vehicleNumber, vehicleNumber);
    system->hashMap[hashIndex].slot = slot + 1;

    printf("Vehicle %s parked at slot %d.\n", vehicleNumber, slot + 1);
}
void removeVehicle(ParkingSystem* system, char* vehicleNumber) {
int hashIndex = hashFunction(vehicleNumber);
if (strcmp(system->hashMap[hashIndex].vehicleNumber, vehicleNumber) != 0) {
printf("Vehicle %s not found!\n", vehicleNumber);
return;
}

int slot = system->hashMap[hashIndex].slot;
system->slots[slot - 1] = 1; // Mark slot as free

Node** curr = &(system->parkedList);
while (*curr) {
    if (strcmp((*curr)->vehicleNumber, vehicleNumber) == 0) {
        Node* temp = *curr;
        *curr = (*curr)->next;
        free(temp);

        time_t currentTime = time(NULL);
        double parkingTime = difftime(currentTime, system->hashMap[hashIndex].entryTime);
        double fine = (parkingTime / 60) * 10; // 10 rupees per hour
        if (fine > MAX_FINE_AMOUNT) {
            fine = MAX_FINE_AMOUNT;
        }

        printf("Vehicle %s removed from slot %d.\n", vehicleNumber, slot);
        printf("Parking time: %.2f seconds\n", parkingTime / 60);
        printf("Fine: %.2f rupees\n", fine);

        break;
    }
    curr = &((*curr)->next);
}

strcpy(system->hashMap[hashIndex].vehicleNumber, "");
system->hashMap[hashIndex].slot = -1;

char* nextVehicle = dequeue(system);
if (nextVehicle != NULL) {
    parkVehicle(system, nextVehicle);
}

}

void displayParkedVehicles(ParkingSystem* system) {
Node* curr = system->parkedList;
if (!curr) {
printf("No vehicles parked.\n");
return;
}

printf("Parked Vehicles:\n");
while (curr) {
    printf("Vehicle: %s, Slot: %d\n", curr->vehicleNumber, curr->slot);
    curr = curr->next;
}

}

int main() {
int totalSlots, maxQueueSize;
printf("Enter the number of parking slots: ");
scanf("%d", &totalSlots);
printf("Enter the maximum queue size: ");
scanf("%d", &maxQueueSize);

ParkingSystem* system = initializeSystem(totalSlots, maxQueueSize);

int choice;
char vehicleNumber[MAX_VEHICLE_NUMBER];
while (1) {
    printf("\n--- Parking Management System ---\n");
    printf("1. Park Vehicle\n");
    printf("2. Remove Vehicle\n");
    printf("3. Display Parked Vehicles\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("Enter vehicle number to park: ");
            scanf("%s", vehicleNumber);
            parkVehicle(system, vehicleNumber);
            break;
        case 2:
            printf("Enter vehicle number to remove: ");
            scanf("%s", vehicleNumber);
            removeVehicle(system, vehicleNumber);
            break;
        case 3:
            displayParkedVehicles(system);
            break;
        case 4:
            freeSystem(system);
            printf("Exiting...\n");
            return 0;
        default:
            printf("Invalid choice! Try again.\n");
    }
}

return 0;

}
