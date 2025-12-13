#ifndef UTILS_H
#define UTILS_H

void pauseScreen();
void clearScreen();
void trim(char *str);
void protectFolder();

/* INPUT AMAN */
int inputInt(const char *label);
void inputString(const char *label, char *buffer, int size);

#endif
