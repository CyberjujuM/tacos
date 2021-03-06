/**
 * @file unistd.h
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

#ifndef _UNISTD_H_
#define _UNISTD_H_

/**
 * @file unistd.h
 */

#include <sys/types.h>

#define STDIN_FILENO  0
#define STDOUT_FILENO 1
#define STDERR_FILENO 1

/**
 * @brief Change le current working directory.
 *
 * Change le current working directory.
 *
 * @param path Le chemin où on veut aller.
 *
 * @return 0 en cas de succès, -1 sinon.
 */
int chdir(const char *path);


/**
 * @brief Retourne l'actuel working directory.
 *
 * Retourne l'actuel working directory.
 *
 * @param buf Table qui prend le chemin actuel. Si NULL, alors un malloc 
 * est fait.
 * @param size Taille du buffer. Si le buffer est trop petit, une erreur 
 * sera renvoyée.
 *
 * @return Le chemin actuel. NULL en cas d'erreur.
 */
const char * getcwd(char * buf, size_t size);

/**
 * @brief Retourne le chemin absolu d'un path en fonction du cwd.
 *
 * Retourne le chemin absolue d'un path en fonction du cwd à partir 
 * d'un chemin relatif.
 *
 * @param dirname Chemin relatif.
 *
 * @return Chemin absolu.
 */
char * get_absolute_path(const char *dirname);

/**
 * @brief Obtenir l'identifiant du processus.
 *
 * Obtenir l'identifiant du processus.
 *
 * @return L'identifiant du processus.
 */
pid_t getpid(void);

/**
 * @brief Réalise l'appel-système indiqué par son identifiant.
 *
 * Réalise l'appel-système indiqué par son identifiant.
 *
 * @param func L'identifiant du syscall.
 */
void syscall(uint32_t func, uint32_t param1, uint32_t param2, uint32_t param3);

/** 
 * @brief Endort le processus pour une durée déterminée (en secondes).
 *
 * Endort le processus pour une durée déterminée (en secondes).
 * 
 * @see usleep
 *
 * @param seconds Le nombre de secondes pendant lesquelles le processus
 * doit être endormi.
 * 
 * @return 0 si le temps prévu s'est écoulé.
 */

unsigned int sleep(unsigned int seconds);

/** 
 * @brief Endort le processus pour une durée déterminée (en microsecondes).
 * 
 * Endort le processus pour une durée déterminée (en microsecondes).
 *
 * @param milliseconds Le nombre de microsecondes pendant lesquelles le 
 * processus doit être endormi.
 * 
 * @return 0 en cas de succès, -1 en cas d'erreur.
 */
unsigned int usleep(unsigned int microseconds);

ssize_t write(int fd, const void *buf, size_t count);

ssize_t read(int fd, void *buf, size_t count);

int lseek(int fd, long offset, int whence);

#endif //_UNISTD_H_
