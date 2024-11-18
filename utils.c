#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

signed int pollingDelay = 10; // in miliseconds

char *to_lower_string(char *str) {
    for (char *p = str; *p; p++) *p = tolower(*p);
    return str;
}

_Bool equals(char *command, char *check) {
    to_lower_string(command);
    return strcmp(command, check) == 0;
}

void fancy_print(const char *str, ...) {
    char buffer[1024]; // Buffer to hold the formatted string.
    va_list args;

    va_start(args, str);
    vsnprintf(buffer, sizeof(buffer), str, args); // Format the string safely.
    va_end(args);

    const char *text = buffer;


    while (*text != '\0') {
        putchar(*text);
        fflush(stdout);
        if (*text == '\n') {
            while (getchar() != '\n');
        }
#ifdef _WIN32
        Sleep(pollingDelay);
#else
        usleep(pollingDelay * 1000); /* sleep for 100 milliSeconds */
#endif
        text++;
    }
}
