#include <stdio.h>
#include <stdlib.h>

char *read_text_file(const char *filename)
{
    FILE *fp;
    long file_size;
    char *buffer;

    if (filename == NULL)
        return NULL;

    fp = fopen(filename, "rb");
    if (fp == NULL)
        return NULL;

    /* Determine file size */
    if (fseek(fp, 0, SEEK_END) != 0) {
        fclose(fp);
        return NULL;
    }

    file_size = ftell(fp);
    if (file_size < 0) {
        fclose(fp);
        return NULL;
    }

    rewind(fp);

    /* Allocate buffer (+1 for terminating '\0') */
    buffer = malloc((size_t)file_size + 1);
    if (buffer == NULL) {
        fclose(fp);
        return NULL;
    }

    /* Read entire file */
    if (fread(buffer, 1, (size_t)file_size, fp) != (size_t)file_size) {
        free(buffer);
        fclose(fp);
        return NULL;
    }

    buffer[file_size] = '\0';

    fclose(fp);
    return buffer;
}