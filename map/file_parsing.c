//
// Created by Björn Pfoster on 15.12.2024.
//

#include "file_parsing.h"

#include <stdbool.h>

#include "../lib/cJSON.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
static char *file_content;
static cJSON *json;
// Helper function to read entire file into a buffer
static char *read_file(const char *path) {
    FILE *f = fopen(path, "rb");
    if (!f) return NULL;

    fseek(f, 0, SEEK_END);
    long length = ftell(f);
    fseek(f, 0, SEEK_SET);

    char *data = (char *) malloc(length + 1);
    if (!data) {
        fclose(f);
        return NULL;
    }
    if (fread(data, 1, length, f) != (size_t) length) {
        fclose(f);
        free(data);
        return NULL;
    }
    data[length] = '\0';
    fclose(f);
    return data;
}

cJSON *read_file_json(const char *path) {
    file_content = read_file(path);
    if (!file_content) {
        return NULL;
    }

    cJSON *json = cJSON_Parse(file_content);
    if (!json) {
        reset();
        return NULL;
    }

    return json;
}

void write_file_json(const char *path, cJSON *json) {
    FILE *f = fopen(path, "w+");
    if (f == NULL) {
        fclose(f);
        return;
    }
    char *content = cJSON_Print(json);
    fputs(content, f);
    fclose(f);
    cJSON_free(content);
    cJSON_Delete(json);
}

cJSON *read_array(cJSON *root, const char *path) {
    cJSON *array = cJSON_GetObjectItemCaseSensitive(root, path);
    if (!array || !cJSON_IsArray(array)) {
        return NULL;
    }
    int roomCount = cJSON_GetArraySize(array);
    if (roomCount <= 0) {
        return NULL;
    }

    return array;
}

cJSON *read_object(cJSON *root, const char *path) {
    cJSON *object = cJSON_GetObjectItemCaseSensitive(root, path);
    if (!object || !cJSON_IsObject(object)) {
        return NULL;
    }
    return object;
}

int read_int(cJSON *json, const char *path) {
    cJSON *item = cJSON_GetObjectItemCaseSensitive(json, path);
    return (item && cJSON_IsNumber(item)) ? item->valueint : -1;
}

char *read_string(cJSON *json, const char *path) {
    cJSON *item = cJSON_GetObjectItemCaseSensitive(json, path);
    if (item && cJSON_IsString(item)) {
        return strdup(item->valuestring);
    }
    return NULL;
}

_Bool read_bool(cJSON *json, const char *path) {
    cJSON *item = cJSON_GetObjectItemCaseSensitive(json, path);
    if (item && cJSON_IsBool(item)) {
        return (_Bool) item->valueint;
    }
    return false;
}

char *read_array_item_string(cJSON *json, int index) {
    cJSON *line = cJSON_GetArrayItem(json, index);
    if (line && cJSON_IsString(line)) {
        return strdup(line->valuestring);
    }
    return NULL;
}

void reset() {
    if (json) {
        cJSON_Delete(json);
    }
    free(file_content);
}
