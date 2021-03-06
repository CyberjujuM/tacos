/**
 * @file msr.h
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

#ifndef _MSR_H_
#define _MSR_H

#define IA32_SYSENTER_CS		0x0174
#define IA32_SYSENTER_ESP		0x0175
#define IA32_SYSENTER_EIP		0x0176

#define write_msr(reg, msr_low, msr_high) 	\
		__asm__ volatile (					\
			"wrmsr\n\t"						\
			: /* No output */				\
			: "c" (reg), "a" (msr_low), "d" (msr_high))
			
#define read_msr(reg, msr_low, msr_high) 		\
		__asm__ volatile (						\
			"rdmsr\n\t"							\
			: "=a" (*msr_low), "=d" (*msr_high)	\
			: "c" (reg))
	
		

#endif
