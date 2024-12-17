//
// Created by Björn Pfoster on 15.12.2024.
//

#ifndef FILE_PARSING_H
#define FILE_PARSING_H
#include "../lib/cJSON.h"

cJSON *read_file_json(const char *path);

void write_file_json(const char *path, cJSON *json);

cJSON *read_array(cJSON *root, const char *path);

int read_int(cJSON *json, const char *path);

char *read_string(cJSON *json, const char *path);

_Bool read_bool(cJSON *json, const char *path);

char *read_array_item_string(cJSON *json, int index);

void reset();

#endif //FILE_PARSING_H
