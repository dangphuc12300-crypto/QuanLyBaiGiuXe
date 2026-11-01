#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "parking.h"

static int readLine(const char *prompt, char *out, size_t size) {
    printf("%s", prompt);
    if (!fgets(out, (int)size, stdin)) return 0;
    out[strcspn(out, "\r\n")] = '\0';
    return 1;
}

static void normalizePlate(char *plate) {
    for (size_t i = 0; plate[i]; ++i)
        plate[i] = (char)toupper((unsigned char)plate[i]);
}

void processEntry(ParkingSlot slots[], int count) {
    char plate[PLATE_LEN], type[12];
    int index;
    if (!readLine("Nhap bien so xe: ", plate, sizeof(plate))) return;
    normalizePlate(plate);
    if (strlen(plate) < 5) {
        printf("Bien so khong hop le (toi thieu 5 ky tu).\n");
        return;
    }
    if (findVehicle(slots, count, plate) >= 0) {
        printf("Bien so nay dang co trong bai.\n");
        return;
    }
    if (readLine("Loai xe (XM/OTO): ", type, sizeof(type)) == 0) return;
    for (size_t i = 0; type[i]; ++i) type[i] = (char)toupper((unsigned char)type[i]);
    if (strcmp(type, "XM") != 0 && strcmp(type, "OTO") != 0) {
        printf("Loai xe khong hop le.\n");
        return;
    }
    index = findFreeSlot(slots, count);
    if (index < 0) {
        printf("Bai xe da day, khong the tiep nhan.\n");
        return;
    }
    slots[index].occupied = 1;
    snprintf(slots[index].plate, PLATE_LEN, "%s", plate);
    snprintf(slots[index].vehicleType, sizeof(slots[index].vehicleType), "%s", type);
    slots[index].entryTime = time(NULL);
    char t[32];
    showDateTime(slots[index].entryTime, t, sizeof(t));
    printf("Nhan xe thanh cong. Vi tri P%02d, gio vao: %s\n", slots[index].id, t);
    saveActiveVehicles(slots, count);
}

void processExit(ParkingSlot slots[], int count) {
    char plate[PLATE_LEN], in[32], out[32];
    if (!readLine("Nhap bien so xe can ra: ", plate, sizeof(plate))) return;
    normalizePlate(plate);
    int index = findVehicle(slots, count, plate);
    if (index < 0) {
        printf("Khong tim thay xe trong bai.\n");
        return;
    }
    time_t exitTime = time(NULL);
    double seconds = difftime(exitTime, slots[index].entryTime);
    long fee = calculateFee(slots[index].entryTime, exitTime, slots[index].vehicleType);
    if (fee < 0) {
        printf("Loi moc thoi gian, khong the tinh phi.\n");
        return;
    }
    showDateTime(slots[index].entryTime, in, sizeof(in));
    showDateTime(exitTime, out, sizeof(out));
    ParkingRecord record;
    snprintf(record.plate, sizeof(record.plate), "%s", slots[index].plate);
    record.slotId = slots[index].id;
    snprintf(record.vehicleType, sizeof(record.vehicleType), "%s", slots[index].vehicleType);
    record.entryTime = slots[index].entryTime;
    record.exitTime = exitTime;
    record.durationHours = seconds / 3600.0;
    record.fee = fee;

    printf("\nBien so: %s | Vi tri: P%02d\n", record.plate, record.slotId);
    printf("Gio vao: %s\nGio ra: %s\n", in, out);
    printf("Thoi gian gui: %.2f gio\nPhi gui: %ld VND\n", record.durationHours, record.fee);
    if (!appendHistory(&record)) {
        printf("Khong luu duoc lich su; giu nguyen trang thai xe de tranh mat du lieu.\n");
        return;
    }
    slots[index].occupied = 0;
    slots[index].plate[0] = '\0';
    slots[index].vehicleType[0] = '\0';
    slots[index].entryTime = 0;
    saveActiveVehicles(slots, count);
    printf("Da ghi lich su va giai phong vi tri.\n");
}

void searchVehicle(const ParkingSlot slots[], int count) {
    char plate[PLATE_LEN];
    if (!readLine("Nhap bien so can tim: ", plate, sizeof(plate))) return;
    normalizePlate(plate);
    int index = findVehicle((ParkingSlot *)slots, count, plate);
    if (index < 0) printf("Khong tim thay xe.\n");
    else {
        char t[32];
        showDateTime(slots[index].entryTime, t, sizeof(t));
        printf("Tim thay: %s tai P%02d, loai %s, vao luc %s\n",
               slots[index].plate, slots[index].id, slots[index].vehicleType, t);
    }
}
