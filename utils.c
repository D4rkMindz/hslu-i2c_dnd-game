#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <sys/time.h>

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

long _microtime() {
    struct timeval currentTime;
    gettimeofday(&currentTime, NULL);
    return currentTime.tv_sec * (int) 1e6 + currentTime.tv_usec;
}

void fancy_print(const char *str, ...) {
    char buffer[1024]; // Buffer to hold the formatted string.
    va_list args;

    va_start(args, str);
    // format the string safely.
    vsnprintf(buffer, sizeof(buffer), str, args);
    va_end(args);

    const char *text = buffer;
    while (*text != '\0') {
        if (*text == '\r') {
            long now = _microtime();
            long after = _microtime();
            int c = 0;
            // if the reaction time is less than 100ms,
            // the input is actually from the buffer
            while (c != '\n' || after - now < 100) {
                c = getchar();
                after = _microtime();
            }
            // prevent the carriage return's "\n" from being printed
            text++;
        } else {
            // prevent output of \r
            putchar(*text);
            fflush(stdout);
        }
        sleep_ms(pollingDelay);
        fflush(stdout);
        text++;
    }


    // reset the buffer
    memset(buffer, 0, sizeof(buffer));
}
