/**
 * @file ksignal.h
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

#ifndef _KSIGNAL_H
#define _KSIGNAL_H

#include <ksyscall.h>
#include <signal.h>
#include <types.h>
#include <kprocess.h>

typedef struct {
	vaddr_t ret_addr;
	int sig;
	regs_t context;
	uint32_t state;
	sigset_t mask;
	char retcode[8];
} sigframe;

SYSCALL_HANDLER3(sys_signal, uint32_t signum, sighandler_t handler, sighandler_t* ret);
SYSCALL_HANDLER3(sys_sigprocmask, uint32_t how, sigset_t* set, sigset_t* oldset);
SYSCALL_HANDLER3(sys_kill, int pid, int signum, int* ret);
SYSCALL_HANDLER0(sys_sigret);
SYSCALL_HANDLER1(sys_sigsuspend, sigset_t* mask);

int exec_sighandler(process_t* process);

int signal_pending(process_t* process);


#endif /* _KSIGNAL_H */
