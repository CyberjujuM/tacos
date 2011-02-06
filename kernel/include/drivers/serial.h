/**
 * @file serial.h
 *
 * @author TacOS developers 
 *
 * Maxime Cheramy <maxime81@gmail.com>
 * Nicolas Floquet <nicolasfloquet@gmail.com>
 * Benjamin Hautbois <bhautboi@gmail.com>
 * Ludovic Rigal <ludovic.rigal@gmail.com>
 * Simon Vernhes <simon@vernhes.eu>
 *
 * @section LICENSE
 *
 * Copyright (C) 2010 - TacOS developers.
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
 * Description de ce que fait le fichier
 */

#ifndef _SERIAL_H
#define _SERIAL_H

/* Masques pour les flags */
#define ECHO_ENABLED 0x2


typedef enum {
	COM1, COM2, COM3, COM4
}serial_port;

int serial_init(serial_port port, char* protocol, unsigned int bauds, int flags);

int serial_puts(serial_port port, char* string);
int serial_putc(serial_port port, char c);
int serial_gets(serial_port port, char* buffer, unsigned int size);

void serial_isr(int id __attribute__ ((unused)));
#endif /* _SERIAL_H_ */