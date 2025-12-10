#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "utils.h"

void pauseScreen() {
    printf("\nTekan ENTER untuk melanjutkan...");
    getchar(); getchar();
}

void clearScreen() {
    system("cls"); // Windows
}

void trim(char *str) {
    size_t len = strlen(str);
    while (len > 0 && (str[len - 1] == '\n')) {
        str[len - 1] = '\0';
        len--;
    }
}

void protectFolder() {
    struct stat st = {0};
    if (stat("db", &st) == -1) {
        system("mkdir db");
    }
}
