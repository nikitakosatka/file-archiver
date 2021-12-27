#include "utils.h"

long int getSize(FILE *filePointer) {
    fseek(filePointer, 0L, SEEK_END);
    long int res = ftell(filePointer);
    rewind(filePointer);

    return res;
}

void create(int filesCount, FILE **files, char **filenames, char *filename) {
    FILE *resultFile = fopen(filename, "wb");
    int size;

    fputc(filesCount, resultFile);

    for (int i = 0; i < filesCount; i++) {
        size = (int) getSize(files[i]);

        fputc((int) strlen(filenames[i]), resultFile);

        for (int j = 0; j < strlen(filenames[i]); j++) {
            fputc(filenames[i][j], resultFile);
        }

        fputc(size, resultFile);

        for (int j = 0, ch = fgetc(files[i]); j < size && ch != EOF; j++) {
            fputc(ch, resultFile);
            ch = fgetc(files[i]);
        }

        fclose(files[i]);
    }

    fclose(resultFile);
}

void extract(FILE *filePointer) {
    int filesCount = fgetc(filePointer);

    for (int i = 0; i < filesCount; i++) {
        int filenameSize = fgetc(filePointer);
        char *filename = malloc(filenameSize);

        for (int j = 0; j < filenameSize; j++) {
            filename[j] = (char) fgetc(filePointer);
        }

        FILE *extractingFile = fopen(filename, "wb");

        int fileSize = fgetc(filePointer);

        for (int j = 0; j < fileSize; j++) {
            fputc(fgetc(filePointer), extractingFile);
        }

        fclose(extractingFile);
    }

    fclose(filePointer);
}

void printList(FILE *filePointer) {
    int filesCount = fgetc(filePointer);

    printf("Files in archive: %d\n", filesCount);

    for (int i = 0; i < filesCount; i++) {
        int filenameSize = fgetc(filePointer);
        char *filename = malloc(filenameSize);

        for (int j = 0; j < filenameSize; j++) {
            filename[j] = (char) fgetc(filePointer);
        }

        int fileSize = fgetc(filePointer);

        for (int j = 0; j < fileSize; j++) {
            fgetc(filePointer);
        }

        printf("%s\t%d bytes\n", filename, fileSize);
    }

    fclose(filePointer);
}