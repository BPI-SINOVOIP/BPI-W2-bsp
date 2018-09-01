#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "vo_reg.h"
#include "SpuGen.h"
#include "logo.h"


#define DEFAULT_LOGO_BIN_FILE_NTSC	"logo_ntsc.bin"
#define DEFAULT_LOGO_BIN_FILE_PAL	"logo_pal.bin"

#define ENABLE_LOGO_LOADER
#ifdef ENABLE_LOGO_LOADER

#ifndef COUNT
#define COUNT(array)	sizeof(array)/sizeof(array[0])
#endif /* COUNT */

/*
flash_info_t pvr_box_flash_info_test = {
	.device_path	= "./flashdev",
	.logo_offset	= 0x0000d000,
	.logo_len	= 0,
	.param_offset	= 0x0000ff00,
	.param_len	= 0,
};
*/

/* PVR-BOX PAL(720x576) logo. */
/*
logo_info_t pvr_box_logo_info_pal = {
	.logo_type	= LOGO_PAL,
	.width		= 720,
	.height		= 576,
	.flash_info	= &pvr_box_flash_info,
	.dev_mount_dir	= "/mnt/usbmounts",
	.logo_dir	= NULL,
	.logo_bmp_file	= "logo_pal.bmp",
	.logo_bin_file	= DEFAULT_LOGO_BIN_FILE_PAL,
};
*/


#define LOGO_ERR_LOG_FILE	"LOGO_ERR.log"
#ifdef ENABLE_ERR_LOG
# define ERR_LOG(format...)	logo_errlog(__FILE__, __FUNCTION__, __LINE__, format)
#else /* ENABLE_ERR_LOG */
# define ERR_LOG(format...)	printf(format)
#endif /* ENABLE_ERR_LOG */
int logo_errlog(const char *file, const char *function, unsigned int line,
							const char *format, ...) {
	FILE *fp;
	va_list list;

	if((fp = fopen(LOGO_ERR_LOG_FILE, "a")) == NULL) {
		printf("Error open log file!\n");
		return -EINVAL;

	}

	fprintf(fp, "%s:%s(%d), ", file, function, line);

	va_start(list, format);
	printf(format, list);
	vfprintf(fp, format, list);
	va_end(list);

	fclose(fp);

	return 0;
}

/* For logo installer */
unsigned char colordb[4][3];
int colorIndex = 0;

/*
mode : NTSC = 0, PAL = 1
offset : the size of top field (bytes)
color : 
0: background pixel
1: Pattern pixel
2: Emphasis pixel-1
3: Emphasis pixel-2
*/
void VO_setSPArg(logo_info_t *logo_info, int offset, void *color) {
//void VO_setSPArg(int mode, int offset, void *color) {
	//FILE *fp;
	VO_COLOR *sp_color = (VO_COLOR*)color;
	param_info_t *param_info = &logo_info->param_info;
	int i;

	param_info->mode	= logo_info->logo_type;
	param_info->offset	= offset;

	/*
	fp = fopen("VO_UpdateLogo.txt","wt");
	fprintf(fp, "%d, %d\n", param_info->mode , offset );
	*/
	for(i = 0; i < 4; i++, sp_color++) {
		printf("y=%d, cb=%d, cr=%d\n", sp_color->y, sp_color->cb, sp_color->cr);
		/*
		fprintf(fp, "0x%x, 0x%x\n", VO_SPCLUT_0_reg + i * 4,
						(VO_SPCLUT_y(sp_color->y) |
						VO_SPCLUT_cb(sp_color->cb) |
						VO_SPCLUT_cr(sp_color->cr)));
		*/

		param_info->spclut_reg[i] = VO_SPCLUT_0_reg + (i * 4);
		param_info->spclut[i] =
				VO_SPCLUT_y(sp_color->y) |
				VO_SPCLUT_cb(sp_color->cb) |
				VO_SPCLUT_cr(sp_color->cr);
	}

	/*
	fclose(fp);
	*/
}

int RGB2YUV(unsigned char R, unsigned char G, unsigned char B, 
            unsigned char *Y, unsigned char *U, unsigned char *V) {
	if((!Y) || (!U) || (!V)) {
		ERR_LOG("RGB2YUV error!!\n");
		return 0;
	}

	*Y = ( 257*R + 504*G +  98*B)/1000 +  16 ;  /* Y  */
	*U = (-148*R - 291*G + 439*B)/1000 + 128 ;  /* Cb */
	*V = ( 439*R - 368*G -  71*B)/1000 + 128 ;  /* Cr */

	return 1;
}

