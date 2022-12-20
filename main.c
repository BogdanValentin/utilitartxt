#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void errorFile(char fileName[]);

void errorSyntax();

void help();

void printFile(char fileName[]);

void charNumberFile(char fileName[]);

void wordCount(char fileName[]);

void lineCount(char fileName[]);

int main(int argc, char *argv[]) {
    if (strcmp(argv[1], "-h") == 0) {
        help();
    } else if (argc < 3) {
        errorSyntax();
    } else {
        if (strcmp(argv[1], "-r") == 0) {
            printFile(argv[2]);
        } else if (strcmp(argv[1], "-d") == 0) {
            charNumberFile(argv[2]);
        } else if (strcmp(argv[1], "-wc") == 0) {
            wordCount(argv[2]);
        } else if (strcmp(argv[1], "-lc") == 0) {
            lineCount(argv[2]);
        }
    }
    return 0;
}

void errorFile(char fileName[]) {
    printf("Error opening %s!", fileName);
    exit(1);
}

void errorSyntax() {
    printf("Syntax error!\nUse -h for help");
}

void help() {
    printf("Arguments:\n"
           "-h : Help\n"
           "-r <file>: Prints the contents of <file>\n"
           "-d <file>: Prints the number of characters, vowels, consonants and digits of <file>\n"
           "-wc <file>: Prints the number of words in <file>\n"
           "-wl <file>: Prints the number of lines in <file>");
}

void printFile(char fileName[]) {
    FILE *file = fopen(fileName, "rt");
    if (file == NULL) {
        errorFile(fileName);
    }
    char character;
    while (fscanf(file, "%c", &character) == 1) {
        printf("%c", character);
    }
    fclose(file);
}

void charNumberFile(char fileName[]) {
    FILE *file = fopen(fileName, "rt");
    if (file == NULL) {
        errorFile(fileName);
    }
    char character;
    long long charNumber = 0, vowelNumber = 0, consonantNumber = 0, digitNumber = 0;
    while (fscanf(file, "%c", &character) == 1) {
        if (character != '\n') {
            charNumber++;
        }
        if (strchr("aeiouAEIOU", character) != NULL) {
            vowelNumber++;
        } else if (strchr("bcdfghjklmnpqrstvwxyzBCDFGHJKLMNPQRSTVWXYZ", character) != NULL) {
            consonantNumber++;
        } else if (strchr("0123456789", character) != NULL) {
            digitNumber++;
        }
    }
    fclose(file);
    printf("File %s contains:\n%lld character", fileName, charNumber);
    if (charNumber != 1) {
        printf("s");
    }
    printf("\n%lld vowel", vowelNumber);
    if (vowelNumber != 1) {
        printf("s");
    }
    printf("\n%lld consonant", consonantNumber);
    if (consonantNumber != 1) {
        printf("s");
    }
    printf("\n%lld digit", digitNumber);
    if (digitNumber != 1) {
        printf("s");
    }
}

void wordCount(char fileName[]) {
    FILE *file = fopen(fileName, "rt");
    if (file == NULL) {
        errorFile(fileName);
    }
    long long wCount = 0;
    int isWord = 0;
    char character;
    while (fscanf(file, "%c", &character) == 1) {
        if (character == ' ' || character == '\n') {
            isWord = 0;
        } else {
            if (!isWord) {
                wCount++;
                isWord = 1;
            }
        }
    }
    fclose(file);
    printf("File %s contains %lld word", fileName, wCount);
    if (wCount != 1) {
        printf("s");
    }
}

void lineCount(char fileName[]) {
    FILE *file = fopen(fileName, "rt");
    if (file == NULL) {
        errorFile(fileName);
    }
    char character;
    long long lCount = 0;
    if (fscanf(file, "%c", &character) == 1) {
        lCount++;
        while (fscanf(file, "%c", &character) == 1) {
            if (character == '\n') {
                lCount++;
            }
        }
    }
    fclose(file);
    printf("File %s contains %lld line", fileName, lCount);
    if (lCount != 1) {
        printf("s");
    }
}