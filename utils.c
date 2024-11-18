#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>

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
        usleep(10 * 1000); // 10k nanoseconds = 10 miliseconds
        text++;
    }
}