// return 0 means error
int converTo2Bits(unsigned Y, unsigned U, unsigned V) {
	int i;

	if(colorIndex == 0) {
		colordb[0][0] = Y;
		colordb[0][1] = U;
		colordb[0][2] = V;
		colorIndex++;
		return colorIndex;
	}

	for(i = 0; i < colorIndex; i++) {
		if ((colordb[i][0] == Y) && (colordb[i][1] == U) && (colordb[i][2] == V)) 
			return (i+1);
	}

	// not match in colordb, create new entry
	if(colorIndex == 4) {
		ERR_LOG("Error! exceed 4 kind of colors!!!!\n");
		return 0;
	}

	colordb[colorIndex][0] = Y;
	colordb[colorIndex][1] = U;
	colordb[colorIndex][2] = V;
	colorIndex++;

	return colorIndex;
}

int transfer_bmp_image(logo_info_t *logo_info) {
	int i, result, writeByte;
	int imgCount = 0;
	int width = 0;
	int height = 0;
	VO_COLOR voColor[4];
	FILE *ifd = NULL;
	FILE *ofd = NULL;
	unsigned char *RGBBuffer;
	unsigned char R, G, B, Y, U, V;
	unsigned char *spuPixelImg = NULL;
	unsigned char bmpHeader[54];
	unsigned int spuPixelImgSiz = 0;
	unsigned int RGBBufferSiz = 0;
	unsigned int RGBIndex = 0;
	int BottomOffset = 0;
	struct stat st;
	char param_data[128];
	param_info_t *param_info = &logo_info->param_info;
	int ret;
	int bitspp, ncolors;
	unsigned int clut[256];
	

	if((ret = stat(logo_info->logo_bmp_file, &st)) != 0) {
		ERR_LOG("Can not find bitmap file, %s!\n", logo_info->logo_bmp_file);
		return -EINVAL;
	}

	if((ifd = fopen(logo_info->logo_bmp_file,"rb")) == NULL) {
		ERR_LOG("Bitmap file, %s, open error!\n", logo_info->logo_bmp_file);
		return -EINVAL;
	}

	printf("Bitmap file, %s, open success!\n", logo_info->logo_bmp_file);

	//read BMP24 header (total 54 byte)
	//bmpHeader = (unsigned char *)malloc(54*sizeof(unsigned char));
	memset(bmpHeader, 0, sizeof(bmpHeader));
	if((result = fread(&bmpHeader, 1, 54, ifd)) != 54) {
		ERR_LOG("Read header error for bitmap file, %s!\n", logo_info->logo_bmp_file);
		fclose(ifd);
		return -EINVAL;
	}

	if((bmpHeader[0] != 0x42) || (bmpHeader[1] != 0x4D)) {
		ERR_LOG("This is not a BMP file! \n");
		fclose(ifd);
		return -EINVAL;
	}

	switch (bmpHeader[0x1c]) {
		case 4:
		case 24:
		break;
		default:
			ERR_LOG("We only support 4 or 24 bits per pixel right now! \n");
			fclose(ifd);
		return -EINVAL;
	}

	/* PHOTOSHOP seems have bug in this field. */
	if((bmpHeader[18] == 0xD0) && (bmpHeader[19] == 0x02) && (bmpHeader[22] == 0x40) && (bmpHeader[23] == 0x02)) {
		printf("Logo Type: PAL.\n");
		logo_info->logo_type = LOGO_PAL;
		width = 720;
		height = 576;
	} else if((bmpHeader[18] == 0xD0) && (bmpHeader[19] == 0x02) && (bmpHeader[22] == 0xE0) && (bmpHeader[23] == 0x01)) {
		printf("Logo Type: NTSC.\n");
		logo_info->logo_type = LOGO_NTSC;
		width = 720;
		height = 480;
	} else if((bmpHeader[18] == 0x80) && (bmpHeader[19] == 0x07) && (bmpHeader[22] == 0x38) && (bmpHeader[23] == 0x04)) {
		printf("Logo Type: 1080.\n");
		logo_info->logo_type = LOGO_1080;
		width = 1920;
		height = 1080;
	} else {
		ERR_LOG("Unacceptable BMP's format! It must be 720x480 or 720x576 or 1920x1080. (bmpHeader[18]=0x%x, bmpHeader[19]=0x%x, bmpHeader[22]=0x%x, bmpHeader[23]=0x%x\n",	bmpHeader[18], bmpHeader[19], bmpHeader[22], bmpHeader[23]);
		fclose(ifd);
		return -EINVAL;
	}

	bitspp = *((short*)&bmpHeader[0x1c]);
	ncolors = *((int*)&bmpHeader[0x2e]);

	RGBBufferSiz = (width*height)*3;
	if((RGBBuffer = (unsigned char*)malloc(RGBBufferSiz)) == NULL) {
		ERR_LOG("Can not allocate memory for RGBBuffer!\n");
		fclose(ifd);
		return -EINVAL;
	}
	memset(RGBBuffer, 0, RGBBufferSiz);

	if(bitspp == 24) {
	for(i = 0; i < RGBBufferSiz && !feof(ifd); i++) {
		if((ret = fread(&RGBBuffer[i], 1, 1, ifd)) != 1) {
			ERR_LOG("Read bitmap image for RGBBuffer failed!(ret=%d, pos=%d)\n",
									ret, i);
			free(RGBBuffer);
			fclose(ifd);
			return -EINVAL;
		}
	}
	} else {
		unsigned char *buf = calloc(width*height*bitspp/8, 1);
		/* read palette */
		fread(clut, 4, ncolors, ifd);
		/* transfer index to RGB */
		fread(buf, 1, width*height*bitspp/8, ifd);
		for (i=0; i < (width*height); i++) {
			unsigned int rgb;
			unsigned int color_index;

			color_index = buf[i*bitspp/8];
			if(bitspp==4) {
				if(i&1) /* odd */
					color_index &= 0x0f;
				else	/* even */
					color_index >>= 4;
			}

			rgb = clut[color_index];
			RGBBuffer[i*3+2] = (unsigned char)((rgb>>16)&0x0ff);
			RGBBuffer[i*3+1] = (unsigned char)((rgb>>8)&0x0ff);
			RGBBuffer[i*3]   = (unsigned char)(rgb&0x0ff);
		}

		free(buf);
	}

	printf("RGBBufferSiz=%d, i=%d\n", RGBBufferSiz, i);

	fclose(ifd);

	if(logo_info->logo_bin_file == NULL ||
			(ofd = fopen(logo_info->logo_bin_file ,"w+b")) == NULL) {
		ERR_LOG("Output file %s open error\n", logo_info->logo_bin_file);
		free(RGBBuffer);
		return -EINVAL;
	}

	printf("Binary image file, %s, open success!\n", logo_info->logo_bin_file);

	spuPixelImgSiz = (height*width)/4;
	if((spuPixelImg = (unsigned char *)malloc(spuPixelImgSiz)) == NULL) {
		ERR_LOG("Can not allocate memory for spuPixelImg!\n");
		free(RGBBuffer);
		fclose(ofd);
		return -EINVAL;
	}
	memset(spuPixelImg, 0, spuPixelImgSiz);

	for(i = 0; i < (width*height); i++) {
		RGBIndex = width*((height-1)-(i/width))+(i%width);

		if((RGBIndex*3+2) > RGBBufferSiz) {
			ERR_LOG("RGBIndex=%u is too big! (i=%d)\n", RGBIndex, i);
			free(RGBBuffer);
			free(spuPixelImg);
			fclose(ofd);
			return -EINVAL;
		}

		R = RGBBuffer[RGBIndex*3+2];
		G = RGBBuffer[RGBIndex*3+1];
		B = RGBBuffer[RGBIndex*3];

		if(!RGB2YUV(R, G, B, &Y, &U, &V)) {
			ERR_LOG("RGB2YUV error, pos: %d\n", i);
			free(RGBBuffer);
			free(spuPixelImg);
			fclose(ofd);
			return -EINVAL;
		}

		if(!(result = converTo2Bits(Y, U, V))) {
			ERR_LOG("coverTo2Bits error, pos: %d\n", i);
			free(RGBBuffer);
			free(spuPixelImg);
			fclose(ofd);
			return -EINVAL;
		}

		// since 0 means error, so we have to -1
		result--;
		switch(i%4) {
			case 0:
				writeByte = (writeByte & 0x3F) | ((result << 6) & 0xC0);
				break;
			case 1:
				writeByte = (writeByte & 0xCF) | ((result << 4) & 0x30);
				break;
			case 2:
				writeByte = (writeByte & 0xF3) | ((result << 2) & 0x0C);
				break;
			case 3:
				writeByte = (writeByte & 0xFC) | result; 
				break;
		}

		if(i%4 == 3) 
			spuPixelImg[imgCount++] = writeByte;

	}

	BottomOffset = SpuEncode(ofd, spuPixelImg, width, height);

	fclose(ofd);

	printf("\n");
	printf("---------------------------------------\n");
	printf("RLE sub-picture file conver success!\n");
	printf("The Bottom Offset: %d\n", BottomOffset);
	printf("The palette:\n");

	printf("[DEBUG_MSG] colorIndex=%d\n", colorIndex);

	for(i = 0; i< colorIndex; i++) {
		printf("(%d) Y: %d, Cb: %d, Cr: %d\n", i+1, 
				colordb[i][0], colordb[i][1], colordb[i][2]);
		voColor[i].y = colordb[i][0];
		voColor[i].cb = colordb[i][1];
		voColor[i].cr = colordb[i][2];                           
	}
        
	VO_setSPArg(logo_info, BottomOffset, voColor);

	free(RGBBuffer);
	free(spuPixelImg);
    
	if(logo_info->logo_param_file == NULL ||
			(ofd = fopen(logo_info->logo_param_file ,"w+b")) == NULL) {
		ERR_LOG("Output parameter file %s open error\n", logo_info->logo_param_file);
		return -EINVAL;
	}

	memset(param_data, 0, sizeof(param_data));
	param_info = &logo_info->param_info;
	//snprintf(param_data, sizeof(param_data), "-r 0\r\n-e 00.01.02.03.04.05\r\n-l %d %lu 0x%06x 0x%06x 0x%06x 0x%06x\r\n", param_info->mode, param_info->offset, param_info->spclut[0], param_info->spclut[1], param_info->spclut[2], param_info->spclut[3]);
	//snprintf(param_data, sizeof(param_data), "Logo_Type=%s\nLogo_Offset=%lu\nLogo_Reg5370=0x%06x\nLogo_Reg5374=0x%06x\nLogo_Reg5378=0x%06x\nLogo_Reg537c=0x%06x\n", (param_info->mode==LOGO_PAL)?"PAL":"NTSC", param_info->offset, param_info->spclut[0], param_info->spclut[1], param_info->spclut[2], param_info->spclut[3]);
	snprintf(param_data, sizeof(param_data), "Logo_Offset=%lu\nLogo_Reg5370=0x%06x\nLogo_Reg5374=0x%06x\nLogo_Reg5378=0x%06x\nLogo_Reg537c=0x%06x\n", param_info->offset, param_info->spclut[0], param_info->spclut[1], param_info->spclut[2], param_info->spclut[3]);

	if((ret = fwrite(param_data, 1, strlen(param_data), ofd)) != strlen(param_data)) {
		printf("File write error: %s. (%s)\n",
			logo_info->logo_param_file, strerror(errno));
		fclose(ofd);
		return -EINVAL;
	}
	printf("param_data:\n%s\n", param_data);

	fclose(ofd);
	
	printf("bye\n");

	return 0;
}

int main(int argc, char **argv) {
	logo_info_t logo_info;
	int ret;
	int i;

	printf("Logo Changer release date/time: %s %s\n", __DATE__, __TIME__);

	if(argc != 4) {
		fprintf(stderr, "Usage: %s <INPUT_FILE> <OUTPUT_FILE> <OUTPUT_PARAM_FILE>\n", argv[0]);
		return -EINVAL;
	}

	logo_info.logo_bmp_file = argv[1];
	logo_info.logo_bin_file = argv[2];
	logo_info.logo_param_file = argv[3];

	if((ret = transfer_bmp_image(&logo_info)) == 0) {
		for(i = 0; i < 4; i++) {
			printf("param_info.spclut_reg[%d]\t=0x%08lX\n",
				i, logo_info.param_info.spclut_reg[i]);
			printf("param_info.spclut[%d]\t\t=0x%08X\n",
				i, logo_info.param_info.spclut[i]);
		}
		printf("Logo changed successfully!\n");
	}

	printf("...(done).\n");

	return ret;
}

#endif /* ENABLE_LOGO_LOADER */

