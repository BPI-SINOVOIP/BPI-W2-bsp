#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sha256.h"

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
	sha256_context ctx;
	int i, j, tmp;
	FILE *fp;
	unsigned char Message_Digest[32];
	char *src, *ptr;
	unsigned long src_size;
	unsigned int pad_len;
	long num_of_bits;

	if (argc <4) {
#if defined(__CYGWIN__)
		printf("Usage:\n\t./do_sha256.exe <input_file> <output_padding_file> <output_digest>\n\n");
#else
		printf("Usage:\n\t./do_sha256 <input_file> <output_padding_file> <output_digest>\n\n");
#endif
		return 1;
	}
	
	// load input file
	fp = fopen(argv[1], "rb");
	if (fp == NULL) {
		printf("fail to open %s\n", argv[1]);
		return -1;
	}
	
	if (get_size(fp, &src_size)) {
		printf("fail to get size %s\n", argv[1]);
		return -1;
	}
	
	// allocate more than src_size (for later output padding use)
	src = (char *) malloc(src_size);
	fread(src, sizeof(char), src_size, fp);
	fclose(fp);

	// calculate padding length
	pad_len = 1;
	while ((src_size + pad_len) % 64 != 56)
		pad_len++;
	pad_len += 8;
	
	if ((src_size + pad_len) % 64) {
		printf("padding result is not multiple of 512 bit\n");
		return -2;
	}
	
	// set padding bits
	ptr = (char *) malloc(pad_len);
	memset(ptr, 0, pad_len);
	ptr[0] = 1 << 7;
	
	// set length
	num_of_bits = src_size * 8;
	printf("%s length (bit): 0x%lx\n", argv[1], num_of_bits);
	for (i = pad_len - 8, j = 32; j >= 0; j -= 32) {
		tmp = (int) ((long long)num_of_bits >> j);
		ptr[i++] = (tmp >> 24) & 0xff;
		ptr[i++] = (tmp >> 16) & 0xff;
		ptr[i++] = (tmp >> 8) & 0xff;
		ptr[i++] =  tmp & 0xff;
		//printf("%ld >> %d = %d\n", num_of_bits, j, tmp);
	}
	
	
	sha256_starts(&ctx);
	sha256_update(&ctx, (unsigned char *) src, src_size);
        sha256_finish(&ctx, Message_Digest);

       	    printf("sha256 result:\n");
       	    for(i = 0; i < sizeof(Message_Digest) ; ++i) {
       	        printf("%02X ", Message_Digest[i]);
       	    }
       	    printf("\n");

	// write padding result
	fp = fopen(argv[2], "wb");
	if (fp == NULL) {
		printf("fail to open %s\n", argv[2]);
		return -1;
	}
	
	//fwrite(src, sizeof(char), src_size, fp);
	fwrite(ptr, sizeof(char), pad_len, fp);
	fclose(fp);

	// write digest
	fp = fopen(argv[3], "wb");
	if (fp == NULL) {
		printf("fail to open %s\n", argv[3]);
		return -1;
	}
	
	fwrite(Message_Digest, sizeof(char), sizeof(Message_Digest), fp);
	fclose(fp);

	free(src);
	free(ptr);
	return 0;
}
