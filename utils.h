#ifndef UTILS_H
#define UTILS_H

char *to_lower_string(char *str);

_Bool equals(char *command, char *check);

void get_input(const char *format, void *variable);

void sleep_ms(int ms);

void fancy_print(char *str, ...);
#endif // UTILS_H
