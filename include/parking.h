#ifndef PARKING_H
#define PARKING_H

#include <time.h>

#define MAX_SLOTS 20
#define PLATE_LEN 20
#define NAME_LEN 50
#define HISTORY_FILE "data/lichsu.csv"
#define DATA_FILE "data/xe_dang_gui.csv"

typedef struct {
    int id;
    int occupied;
    char plate[PLATE_LEN];
    char vehicleType[12];
    time_t entryTime;
} ParkingSlot;

typedef struct {
    char plate[PLATE_LEN];
    int slotId;
    char vehicleType[12];
    time_t entryTime;
    time_t exitTime;
    double durationHours;
    long fee;
} ParkingRecord;

void initParking(ParkingSlot slots[], int count);
int findFreeSlot(ParkingSlot slots[], int count);
int findVehicle(ParkingSlot slots[], int count, const char *plate);
int countOccupied(ParkingSlot slots[], int count);
void showParkingMap(const ParkingSlot slots[], int count);
void showDateTime(time_t value, char *buffer, size_t size);
long calculateFee(time_t entry, time_t exit, const char *vehicleType);
int saveActiveVehicles(const ParkingSlot slots[], int count);
int loadActiveVehicles(ParkingSlot slots[], int count);
int appendHistory(const ParkingRecord *record);
void showHistory(void);
void showStatistics(void);
void printMenu(void);
void processEntry(ParkingSlot slots[], int count);
void processExit(ParkingSlot slots[], int count);
void searchVehicle(const ParkingSlot slots[], int count);

#endif
