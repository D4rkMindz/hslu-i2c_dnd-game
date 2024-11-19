#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <sys/wait.h>

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

void sleep_ms(int ms) {
#ifdef _WIN32
    Sleep(ms);
#else
    usleep(ms * 1000); /* sleep for 100 milliSeconds */
#endif
}

void get_input(const char *format, void *variable) {
    scanf(format, variable);
    char c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void fancy_print(const char *str, ...) {
    char buffer[1024]; // Buffer to hold the formatted string.
    va_list args;

    va_start(args, str);
    vsnprintf(buffer, sizeof(buffer), str, args); // Format the string safely.
    va_end(args);

    const char *text = buffer;

    while (*text != '\0') {
        if (*text == '\r') {
            int input = getchar();
            while (input != 10) {
                input = getchar();
                printf("waiting\n");
                // do nothing
            }
            text++;
        } else {
            putchar(*text);
            fflush(stdout);
        }
        sleep_ms(pollingDelay);
        text++;
    }
}
