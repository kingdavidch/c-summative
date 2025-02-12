// (Note: Huffman coding requires extensive code. Below is a simplified structure.)
#include <stdio.h>
#include <stdlib.h>

// Implement Huffman tree, frequency table, and bitwise I/O here

void compress(const char *inputFile, const char *outputFile) {
    printf("Compressing %s to %s\n", inputFile, outputFile);
    // Build Huffman tree, write compressed data
}

void decompress(const char *inputFile, const char *outputFile) {
    printf("Decompressing %s to %s\n", inputFile, outputFile);
    // Read Huffman tree, decode data
}

int main() {
    compress("original.txt", "compressed.txt");
    decompress("compressed.txt", "decompressed.txt");
    // Use stat() to compare file sizes
    return 0;
}
