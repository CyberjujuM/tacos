#include <types.h>
#include <stdlib.h>
#include <stdio.h> 
#include <syscall.h>
#include <process.h>
#include <elf.h>

#define GET_PROCESS 0
#define GET_PROCESS_LIST 1


void exit(uint32_t value)
{ 
	syscall(SYS_EXIT,value,0,0);
	while(1); // Pour ne pas continuer à executer n'importe quoi alors que le processus est sensé être arrété
}

uint32_t get_pid()
{
	int pid;
	syscall(SYS_GETPID,(uint32_t)&pid, 0, 0);
	return pid;
}

void exec(paddr_t prog, char* name, int orphan)
{
	int ret = -1;

	process_init_data_t init_data;
	
	init_data.name	= name;
	init_data.stack_size = 0x1000;
	init_data.priority = 0;
	init_data.args = "fajitas bonitas";

	init_data.data = prog;

	init_data.mem_size = 0;
	init_data.entry_point = 0;
	
	init_data.ppid = orphan?0:get_pid();
	
	syscall(SYS_EXEC, (uint32_t)NULL, (uint32_t)&init_data, 1);


}

int exec_elf(char* name, int orphan)
{	
	int ret = -1;
	FILE *fd	= fopen(name, "r");
	
	process_init_data_t init_data;
	
	if(fd != NULL)
	{
		ret = 0;
			
		init_data.name	= name;
		init_data.stack_size = 0x1000;
		init_data.priority = 0;
		init_data.args = "fajitas bonitas";
		
		init_data.mem_size = elf_size(fd);
		init_data.data = malloc(init_data.mem_size);
		init_data.entry_point = load_elf(fd, init_data.data);

		init_data.ppid = orphan?0:get_pid();

		syscall(SYS_EXEC, (uint32_t)&init_data, (uint32_t)NULL, (uint32_t)NULL);
		
		free(init_data.data);
	}
	return ret;
}

process_t* get_process(int pid)
{
	process_t* temp;
	syscall(SYS_PROC,(uint32_t)GET_PROCESS, (uint32_t)pid, (uint32_t) &temp);
	return temp;
}

process_t* get_process_list(uint32_t action)
{
	process_t* temp;
	syscall(SYS_PROC,(uint32_t)GET_PROCESS_LIST, (uint32_t)action, (uint32_t) &temp);
	return temp;
}
