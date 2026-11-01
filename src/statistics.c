#include <stdio.h>
#include <string.h>
#include <time.h>
#include "parking.h"

void showStatistics(void) {
    FILE *fp = fopen(HISTORY_FILE, "r");
    if (!fp) {
        printf("Chua co du lieu thong ke.\n");
        return;
    }
    char line[256];
    int count = 0;
    long total = 0;
    if (fgets(line, sizeof(line), fp) == NULL) { fclose(fp); return; }
    while (fgets(line, sizeof(line), fp)) {
        char plate[PLATE_LEN], type[12], in[32], out[32];
        int slot;
        double hours;
        long fee;
        if (sscanf(line, "%19[^,],%d,%11[^,],%31[^,],%31[^,],%lf,%ld",
                   plate, &slot, type, in, out, &hours, &fee) == 7) {
            count++;
            total += fee;
        }
    }
    fclose(fp);
    printf("\n--- THONG KE LICH SU ---\n");
    printf("So luot xe da hoan tat: %d\n", count);
    printf("Tong doanh thu: %ld VND\n", total);
    printf("Luu y: day la thong ke tong tu file lich su, chua loc theo ngay/ca.\n");
}
