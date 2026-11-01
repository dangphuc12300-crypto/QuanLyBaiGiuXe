#include <stdio.h>
#include <time.h>
#include <string.h>
#include "parking.h"

void showDateTime(time_t value, char *buffer, size_t size) {
    struct tm *local = localtime(&value);
    if (local == NULL) {
        snprintf(buffer, size, "Khong xac dinh");
        return;
    }
    strftime(buffer, size, "%d/%m/%Y %H:%M:%S", local);
}

/* Bang gia minh hoa: xe may 5.000d/gio, o to 20.000d/gio.
   Lam tron len theo gio; toi thieu 1 gio. */
long calculateFee(time_t entry, time_t exit, const char *vehicleType) {
    double seconds = difftime(exit, entry);
    if (seconds < 0) return -1;
    long hours = (long)(seconds / 3600.0);
    if (seconds > hours * 3600.0) hours++;
    if (hours < 1) hours = 1;

    if (strcmp(vehicleType, "OTO") == 0) return hours * 20000L;
    return hours * 5000L;
}
