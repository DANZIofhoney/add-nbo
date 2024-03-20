#define _CRT_SECURE_NO_WARNINGS
#include <stddef.h> // for size_t
#include <stdint.h> // for uint8_t 이런걸 외워둬야한다고 말씀을 하시는 교수님
#include <stdio.h> // for printf

uint32_t bigEndian(uint32_t num);

int main(int argc, char* argv[])
{
    if (argc == 3) //main
    {
        FILE* fp1, * fp2;
        fp1 = fopen(argv[1], "rb");
        fp2 = fopen(argv[2], "rb");

        uint32_t binfile1, binfile2;
        fread(&binfile1, 4, 1, fp1);
        fread(&binfile2, 4, 1, fp2);

        binfile1 = bigEndian(binfile1);
        binfile2 = bigEndian(binfile2);

        printf("%d(0x%x) + %d(0x%x) = %d(0x%x)", binfile1, binfile1, binfile2, binfile2, binfile1 + binfile2, binfile1 + binfile2);

        fclose(fp1);
        fclose(fp2);
    }
    else { //ERROR
        printf("./add-nbo {binfile1.bin} {binfile2.bin}");
    }

    return 0;
}

uint32_t bigEndian(uint32_t num) {
    //4byte into 1byte
    uint32_t first_byte = (num & 0xff000000) >> 24;
    uint32_t second_byte = (num & 0x00ff0000) >> 8;
    uint32_t third_byte = (num & 0x0000ff00) << 8;
    uint32_t fourth_byte = (num & 0x000000ff) << 24;
    
    uint32_t total = first_byte | second_byte | third_byte | fourth_byte;
    return total;
}
