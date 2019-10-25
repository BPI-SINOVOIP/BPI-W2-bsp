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

#include <asm/cpufeature.h>
#include <asm/sysreg.h>

static inline int read_pmuver(void)
{
	u64 dfr0 = read_sysreg(id_aa64dfr0_el1);
	return cpuid_feature_extract_unsigned_field(dfr0,
						    ID_AA64DFR0_PMUVER_SHIFT);
}

static inline void write_pmcr(u32 val)
{
	write_sysreg(val, pmcr_el0);
}

static inline u32 read_pmcr(void)
{
	return read_sysreg(pmcr_el0);
}

static inline void write_pmselr(u32 val)
{
	write_sysreg(val, pmselr_el0);
}

static inline void write_pmccntr(u64 val)
{
	write_sysreg(val, pmccntr_el0);
}

static inline u64 read_pmccntr(void)
{
	return read_sysreg(pmccntr_el0);
}

static inline void write_pmxevcntr(u32 val)
{
	write_sysreg(val, pmxevcntr_el0);
}

static inline u32 read_pmxevcntr(void)
{
	return read_sysreg(pmxevcntr_el0);
}

static inline void write_pmxevtyper(u32 val)
{
	write_sysreg(val, pmxevtyper_el0);
}

static inline void write_pmcntenset(u32 val)
{
	write_sysreg(val, pmcntenset_el0);
}

static inline void write_pmcntenclr(u32 val)
{
	write_sysreg(val, pmcntenclr_el0);
}

static inline void write_pmintenset(u32 val)
{
	write_sysreg(val, pmintenset_el1);
}

static inline void write_pmintenclr(u32 val)
{
	write_sysreg(val, pmintenclr_el1);
}

static inline void write_pmovsclr(u32 val)
{
	write_sysreg(val, pmovsclr_el0);
}

static inline u32 read_pmovsclr(void)
{
	return read_sysreg(pmovsclr_el0);
}

static inline u32 read_pmceid0(void)
{
	return read_sysreg(pmceid0_el0);
}

static inline u32 read_pmceid1(void)
{
	return read_sysreg(pmceid1_el0);
}

#endif
