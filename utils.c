#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

char *to_lower_string(char *str) {
    for (char *p = str; *p; p++) *p = tolower(*p);
    return str;
}

_Bool equals(char *command, char *check) {
    to_lower_string(command);
    return strcmp(command, check) == 0;
}

void fancy_print(char *str) {
    int i = 0;
    while (str[i] != '\0') {
        printf("%c", str[i]);
        fflush(stdout);
        usleep(50*1000);
        i++;
        if (str[i] == '\n') {
            while (getchar() != '\n') continue;
        }
    }
}
