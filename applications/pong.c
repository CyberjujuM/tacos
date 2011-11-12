/**
 * @file clock_graph.c
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
 * Very basic pong game
 */

#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <vesa_types.h>

#define WIDTH 640
#define HEIGHT 480
#define BYTES_PER_PIXEL 3
#define BITS_PER_PIXEL 24

#define BALL_SIZE 15
#define RACKET_WIDTH 13
#define RACKET_HEIGHT 100


#define _COLOR(_p, _bpp) _p.bpp ## _bpp
#define COLOR(_p, _bpp) _COLOR(_p, _bpp)

#define VIDEO_BUFFER ((void*)0x10000000)

static int vesa_fd;

struct mousedata {
	int x;
	int y;
	bool buttons[3];
};

void put_pixel(color_t c, int x, int y) {
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
	memcpy(VIDEO_BUFFER + (y * WIDTH + x) * BYTES_PER_PIXEL, &COLOR(c, BITS_PER_PIXEL), sizeof(COLOR(c, BITS_PER_PIXEL)));
    }
}

void drawFilledRect(int x1, int y1,int x2, int y2, color_t color) {
    int i = x1;
    int j = y1;
    for (j = y1; j<y2; j++) {
	for (i = x1; i<x2; i++) {
	    put_pixel(color,i,j);
	}
    }
}

void drawBall (int x, int y, color_t color) {
    drawFilledRect (x,y,x + BALL_SIZE, y + BALL_SIZE,color);
}

void drawRacket (int y, color_t color) {
    if (y > HEIGHT - RACKET_HEIGHT) {
	y =  HEIGHT - RACKET_HEIGHT;
    }
    drawFilledRect(0,y,RACKET_WIDTH, y + RACKET_HEIGHT,color);
}

void moveBall(int * x, int * y, int * velX, int * velY, int racketY) {
    *x += *velX;
    *y += *velY;

    // check collisions with right wall
    if (*x + BALL_SIZE >= WIDTH)
	*velX = -*velX;
    // check collisions with racket/left wall
    else if (*x <= RACKET_WIDTH) {
       if(! (*y + BALL_SIZE >= racketY && *y <= racketY + RACKET_HEIGHT)){
	usleep(1000000);
	*x = WIDTH/2 - BALL_SIZE / 2;
	*y = HEIGHT/2 - BALL_SIZE /2;
	*velX = -*velX;
       }
       else {
	*velX = -*velX;
       }
    }

    // check collisions with top/bottom walls
    if (*y <= 0 || *y + BALL_SIZE >= HEIGHT)
	*velY = -*velY;
}

int main() {
    vesa_fd = open("$vesa", O_RDONLY);
    struct vesa_setmode_req req = { WIDTH, HEIGHT, BITS_PER_PIXEL };
    color_t color;

    int fd = open("$mouse", O_RDONLY);
    struct mousedata data;

    int ballX = WIDTH/2 - BALL_SIZE / 2;
    int ballY = HEIGHT/2 - BALL_SIZE /2;
    int velX = 10;
    int velY = 10;

    COLOR(color, BITS_PER_PIXEL).r = 255;
    COLOR(color, BITS_PER_PIXEL).g = 255;
    COLOR(color, BITS_PER_PIXEL).b = 255;
    ioctl(vesa_fd, SETMODE, &req);

    while (1) {	
	// read mouse position
	read(fd, &data, sizeof(data));
	data.y = 199 - data.y;
	data.x = data.x * WIDTH / 320;
	data.y = data.y * HEIGHT / 200;

	// draw ball and racket
	moveBall(&ballX,&ballY,&velX,&velY,data.y);
	drawBall(ballX,ballY,color);
	drawRacket(data.y,color);
	ioctl(vesa_fd, FLUSH, 0);
	
	usleep(10000);
    }
    return 0;
}
