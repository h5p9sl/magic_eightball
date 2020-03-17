#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct StringArray {
    size_t count;
    char** strings;
};

struct StringArray* load_responses(const char* file_name) {
    struct StringArray* strs = (struct StringArray*)
            malloc(sizeof(struct StringArray));
    FILE* file = fopen(file_name, "r");

    size_t file_len = 0l;
    char* buf = NULL;

    if (file) {
        // Get file length
        fseek(file, 0, SEEK_END);
        file_len = ftell(file);
        rewind(file);
        // Read all the file data into a buffer
        buf = (char*)malloc(file_len);
        fread(buf, 1, file_len, file);
    } else {
        fprintf(stderr, "Unable to find file: %s", file_name);
        exit(1);
    }

    if (buf) {
        strs->count = 0;
        // Iterate through file
        for (int i = 0; i < file_len; i++) {
            // Count number of newlines
            if (buf[i] == '\n') {
                buf[i] = '\0';
                strs->count++;
            }
        }
        // Allocate buffer of string-pointers
        strs->strings = (char**)malloc(sizeof(char*) * strs->count);
        // Assign pointers
        int j = 0;
        strs->strings[j++] = &buf[0];
        for (int i = 1; i < file_len; i++) {
            if (buf[i - 1] == '\0') {
                strs->strings[j++] = &buf[i];
            }
        }
    }

    fclose(file);
    return strs; 
}

void free_responses(struct StringArray* strs) {
    free(strs->strings);
    free(strs);
}

int main() {
    struct StringArray* responses = load_responses("data.txt");
    char* buf = (char*)alloca(64 * sizeof(char));

    srand(time(NULL));

    while (1) {
        // Get input from the user
        printf("Please ask a question\n> ");
        fgets(buf, 64, stdin);

        // Print out a random response
        puts(responses->strings[rand() % responses->count - 1]);
    }

    free_responses(responses);
    return 0;
}
