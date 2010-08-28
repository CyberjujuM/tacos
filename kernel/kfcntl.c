#include <kprocess.h>
#include <stdio.h>
#include <fat.h>
#include <string.h>
#include <kmalloc.h>

#include <keyboard.h>
#include <video.h>

void init_stdfd(struct _file_descriptor *fd0, struct _file_descriptor *fd1, struct _file_descriptor *fd2) {
	fd0->used = TRUE; /* stdin */
	fd0->ofd = kmalloc(sizeof(open_file_descriptor));
	fd0->ofd->write = write_keyboard;
	fd0->ofd->read = read_screen;
	fd0->ofd->current_octet_buf = 0;
	fd1->used = TRUE; /* stdout */
	fd1->ofd = kmalloc(sizeof(open_file_descriptor));
	fd1->ofd->write = write_screen;
	fd1->ofd->extra_data = creation_text_window(0, 0, 80, 24, 0, 0, 0, DEFAULT_ATTRIBUTE_VALUE, 0);
	fd2->used = TRUE; /* stderr */
	fd2->ofd = kmalloc(sizeof(open_file_descriptor));
	fd2->ofd->write = write_screen;
	fd2->ofd->extra_data = creation_text_window(0, 0, 80, 24, 0, 0, 0, DEFAULT_ATTRIBUTE_VALUE, 1);
}


void* sys_open(uint32_t fd_id, uint32_t p_path , uint32_t flags) {
	int i=0;
	
	//process_t * process = (process_t*) p_process;
	char * path = (char*) p_path;
	process_t* process = get_current_process();
	
	// recherche d une place dans la file descriptor table du process
	while(process->fd[i].used==TRUE) 
		i++;
	
	// creation d un open_file_descriptor
	process->fd[i].ofd = kmalloc(sizeof(open_file_descriptor));
	process->fd[i].used = TRUE;
	
	// ouverture du fichier (sur fd0 pour le moment)
	if (fat_open_file(path, process->fd[i].ofd, flags) == 0) {
		// C'est ici qu'on devrait vérifier si le fichier ouvert est spécial 
		// pour savoir si on doit binder au file system ou à un driver.
		process->fd[i].ofd->write = write_file;
		process->fd[i].ofd->read = read_file;
		process->fd[i].ofd->seek = seek_file;
		*((int *)fd_id) = i;
	} else {
		*((int *)fd_id) = -1;
	}

  return NULL;
}

