#include "hsectl.h"

void __hse_sw_yuyv2nv12(void *dst0,
			void *dst1,
			void *src,
			uint32_t width,
			uint32_t height,
			uint32_t src_pitch,
			uint32_t dst_pitch)
{
	int i, j, k;
	int h, w;
	uint8_t *s0 = src;
	uint8_t *d0 = dst0;
	uint8_t *d1 = dst1;

	i = j = k = 0;
	for (h = 0; h < height; h++) {
		for (w = 0; w < width; w+=4) {
			d0[j++] = s0[i++];
			d1[k++] = s0[i++];
			d0[j++] = s0[i++];
			d1[k++] = s0[i++];
		}
		i += (src_pitch - width);
		j += (dst_pitch - width / 2);
		k += (dst_pitch - width / 2);
	}
}

void __hse_sw_rotate(void *src,
		     void *dst,
		     uint32_t mode,
		     uint32_t width,
		     uint32_t height,
		     uint32_t src_pitch,
		     uint32_t dst_pitch)
{
	uint32_t x_size;
	uint32_t y_size;
	uint32_t x_bound;
	uint8_t *s = src;
	uint8_t *d = dst;
	int i, j;

	switch (mode) {
	case HSE_ROTATE_MODE_90:
	case HSE_ROTATE_MODE_270:
		x_size = dst_pitch;
		y_size = width;
		x_bound = height;
		break;
	case HSE_ROTATE_MODE_180:
		x_size = dst_pitch;
		y_size = height;
		x_bound = width;
		break;
	default:
		return;
	}

	if (mode == HSE_ROTATE_MODE_90) {
		/*
		i j -> x y
		0 0 -> 3 0
		0 1 -> 2 0
		...
		1 0 -> 3 1
		1 1 -> 2 1
		...
		*/
		for (i = 0; i < height; i++)
			for (j = 0; j < width; j++)
				d[(y_size - 1 - j) * x_size + i] = s[i * src_pitch + j];
	}
	else if (mode == HSE_ROTATE_MODE_270) {
		/*
		i j -> x y
		0 0 -> 0 3
		0 1 -> 1 3
		...
		1 0 -> 0 2
		1 1 -> 1 2
		...
		*/
		for (i = 0; i < height; i++)
			for (j = 0; j < width; j++)
				d[(j) * x_size + width - 1 - i] = s[i * src_pitch + j];
	}
	else if (mode == HSE_ROTATE_MODE_180) {
		/*
		i j -> x y
		0 0 -> 3 3
		0 1 -> 3 2
		...
		1 0 -> 2 3
		1 1 -> 2 2
		...
		*/
		for (i = 0; i < height; i++)
			for (j = 0; j < width; j++)
				d[(y_size - 1 - i) * x_size + width - 1 - j] = s[i * src_pitch + j];
	}
}

