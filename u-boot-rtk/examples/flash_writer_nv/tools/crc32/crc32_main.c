#include <stdio.h>
#include <stdlib.h>


extern unsigned int crc32(
    unsigned char  *p,
    int	   len,
    unsigned int *crc );


static int get_size(FILE *fp, unsigned long *size)
{
        if (fp == NULL)
                return -1;

        fseek(fp, 0, SEEK_END);
        *size = ftell(fp);
        rewind(fp);
        return 0;
}

int main(int argc, char **argv)
{
	char *filename;
	FILE *fp;
	int res;
	unsigned long length;
	unsigned int checksum;
	unsigned char *buf;
	
	if (argc != 2) {
		return 0;
	}
	
	filename = argv[1];
	if ((fp = fopen(filename, "rb")) == NULL) {
		return -1;
	}
	
	if (get_size(fp, &length)) {
		res = -1;
		goto finally;
	}

	if ((buf = malloc(length)) == NULL) {
		res = -2;
		goto finally;
	}
	
	fread(buf, sizeof(char), length, fp);
	crc32(buf, (unsigned int)length, &checksum);
	printf("%x\n", checksum);
	res = 0;

finally:	
	if (fp != NULL)
		fclose(fp);
	return res;
}
