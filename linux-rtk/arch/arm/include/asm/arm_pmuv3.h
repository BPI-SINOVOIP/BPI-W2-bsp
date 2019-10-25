// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2012 ARM Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __ASM_PMUV3_H
#define __ASM_PMUV3_H

#include <asm/cp15.h>
#include <asm/cputype.h>

#define PMCCNTR		__ACCESS_CP15_64(0, c9)

#define PMCR		__ACCESS_CP15(c9, 0, c12, 0)
#define PMCNTENSET	__ACCESS_CP15(c9, 0, c12, 1)
#define PMCNTENCLR	__ACCESS_CP15(c9, 0, c12, 2)
#define PMOVSR		__ACCESS_CP15(c9, 0, c12, 3)
#define PMSELR		__ACCESS_CP15(c9, 0, c12, 5)
#define PMCEID0		__ACCESS_CP15(c9, 0, c12, 6)
#define PMCEID1		__ACCESS_CP15(c9, 0, c12, 7)
#define PMXEVTYPER	__ACCESS_CP15(c9, 0, c13, 1)
#define PMXEVCNTR	__ACCESS_CP15(c9, 0, c13, 2)
#define PMINTENSET	__ACCESS_CP15(c9, 0, c14, 1)
#define PMINTENCLR	__ACCESS_CP15(c9, 0, c14, 2)

static inline int read_pmuver(void)
{
	/* PMUVers is not a signed field */
	u32 dfr0 = read_cpuid_ext(CPUID_EXT_DFR0);
	return (dfr0 >> 24) & 0xf;
}

static inline void write_pmcr(u32 val)
{
	write_sysreg(val, PMCR);
}

static inline u32 read_pmcr(void)
{
	return read_sysreg(PMCR);
}

static inline void write_pmselr(u32 val)
{
	write_sysreg(val, PMSELR);
}

static inline void write_pmccntr(u64 val)
{
	write_sysreg(val, PMCCNTR);
}

static inline u64 read_pmccntr(void)
{
	return read_sysreg(PMCCNTR);
}

static inline void write_pmxevcntr(u32 val)
{
	write_sysreg(val, PMXEVCNTR);
}

static inline u32 read_pmxevcntr(void)
{
	return read_sysreg(PMXEVCNTR);
}

static inline void write_pmxevtyper(u32 val)
{
	write_sysreg(val, PMXEVTYPER);
}

static inline void write_pmcntenset(u32 val)
{
	write_sysreg(val, PMCNTENSET);
}

static inline void write_pmcntenclr(u32 val)
{
	write_sysreg(val, PMCNTENCLR);
}

static inline void write_pmintenset(u32 val)
{
	write_sysreg(val, PMINTENSET);
}

static inline void write_pmintenclr(u32 val)
{
	write_sysreg(val, PMINTENCLR);
}

static inline void write_pmovsclr(u32 val)
{
	write_sysreg(val, PMOVSR);
}

static inline u32 read_pmovsclr(void)
{
	return read_sysreg(PMOVSR);
}

static inline u32 read_pmceid0(void)
{
	return read_sysreg(PMCEID0);
}

static inline u32 read_pmceid1(void)
{
	return read_sysreg(PMCEID1);
}

#endif
