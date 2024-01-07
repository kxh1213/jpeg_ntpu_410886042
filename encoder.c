#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void usage(FILE *fp){
    fprintf(fp, "encoder 0 input.bmp R.txt G.txt B.txt\n");
    return;
}

int demo0(char *fn_bmp, char *fn_R, char *fn_G, char *fn_B, char *fn_dim){
    return 1;
}

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

void extractRGB(char *bmpFileName, char *rFileName, char *gFileName, char *bFileName, char *dimFileName) {
    FILE *bmpFile = fopen(bmpFileName, "rb");
    FILE *rFile = fopen(rFileName, "w");
    FILE *gFile = fopen(gFileName, "w");
    FILE *bFile = fopen(bFileName, "w");
    FILE *dimFile = fopen(dimFileName, "w");

    if (!bmpFile || !rFile || !gFile || !bFile || !dimFile) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    BMPHeader header;
    fread(&header, sizeof(BMPHeader), 1, bmpFile);

    int width = header.width;
    int height = header.height;
    fprintf(dimFile, "%d %d\n", width, height);

    fseek(bmpFile, header.dataOffset, SEEK_SET);
    /*使用 fseek 將檔案指標移動到BMP檔案中像素資料的開始位置header.dataOffset 
    儲存了像素資料相對於檔案開頭的偏移量，程式可以直接設定檔案指標到該位置以讀取像素資料*/

    int padding = (4 - (width * sizeof(unsigned char) * 3) % 4) % 4; 
    /*計算padding的變數，在BMP檔案中，每一行的像素資料都以4的倍數結尾，來確保資料在內存中會對齊，
    padding表示需要在每一行結尾填充的位元數組以滿足對齊條件。*/


    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            unsigned char pixel[3];
            fread(&pixel, sizeof(unsigned char), 3, bmpFile);

            fprintf(rFile, "%d ", pixel[2]);
            fprintf(gFile, "%d ", pixel[1]);
            fprintf(bFile, "%d ", pixel[0]);
        }

        fseek(bmpFile, padding, SEEK_CUR);
        fprintf(rFile, "\n");
        fprintf(gFile, "\n");
        fprintf(bFile, "\n");
    }

    fclose(bmpFile);
    fclose(rFile);
    fclose(gFile);
    fclose(bFile);
    fclose(dimFile);
}
/*讀取RGB值並將其寫入對應的輸出文件中，紅色寫入rFile 綠色寫入gFile 藍色寫入bFile，
RGB值寫入文件後，使用fseek將檔案指標移動到填充的位置。
關閉所有打開的檔案（）BMP檔案及輸出文件？*/


int main(int argc, char *argv[]) {

    int option = 0;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <bmpFileName>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    option = atoi(argv[1]);

    switch(option){
        case 0:
        demo0(argv[2], argv[3], argv[4], argv[5], argv[6]);
        break;
        case 1:
        break;
    }

    

    char *bmpFileName = argv[1];
    char rFileName[20] = "R.txt";
    char gFileName[20] = "G.txt";
    char bFileName[20] = "B.txt";
    char dimFileName[20] = "dim.txt";

    extractRGB(bmpFileName, rFileName, gFileName, bFileName, dimFileName);

    printf("Extraction completed.\n");

    return 0;

    
}