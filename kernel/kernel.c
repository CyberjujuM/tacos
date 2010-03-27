#include <multiboot.h>
#include <idt.h>
#include <i8259.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <memory.h>
#include <pagination.h>
#include <gdt.h>
#include <exception.h>
#include <interrupts.h>
#include <pci.h>
#include <pci_config.h>
//#include <scheduler.h>
#include <time.h>
#include <dummy_process.h>
#include <keyboard.h>
#include <mouse.h>
#include <events.h>
#include <floppy.h>
#include <kpanic.h>
#include <process.h>
#include <kmalloc.h>
#include <vmm.h>
#include <ioports.h>
#include "msr.h"
#include <mbr.h>
#include <fpu.h>
#include <vm86.h>

typedef struct
{
  uint8_t lol;
} kernel_options;

/* Forward declarations. */
void cmain (unsigned long magic, unsigned long addr);
int shell(int argc, char* argv[]);
static void testPageReservation();
static void initKernelOptions(const char *cmdLine, kernel_options *options);

/* pour le test des processus */
process_t task[3];
uint32_t sys_stack[3][1024];
uint32_t user_stack[3][1024];

void exit(uint32_t value)
{
	syscall(0,42,value,0);
}

uint32_t get_pid()
{
	int pid;
	syscall(1,&pid, 0, 0);
	return pid;
}

int test_mouse(int argc, char** argv)
{
	int i = 0;
	int x;
	int y;
	printf("---- Test Mouse ----\n");
	
	while(1)
	{
		if(i%100000 == 0)
		{
			getMouseCoord(&x,&y);
			printf("\nmouse: %d %d [%d;%d;%d]\n",x,y,getMouseBtn(0),getMouseBtn(1),getMouseBtn(2));
		}
		i++;
	}
}

int test_task1(int argc, char** argv)
{
	int i = 0;
	printf("---- Test Task1 ----\n");
	
	while(1)
	{
		if(i%1000000 == 0)
		{
			printf("\ntask%d dit:\"Je tourne!!!\"\n",get_pid());
		}
		i++;
	}
}


void* sys_exit(uint32_t pid, uint32_t ret_value, uint32_t zero)
{
	printf("Exit(process %d returned %d)", pid, ret_value);
}

void* sys_getpid(uint32_t* pid, uint32_t zero1, uint32_t zero2)
{
	process_t* process = get_current_process();
	*pid = process->pid;
}



void cmain (unsigned long magic, unsigned long addr) {
	multiboot_info_t *mbi;
	kernel_options options;

	/* Clear the screen. */
	cls ();

	/* Am I booted by a Multiboot-compliant boot loader? */
	if (magic != MULTIBOOT_BOOTLOADER_MAGIC)
	{
		printf ("Invalid magic number: 0x%x\n", (unsigned) magic);
		return;
	}

	/* Set MBI to the address of the Multiboot information structure. */
	mbi = (multiboot_info_t *) addr;
	initKernelOptions((char *)mbi->cmdline, &options);

	printf("_|_|_|_|_|                      _|_|      _|_|_|\n");
	printf("    _|      _|_|_|    _|_|_|  _|    _|  _|      \n");
	printf("    _|    _|    _|  _|        _|    _|    _|_|  \n");
	printf("    _|    _|    _|  _|        _|    _|        _|\n");
	printf("    _|      _|_|_|    _|_|_|    _|_|    _|_|_|    ");
	printf("(codename:fajitas)\n\n\n");

	printf("Memoire disponible : %dMio\n", (mbi->mem_upper>>10) + 1); /* Grub balance la mémoire dispo -1 Mio... Soit.*/

	gdt_setup((mbi->mem_upper << 10) + (1 << 20));
	init_tss(sys_stack+1023);

	/* Mise en place de la table qui contient les descripteurs d'interruption (idt) */
	idt_setup();

	/* Configuration du i8259 qui s'occupe des interruptions. */
	i8259_setup();

	kpanic_init();
  
	interrupt_set_routine(IRQ_KEYBOARD, keyboardInterrupt, 0);
	mouseInit();
	init_syscall();
	floppy_init_interrupt();

  init_fpu();

	events_init(); 
	
	asm volatile ("sti\n");

	/* Configuration de la pagination */
			//asm("hlt");
	memory_setup((mbi->mem_upper << 10) + (1 << 20));

	pagination_setup();

	//memory_print_free_pages();
	//memory_print_used_pages();


  /* Initialisation de la vmm */
  init_vmm();
  init_kmalloc();

//	printf("Div 0 : %d.\n", 3/0);
//	pci_scan();
//	pci_list();

	floppy_detect_drives();
	printf("Floppy controller version: 0x%x.\n", floppy_get_version());
	
	if(init_floppy() != 0)
		printf("Initialisation du lecteur a echoue.\n");
		
	/*char MBR[FLOPPY_SECTOR_SIZE];
	floppy_read_sector(0,0,0,MBR);
	printf("MBR Signature:0x%x%x.\n",0xFF&MBR[0x01FE], 0xFF&MBR[0x01FF]);*/
	
	mbr_read ();
	mbr_print_signature ();
	mbr_print_part_table ();
	
	/* Test du scheduler */
	
	init_scheduler(1000);

	paddr_t _addr = shell;
	create_process(_addr,0,NULL,64,3);
	//process_print_regs();
/*
	_addr = test_task1;
	kmalloc(64);
	create_process(_addr, 0, NULL, 64, 3);
	//while(1);
*/
	printf("vm86:%d\n",check_vm86);
	syscall_set_handler(0,sys_exit);
	syscall_set_handler(1,sys_getpid);
	start_scheduler();

	while(1){}
}


