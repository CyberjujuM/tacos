#include <multiboot.h>
#include <idt.h>
#include <i8259.h>
#include <stdio.h>
#include <mempage.h>
#include <gdt.h>
#include <exception.h>
#include <pci.h>

/* Forward declarations. */
void cmain (unsigned long magic, unsigned long addr);

static void testhandlerexception(int error_id)
{
	/* TODO : L'erreur renvoyée devrait être 0 car il n'y a pas de code retour. */
	printf("Exception : %d\n", error_id);
}

void cmain (unsigned long magic, unsigned long addr) {
	multiboot_info_t *mbi;

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
  
	/* The Hello World */
	//printf("\nHello World !\n\n");
	/* Mieux! */
	printf("_|_|_|_|_|                      _|_|      _|_|_|\n");
	printf("    _|      _|_|_|    _|_|_|  _|    _|  _|      \n");
	printf("    _|    _|    _|  _|        _|    _|    _|_|  \n");
	printf("    _|    _|    _|  _|        _|    _|        _|\n");
	printf("    _|      _|_|_|    _|_|_|    _|_|    _|_|_|  \n\n\n");

	printf("Memoire disponible : %dMio\n", (mbi->mem_upper>>10) + 1); /* Grub balance la mémoire dispo -1 Mio... Soit.*/

	printf("%d\n", mbi->mem_lower);

	int i;
	for (i = 0; i < 5; i++) {
		printf("test %d\n", i+1);
	}

	//gdt_setup();

	/* Mise en place de la table qui contient les descripteurs d'interruption (idt) */
	idt_setup();

	/* Configuration du i8259 qui s'occupe des interruptions. */
	i8259_setup();

	exception_set_routine(EXCEPTION_DIVIDE_ERROR, testhandlerexception);

	/* Configuration de la pagination */
	mempage_setup((mbi->mem_upper << 10) + (1 << 20));

	//mempage_print_free_pages();
	//mempage_print_used_pages();

	//printf("Div 0 : %d.\n", 3/0);
	pci_scan();
	for(;;){}
}
