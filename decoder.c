#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma pack(1)
typedef struct {
    char signature[2];
    int fileSize;
    int reserved;
    int dataOffset;
    int headerSize;
    int width;
    int height;
    short planes;
    short bitsPerPixel;
    int compression;
    int imageSize;
    int xPixelsPerMeter;
    int yPixelsPerMeter;
    int colorsUsed;
    int colorsImportant;
} BMPHeader;

void createBMP(char *rFileName, char *gFileName, char *bFileName, char *dimFileName, char *bmpFileName) {
    FILE *rFile = fopen(rFileName, "r");
    FILE *gFile = fopen(gFileName, "r");
    FILE *bFile = fopen(bFileName, "r");
    FILE *dimFile = fopen(dimFileName, "r");
    FILE *bmpFile = fopen(bmpFileName, "wb");