int shell(int argc, char* argv[])
{
	char buffer[80];
	//kmalloc(10);
	//asm("xchg %bx, %bx");
	int i = 0;
	
	
	
	for(;;)
	{
		char c;
		
		time_t curr_time = time(NULL);
		printf("\n > ");
			
		while((c = getchar()) != '\n') {
			buffer[i%80] = c;
			putchar(c);
			i++;
		}
		buffer[i%80] = '\0';
		i = 0;
		printf("\n");
		if (strcmp(buffer, "help") == 0) {
			printf("Commandes dispos : reboot, halt, clear, sleep, lspci, switchdebug, switchstd, erase_mbr, test_task, print_memory, date, test_mouse\n");
		}
		if (strcmp(buffer, "reboot") == 0) {
			printf("Reboot non implemente, desole !");
		}
		if (strcmp(buffer, "halt") == 0) {
			printf("Halt !");
			asm("cli");
			asm("hlt");
		}
		if( strcmp(buffer, "date") == 0)
		{
			time_t curr_time = time(NULL);
			printf("%s",ctime(&curr_time));
		}
		if( strcmp(buffer, "clear") == 0)
			cls();
		if( strcmp(buffer, "sleep") == 0)
			sleep(1);
		if( strcmp(buffer, "lspci") == 0)
			pci_list();
		if (strcmp(buffer, "switchdebug") == 0) {
			switchDebugBuffer();
		}
		if (strcmp(buffer, "switchstd") == 0) {
			switchStandardBuffer();
		}
		if (strcmp(buffer, "print_memory") == 0) {
			memory_print();
		}
		if( strcmp(buffer, "erase_mbr") == 0)
		{
			char zeros[FLOPPY_SECTOR_SIZE];
			set_attribute(0, 4);
			cls();
			printf("/!\\ ERASING MBR MOUHAHA /!\\\n");
			floppy_write_sector(0,0,0,zeros);
			reset_attribute();
		}		
		if(strcmp(buffer,"test_task") == 0)
		{
			paddr_t proc_addr =  test_task1;
			process_t* proc = create_process(proc_addr,0,NULL,1024,3);
			//add_process(*proc);
			//while(1);
		}
		if(strcmp(buffer,"test_mouse") == 0)
		{
			test_mouse(0,NULL);
		}
		if(strcmp(buffer,"syscall") == 0)
		{
			//syscall(0x42,0,1,2);
			exit(-1);
		}
		if(strcmp(buffer,"ps")==0)
		{
			print_process_list();
		}
		if (strcmp(buffer, "test_sscanf") == 0) {
			char * str = "Hello 42 bla";
			char s[10];
			char s2[10];
			int d;

			sscanf(str, "%s %d %s", s, &d, s2);

			printf("%s %d %s\n", s2, d, s);
		}
	}
	
	return 0;
}

void waitReturn()
{
	while(getchar() != '\n')
		;
}

void testPageReservation()
{
	paddr_t addr;
	memory_print_free_pages();
	memory_print_used_pages();
	waitReturn();

	addr = memory_reserve_page_frame();
	memory_print_free_pages();
	memory_print_used_pages();
	waitReturn();

	memory_free_page_frame(addr);
	memory_print_free_pages();
	memory_print_used_pages();
	waitReturn();
}

static void defaultOptions(kernel_options *options)
{
	options->lol = 0;
}

static char get_opt(char **cmdLine)
{
	
	while(**cmdLine != '-' && **cmdLine != '\0') 
		(*cmdLine)++;

	if(**cmdLine == '\0')
		return -1;

	*cmdLine += 2;
	return *(*cmdLine - 1);
}

static void initKernelOptions(const char *cmdLine, kernel_options *options)
{
	char *cmd = cmdLine;
	char opt;

	printf("Command line : %s\n", cmdLine);

	defaultOptions(options);
	while((opt = get_opt(&cmd)) != -1)
	{
		switch(opt)
		{
		case 'l':
				options->lol = 1;
				enableFinnouMode(1);
				break;
		default: printf("Unknown option %c\n", opt);
		}
	}
}

