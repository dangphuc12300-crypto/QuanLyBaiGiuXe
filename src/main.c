#include <stdio.h>
#include <stdlib.h>
#include "parking.h"

#define SLOT_COUNT 12

void printMenu(void) {
    printf("\n====================================\n");
    printf("       QUAN LY BAI GIU XE\n");
    printf("====================================\n");
    printf("1. Xe vao bai\n");
    printf("2. Xe ra bai / tinh phi\n");
    printf("3. Hien thi so do bai xe\n");
    printf("4. Tim kiem xe dang gui\n");
    printf("5. Xem lich su gui xe\n");
    printf("6. Thong ke doanh thu\n");
    printf("0. Luu va thoat\n");
    printf("====================================\n");
    printf("Nhap lua chon: ");
}

int main(void) {
    ParkingSlot slots[SLOT_COUNT];
    char input[32];
    int choice;
    initParking(slots, SLOT_COUNT);
    if (!loadActiveVehicles(slots, SLOT_COUNT))
        printf("Canh bao: khong doc duoc du lieu xe dang gui.\n");

    do {
        printMenu();
        if (!fgets(input, sizeof(input), stdin)) break;
        if (sscanf(input, "%d", &choice) != 1) {
            printf("Lua chon khong hop le.\n");
            continue;
        }
        switch (choice) {
            case 1: processEntry(slots, SLOT_COUNT); break;
            case 2: processExit(slots, SLOT_COUNT); break;
            case 3: showParkingMap(slots, SLOT_COUNT); break;
            case 4: searchVehicle(slots, SLOT_COUNT); break;
            case 5: showHistory(); break;
            case 6: showStatistics(); break;
            case 0:
                saveActiveVehicles(slots, SLOT_COUNT);
                printf("Da luu du lieu. Tam biet!\n");
                break;
            default: printf("Vui long chon tu 0 den 6.\n");
        }
    } while (choice != 0);
    return 0;
}
