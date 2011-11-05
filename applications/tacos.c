/**
 * @file tacos.c
 *
 * @author TacOS developers 
 *
 * @section LICENSE
 *
 * Copyright (C) 2011 - TacOS developers.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 3 of
 * the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details at
 * http://www.gnu.org/copyleft/gpl.html
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program; if not, see <http://www.gnu.org/licenses>.
 *
 * @section DESCRIPTION
 *
 * Surprise!
 */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/ioctl.h>
#include <vesa_types.h>

#define WIDTH 1024
#define HEIGHT 768
#define BYTES_PER_PIXEL 3
#define BITS_PER_PIXEL 24

#define _COLOR(_p, _bpp) _p.bpp ## _bpp
#define COLOR(_p, _bpp) _COLOR(_p, _bpp)

#define VIDEO_BUFFER ((unsigned char*)0x10000000)

static int vesa_fd;

typedef struct {
	unsigned short int type;
	unsigned int size;
	unsigned short int reserved1, reserved2;
	unsigned int offset;
} __attribute__ ((packed)) bmpfileheader_t;

typedef struct {
	unsigned int size;
	int width, height;
	unsigned short int planes;
	unsigned short int bits;
	unsigned int compression;
	unsigned int imagesize;
	int xresolution, yresolution;
	unsigned int ncolours;
	unsigned int importantcolours;
} __attribute__ ((packed)) bmpinfoheader_t;

void display_bmp() {
	FILE *bmpfile = fopen("tacos.bmp", "r");
	bmpfileheader_t fileHeader;
	bmpinfoheader_t infoHeader;

	fread(&fileHeader, sizeof(fileHeader), 1, bmpfile);  
	fread(&infoHeader, sizeof(infoHeader), 1, bmpfile);  

	int im_width = infoHeader.width;
	int im_height = infoHeader.height;

	fseek(bmpfile, fileHeader.offset, SEEK_SET);

	color_t pixel;

	int x, y, ligne, col;
	for (y = im_height - 1; y >= 0; y--) {
		for (x = 0; x < im_width; x++) {
			fread(&COLOR(pixel, BITS_PER_PIXEL), sizeof(COLOR(pixel, BITS_PER_PIXEL)), 1, bmpfile);

			for (ligne = 0; (ligne*im_height + y) < HEIGHT; ligne++) {
				for (col = 0; (col*im_width + x) < WIDTH; col++) {
					VIDEO_BUFFER[((ligne*im_height + y) * WIDTH + x + col*im_width)*BYTES_PER_PIXEL + 0] = COLOR(pixel, BITS_PER_PIXEL).b;
					VIDEO_BUFFER[((ligne*im_height + y) * WIDTH + x + col*im_width)*BYTES_PER_PIXEL + 1] = COLOR(pixel, BITS_PER_PIXEL).g;
					VIDEO_BUFFER[((ligne*im_height + y) * WIDTH + x + col*im_width)*BYTES_PER_PIXEL + 2] = COLOR(pixel, BITS_PER_PIXEL).r;
				}
			}
		}

		int pos = ftell(bmpfile);
		if (pos % 4 != 0) {
			fseek(bmpfile, 4 - pos % 4, SEEK_CUR);
		}
	}
}

int main() {
	vesa_fd = open("$vesa", O_RDONLY);
	struct vesa_setmode_req req = { WIDTH, HEIGHT, BITS_PER_PIXEL };
	ioctl(vesa_fd, SETMODE, &req);

	display_bmp();
	ioctl(vesa_fd, FLUSH, 0);

	while (1);

	return 0;
}
