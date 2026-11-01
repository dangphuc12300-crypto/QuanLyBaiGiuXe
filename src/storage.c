#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parking.h"

int saveActiveVehicles(const ParkingSlot slots[], int count) {
    FILE *fp = fopen(DATA_FILE, "w");
    if (!fp) return 0;
    for (int i = 0; i < count; ++i) {
        if (slots[i].occupied)
            fprintf(fp, "%d,%s,%s,%lld\n", slots[i].id, slots[i].plate,
                    slots[i].vehicleType, (long long)slots[i].entryTime);
    }
    fclose(fp);
    return 1;
}

int loadActiveVehicles(ParkingSlot slots[], int count) {
    FILE *fp = fopen(DATA_FILE, "r");
    if (!fp) return 1;
    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        int id;
        char plate[PLATE_LEN], type[12];
        long long entry;
        if (sscanf(line, "%d,%19[^,],%11[^,],%lld", &id, plate, type, &entry) == 4) {
            if (id >= 1 && id <= count && !slots[id-1].occupied) {
                slots[id-1].occupied = 1;
                snprintf(slots[id-1].plate, PLATE_LEN, "%s", plate);
                snprintf(slots[id-1].vehicleType, sizeof(slots[id-1].vehicleType), "%s", type);
                slots[id-1].entryTime = (time_t)entry;
            }
        }
    }
    fclose(fp);
    return 1;
}

int appendHistory(const ParkingRecord *r) {
    FILE *fp = fopen(HISTORY_FILE, "a");
    if (!fp) return 0;
    fseek(fp, 0, SEEK_END);
    if (ftell(fp) == 0)
        fprintf(fp, "bien_so,ma_o,loai_xe,gio_vao,gio_ra,so_gio,phi_vnd\n");
    char in[32], out[32];
    struct tm *tmIn = localtime(&r->entryTime);
    if (tmIn) strftime(in, sizeof(in), "%Y-%m-%d %H:%M:%S", tmIn);
    else snprintf(in, sizeof(in), "unknown");
    struct tm *tmOut = localtime(&r->exitTime);
    if (tmOut) strftime(out, sizeof(out), "%Y-%m-%d %H:%M:%S", tmOut);
    else snprintf(out, sizeof(out), "unknown");
    fprintf(fp, "%s,%d,%s,%s,%s,%.2f,%ld\n", r->plate, r->slotId,
            r->vehicleType, in, out, r->durationHours, r->fee);
    fclose(fp);
    return 1;
}

void showHistory(void) {
    FILE *fp = fopen(HISTORY_FILE, "r");
    if (!fp) {
        printf("Chua co lich su hoac khong mo duoc file.\n");
        return;
    }
    char line[256];
    printf("\n--- LICH SU GUI XE ---\n");
    while (fgets(line, sizeof(line), fp)) printf("%s", line);
    fclose(fp);
}
