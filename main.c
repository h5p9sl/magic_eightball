#include <stdio.h>
#include <stdlib.h>

struct StringArray {
    size_t count;
    char* strings[];
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
    }

    fclose(file);
    return strs; 
}

void free_responses(struct StringArray* strs) {
    free(strs);
}

int main() {
    struct StringArray* responses = load_responses("data.txt");
    free_responses(responses);
    return 0;
}
