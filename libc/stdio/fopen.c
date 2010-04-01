#include <stdio.h>
#include <string.h>
#include <fcntl.h>

FILE *fopen(const char *path, const char *mode) {
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
		return NULL;
	}

	int fileno = open(path, flags); // open doit faire un appel systeme et s'occuper aussi de modifier la fd_table !

	// Va chercher dans le process le file_list pour chainer comme il faut.
	process_t *current_process = get_current_process();
	FILE *stream = malloc(sizeof(FILE));
	stream->_chain = current_process->file_list;
	current_process->file_list = stream;

	stream->_fileno = fileno;
	// TODO : allouer buffer, en tenant compte des droits !

	return stream;
}

FILE *fdopen(int fd, const char *mode) {
	
}

FILE *freopen(const char *path, const char *mode, FILE *stream) {

}