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

#include "utils.h"

#include <stdbool.h>
#include <stdlib.h>

#include "constants.h"

signed int pollingDelay = 10; // in miliseconds

char *to_lower_string(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        // Convert character to lowercase if it's an uppercase letter
        // If it's not an uppercase letter, tolower() will just return it unchanged
        str[i] = (char) tolower((unsigned char) str[i]);
    }
    return str;
}

_Bool equals(char *command, char *check) {
    if (strlen(command) != strlen(check)) {
        return false;
    }

    char *commandCopy = strdup(command);
    char *checkCopy = strdup(check);
    to_lower_string(commandCopy);
    to_lower_string(checkCopy);
    _Bool result = strcmp(commandCopy, checkCopy) == 0;
    free(commandCopy);
    free(checkCopy);

    return result;
}

_Bool equals_case_insensitive(char *command, char *check) {
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
    while ((c = (char) getchar()) != '\n' && c != EOF);
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
    if (DEBUG) {
        printf("%s", text);
        // reset the buffer
        memset(buffer, 0, sizeof(buffer));
        return;
    }

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

// RoomStack Implementation

// Initialize the stack
void initStack(RoomStack *stack) {
    stack->top = -1;
}

// Check if the stack is empty
_Bool isEmpty(RoomStack *stack) {
    return stack->top == -1;
}

// Push an element onto the stack
_Bool push(RoomStack *stack, int roomID) {
    if (stack->top < MAX_STACK_SIZE - 1) {
        stack->data[++stack->top] = roomID;
        return 1;
    }
    return 0; // Stack overflow
}

// Pop an element from the stack
int pop(RoomStack *stack) {
    if (!isEmpty(stack)) {
        return stack->data[stack->top--];
    }
    return -1; // Stack underflow (no previous room)
}

// Peek at the top of the stack
int peek(RoomStack *stack) {
    if (!isEmpty(stack)) {
        return stack->data[stack->top];
    }
    return -1; // Stack underflow
}
