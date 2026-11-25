// This is a test file for JSON operations

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <read-text.h>
#include <cJSON.h>

int main() {
    // Read the JSON file into a string
    char *json_string = read_text_file("mode-library.json");
    if (json_string == NULL) {
        fprintf(stderr, "Failed to read JSON file.\n");
        return 1;
    }

    // Parse the JSON string
    cJSON *json = cJSON_Parse(json_string);
    if (json == NULL) {
        fprintf(stderr, "Failed to parse JSON.\n");
        free(json_string);
        return 1;
    }

    // Print the JSON object as a string
    char *print_string = cJSON_Print(json);
    if (print_string == NULL) {
        fprintf(stderr, "Failed to print JSON.\n");
        cJSON_Delete(json);
        free(json_string);
        return 1;
    }

    fprintf(stdout, "Parsed JSON:\n%s\n", print_string);

    // Don't forget to free the allocated memory
    free(json_string);
    free(print_string);
    cJSON_Delete(json);

    return 0;
}
