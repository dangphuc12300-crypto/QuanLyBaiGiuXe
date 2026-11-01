#include <stdio.h>
#include <string.h>
#include "parking.h"

void initParking(ParkingSlot slots[], int count) {
    for (int i = 0; i < count; ++i) {
        slots[i].id = i + 1;
        slots[i].occupied = 0;
        slots[i].plate[0] = '\0';
        slots[i].vehicleType[0] = '\0';
        slots[i].entryTime = 0;
    }
}

int findFreeSlot(ParkingSlot slots[], int count) {
    for (int i = 0; i < count; ++i)
        if (!slots[i].occupied) return i;
    return -1;
}

int findVehicle(ParkingSlot slots[], int count, const char *plate) {
    for (int i = 0; i < count; ++i)
        if (slots[i].occupied && strcmp(slots[i].plate, plate) == 0) return i;
    return -1;
}

int countOccupied(ParkingSlot slots[], int count) {
    int total = 0;
    for (int i = 0; i < count; ++i) total += slots[i].occupied ? 1 : 0;
    return total;
}

void showParkingMap(const ParkingSlot slots[], int count) {
    printf("\n========== SO DO BAI XE ==========\n");
    for (int i = 0; i < count; ++i) {
        printf("| P%02d: %-8s |", slots[i].id,
               slots[i].occupied ? "CO XE" : "TRONG");
        if ((i + 1) % 4 == 0) printf("\n");
    }
    if (count % 4 != 0) printf("\n");
    printf("Trong: %d/%d | Dang su dung: %d/%d\n",
           count - countOccupied((ParkingSlot *)slots, count), count,
           countOccupied((ParkingSlot *)slots, count), count);
    printf("==================================\n");
}
