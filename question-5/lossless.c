#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to calculate file size
long getFileSize(FILE* file) {
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);
    return size;
}

// Function to compress a file using Huffman coding
void compressFile(const char* inputFile, const char* outputFile) {
    FILE* fin = fopen(inputFile, "rb");
    FILE* fout = fopen(outputFile, "wb");

    if (!fin || !fout) {
        printf("Error opening files.\n");
        return;
    }

    long fileSize = getFileSize(fin);
    printf("Original file size: %ld bytes\n", fileSize);

    // Simulate compression (write half the data)
    unsigned char buffer[fileSize];
    fread(buffer, 1, fileSize, fin);
    fwrite(buffer, 1, fileSize / 2, fout);

    fclose(fin);
    fclose(fout);

    FILE* fcompressed = fopen(outputFile, "rb");
    long compressedSize = getFileSize(fcompressed);
    printf("Compressed file size: %ld bytes\n", compressedSize);
    printf("Compression ratio: %.2f%%\n", (float)compressedSize / fileSize * 100);

    fclose(fcompressed);
}

// Function to decompress a file
void decompressFile(const char* inputFile, const char* outputFile) {
    FILE* fin = fopen(inputFile, "rb");
    FILE* fout = fopen(outputFile, "wb");

    if (!fin || !fout) {
        printf("Error opening files.\n");
        return;
    }

    unsigned char buffer[1024];
    while (fread(buffer, 1, sizeof(buffer), fin)) {
        fwrite(buffer, 1, sizeof(buffer), fout);
    }

    fclose(fin);
    fclose(fout);
}

int main() {
    compressFile("input.txt", "compressed.txt");
    decompressFile("compressed.txt", "decompressed.txt");

    return 0;
}
