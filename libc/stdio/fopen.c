/**
 * @file fopen.c
 *
 * @author TacOS developers 
 *
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int convert_flags(const char *mode) {
	int flags = 0;
	if (strcmp(mode, "r") == 0) {
		flags = O_RDONLY;
	} else if (strcmp(mode, "r+") == 0) {
		flags = O_RDWR;
	} else if (strcmp(mode, "w") == 0) {
		flags = O_WRONLY;
	} else if (strcmp(mode, "w+") == 0) {
		flags = O_RDWR | O_CREAT;
	} else if (strcmp(mode, "a") == 0) {
		flags = O_APPEND | O_WRONLY | O_CREAT; // TODO : faut filer un "mode" indiquant les droits pour le nouveau fichier créé.
	} else if (strcmp(mode, "a+") == 0) {
		flags = O_APPEND | O_RDWR | O_CREAT;
	} else if (strcmp(mode, "ab") == 0) {

	} else if (strcmp(mode, "rb") == 0) {

	} else if (strcmp(mode, "wb") == 0) {
		
	} else if (strcmp(mode, "r+b") == 0 || strcmp(mode, "rb+")) {

	} else if (strcmp(mode, "w+b") == 0 || strcmp(mode, "wb+")) {

	} else if (strcmp(mode, "a+b") == 0 || strcmp(mode, "ab+")) {

	} else { // "Otherwise, the behavior is undefined." cf iso libc
		return -1;
	}

	return flags;
}
	
FILE *fopen(const char *path, const char *mode) {
	int flags = convert_flags(mode);
	int fileno;
	fileno = open(path, flags);

	if (fileno < 0) return NULL;

	FILE *stream = malloc(sizeof(FILE));
	memset(stream, 0, sizeof(FILE));
	stream->_chain = __file_list;
	__file_list = stream;

	stream->_fileno = fileno;
	// TODO : allouer buffer, en tenant compte des droits !

	return stream;
}

/* TODO Enlever les attributes quand la fonction sera codée... */
FILE *fdopen(int fd __attribute__ ((unused)), const char *mode __attribute__ ((unused))) {
	return NULL;
}

FILE *freopen(const char *path, const char *mode, FILE *stream) {
	fclose(stream);
	return fopen(path, mode);
}
