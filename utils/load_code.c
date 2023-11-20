#include <stdio.h>
#include <stdlib.h>

// Function to load source code from file (filename.wl)
char *get_source_code(const char *filename)
{
    FILE *filePointer;
    char *buffer;
    long fileSize;
    size_t result;

    // Open file in read mode
    filePointer = fopen(filename, "rb");
    if (filePointer == NULL)
    {
        printf("File could not be opened.");
        return NULL;
    }

    // Get file size
    fseek(filePointer, 0, SEEK_END);
    fileSize = ftell(filePointer);
    rewind(filePointer);

    // Allocate memory to store the file content
    buffer = (char *)malloc((fileSize + 1) * sizeof(char));
    if (buffer == NULL)
    {
        printf("Memory allocation failed.");
        fclose(filePointer);
        return NULL;
    }

    // Read file content into buffer
    result = fread(buffer, sizeof(char), fileSize, filePointer);
    if (result != fileSize)
    {
        printf("Reading file failed.");
        fclose(filePointer);
        free(buffer);
        return NULL;
    }

    // Add null terminator to indicate end of string
    buffer[fileSize] = '\0';

    // Close the file
    fclose(filePointer);

    return buffer;
}