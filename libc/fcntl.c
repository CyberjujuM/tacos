/**
 * @file fcntl.c
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

/**
 * @file fcntl.c
 */

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/syscall.h>

int open(const char *pathname, int flags) {
	int id;
	if (pathname[0] != '/' && pathname[0] != '$') {
		char * absolutepath = get_absolute_path(pathname);
		syscall(SYS_OPEN,(uint32_t) &id,(uint32_t) absolutepath,(uint32_t) flags);
		free(absolutepath);
	} else {
		syscall(SYS_OPEN,(uint32_t) &id,(uint32_t) pathname,(uint32_t) flags);
	}
	
	return id;
}

int close(int id) {
	int ret;
	syscall(SYS_CLOSE,(uint32_t) id,(uint32_t) &ret,(uint32_t) NULL);
	return ret;
}
