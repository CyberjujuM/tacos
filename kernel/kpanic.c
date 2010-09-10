/**
 * @file kpanic.c
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

#include <stdio.h>
#include <exception.h>
#include <kpanic.h>
#include <kprocess.h>
#include <scheduler.h>

#define GAME_OVER() asm("cli\n\thlt");

void printStackTrace(uint32_t depth)
{
	// Joli petit hack:
	// on récupère ebp à partir de l'adresse de l'argument:
	uint32_t* ebp = &depth - 2;
	uint32_t i;
	kprintf("\nStack Trace:\n");
	
	for(i=0; i<depth+3; ++i)
	{
		uint32_t eip = ebp[1];
		
		if(eip == 0x0010001f) // Si on arrive au multiboot_entry
		{
			break;
		}
		ebp = (uint32_t*) ebp[0];
		if(i>=2)
			kprintf("->0x%x\n",eip);
	}
}

void page_fault_report(int error_code)
{
	uint32_t address;
	/* On récupère le registre cr2 qui contient l'addresse virtuelle à l'origine de l'exception */
	asm("mov %%cr2, %%eax":"=a"(address));
	kprintf("Virtual address: 0x%x\n",address);
	kprintf("Cause: ");
	if(error_code & 0x01) // Bit P
		kprintf("Page-protection violation.\n");
	else
		kprintf("Non-present page.\n");
	
		
	kprintf("\n\n\tPlease press Atl-tab to continue...");
}

void kpanic_main_report(int error_id, int error_code, process_t* badboy)
{
    focus_console(0);
	// background white
	kprintf("\033[47m");
	// Foreground black
	kprintf("\033[30m");
	// cls :
	kprintf("\033[2J");

	kprintf("                              /!\\ KERNEL PANIC /!\\\n");
	kprintf("--------------------------------------------------------------------------------\n");
	/* On affiche le nom du bad boy */
	kprintf("In \033[31m%s (pid:%d)\033[47m\033[30m\n\n", badboy->name, badboy->pid);
	
	printStackTrace(10);
	
	kprintf("\nException handled : ");
	switch(error_id)
	{
		case EXCEPTION_SEGMENT_NOT_PRESENT:
			kprintf("Segment not present (error code : 0x%x).\n", error_code);
			GAME_OVER();
			break;
		case EXCEPTION_DIVIDE_ERROR:
			kprintf("Division by zero.\n");
			break;
		case EXCEPTION_INVALID_OPCODE:
			kprintf("Invalid OpCode.\n");
			GAME_OVER();
			break;
		case EXCEPTION_INVALID_TSS:
			kprintf("Invalid TSS (error code : %d).\n", error_code);
			GAME_OVER();
			break;
		case EXCEPTION_PAGE_FAULT:
			kprintf("Page fault (error code : %d).\n", error_code);
			page_fault_report(error_code);
			break;
		case EXCEPTION_DOUBLE_FAULT:
			kprintf("Double fault (error code : %d).\n", error_code);
			GAME_OVER();
			break;
		case EXCEPTION_GENERAL_PROTECTION :
			kprintf("General Protection fault (error code : %x).\n", error_code);
			GAME_OVER();
			break;
		default:
			kprintf("Unknown exception.\n");
			GAME_OVER();
	}
}
	
	
void kpanic_handler(int error_id, int error_code)
{
	process_t* badboy;
	
	stop_scheduler();	/* On arrête le déroulement des taches durant la gestion du kernel panic */
	badboy = get_current_process();	/* On récupère le bad boy */
	
	kpanic_main_report(error_id, error_code, badboy);	/* Affichage des information plus ou moins utiles */
	
	/* 
	 * Si on arrive ici, c'est que ce n'étais pas si grave que ça, du coup, on règle le problème et on relance le scheduler
	 */
	 
	badboy->state = PROCSTATE_TERMINATED; /* ouais ouais, bourrin */
	asm("sti");			/* Et on tente de revenir au choses normales */
	start_scheduler();
	
	while(1);
}

void kpanic_init()
{
  exception_set_routine(EXCEPTION_SEGMENT_NOT_PRESENT , kpanic_handler);
  exception_set_routine(EXCEPTION_DIVIDE_ERROR, kpanic_handler);
  exception_set_routine(EXCEPTION_INVALID_OPCODE, kpanic_handler);
  exception_set_routine(EXCEPTION_INVALID_TSS, kpanic_handler);
  exception_set_routine(EXCEPTION_PAGE_FAULT, kpanic_handler);
  exception_set_routine(EXCEPTION_DOUBLE_FAULT, kpanic_handler);
  exception_set_routine(EXCEPTION_GENERAL_PROTECTION, kpanic_handler);
}

