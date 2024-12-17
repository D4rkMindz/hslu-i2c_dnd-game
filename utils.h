#ifndef UTILS_H
#define UTILS_H

char *to_lower_string(char *p);

_Bool equals(char *command, char *check);

_Bool equals_case_insensitive(char *command, char *check);

void get_input(const char *format, void *variable);

void sleep_ms(int ms);

void fancy_print(const char *str, ...);

// Define the stack for room history
#define MAX_STACK_SIZE 100

typedef struct {
    int data[MAX_STACK_SIZE];
    int top;
} RoomStack;

// Stack functions
void initStack(RoomStack *stack);

_Bool isEmpty(RoomStack *stack);

_Bool push(RoomStack *stack, int room);

int pop(RoomStack *stack);

int peek(RoomStack *stack);

long _microtime();

#endif
