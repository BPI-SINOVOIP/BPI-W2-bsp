/* Low-level functions for atomic operations. Mips version.
   Copyright (C) 2005-2014 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library.  If not, see
   <http://www.gnu.org/licenses/>.  */

#ifndef _MIPS_BITS_ATOMIC_H
#define _MIPS_BITS_ATOMIC_H 1

#include <stdint.h>
#include <inttypes.h>
#include <sgidefs.h>

typedef int32_t atomic32_t;
typedef uint32_t uatomic32_t;
typedef int_fast32_t atomic_fast32_t;
typedef uint_fast32_t uatomic_fast32_t;

typedef int64_t atomic64_t;
typedef uint64_t uatomic64_t;
typedef int_fast64_t atomic_fast64_t;
typedef uint_fast64_t uatomic_fast64_t;

typedef intptr_t atomicptr_t;
typedef uintptr_t uatomicptr_t;
typedef intmax_t atomic_max_t;
typedef uintmax_t uatomic_max_t;

#if _MIPS_SIM == _ABIO32
#define MIPS_PUSH_MIPS2 ".set	mips2\n\t"
#else
#define MIPS_PUSH_MIPS2
#endif

/* See the comments in <sys/asm.h> about the use of the sync instruction.  */
#ifndef MIPS_SYNC
# define MIPS_SYNC	sync
#endif

/* Certain revisions of the R10000 Processor need an LL/SC Workaround
   enabled.  Revisions before 3.0 misbehave on atomic operations, and
   Revs 2.6 and lower deadlock after several seconds due to other errata.

   To quote the R10K Errata:
      Workaround: The basic idea is to inhibit the four instructions
      from simultaneously becoming active in R10000. Padding all
      ll/sc sequences with nops or changing the looping branch in the
      routines to a branch likely (which is always predicted taken
      by R10000) will work. The nops should go after the loop, and the
      number of them should be 28. This number could be decremented for
      each additional instruction in the ll/sc loop such as the lock
      modifier(s) between the ll and sc, the looping branch and its
      delay slot. For typical short routines with one ll/sc loop, any
      instructions after the loop could also count as a decrement. The
      nop workaround pollutes the cache more but would be a few cycles
      faster if all the code is in the cache and the looping branch
      is predicted not taken.  */


#ifdef _MIPS_ARCH_R10000
#define R10K_BEQZ_INSN "beqzl"
#else
#define R10K_BEQZ_INSN "beqz"
#endif

#define MIPS_SYNC_STR_2(X) #X
#define MIPS_SYNC_STR_1(X) MIPS_SYNC_STR_2(X)
#define MIPS_SYNC_STR MIPS_SYNC_STR_1(MIPS_SYNC)

#if __GNUC_PREREQ (4, 8) || (defined __mips16 && __GNUC_PREREQ (4, 7))
/* The __atomic_* builtins are available in GCC 4.7 and later, but MIPS
   support for their efficient implementation was added only in GCC 4.8.
   We still want to use them even with GCC 4.7 for MIPS16 code where we
   have no assembly alternative available and want to avoid the __sync_*
   builtins if at all possible.  */

/* Compare and exchange.
   For all "bool" routines, we return FALSE if exchange succesful.  */

# define __arch_compare_and_exchange_bool_8_int(mem, newval, oldval, model) \
  (abort (), 0)

# define __arch_compare_and_exchange_bool_16_int(mem, newval, oldval, model) \
  (abort (), 0)

# define __arch_compare_and_exchange_bool_32_int(mem, newval, oldval, model) \
  ({									\
    typeof (*mem) __oldval = (oldval);					\
    !__atomic_compare_exchange_n (mem, (void *) &__oldval, newval, 0,	\
				  model, __ATOMIC_RELAXED);		\
  })

# define __arch_compare_and_exchange_val_8_int(mem, newval, oldval, model) \
  (abort (), (typeof(*mem)) 0)

# define __arch_compare_and_exchange_val_16_int(mem, newval, oldval, model) \
  (abort (), (typeof(*mem)) 0)

# define __arch_compare_and_exchange_val_32_int(mem, newval, oldval, model) \
  ({									\
    typeof (*mem) __oldval = (oldval);					\
    __atomic_compare_exchange_n (mem, (void *) &__oldval, newval, 0,	\
				 model, __ATOMIC_RELAXED);		\
    __oldval;								\
  })

# if _MIPS_SIM == _ABIO32
  /* We can't do an atomic 64-bit operation in O32.  */
#  define __arch_compare_and_exchange_bool_64_int(mem, newval, oldval, model) \
  (abort (), 0)
#  define __arch_compare_and_exchange_val_64_int(mem, newval, oldval, model) \
  (abort (), (typeof(*mem)) 0)
# else
#  define __arch_compare_and_exchange_bool_64_int(mem, newval, oldval, model) \
  __arch_compare_and_exchange_bool_32_int (mem, newval, oldval, model)
#  define __arch_compare_and_exchange_val_64_int(mem, newval, oldval, model) \
  __arch_compare_and_exchange_val_32_int (mem, newval, oldval, model)
# endif

/* Compare and exchange with "acquire" semantics, ie barrier after.  */

# define atomic_compare_and_exchange_bool_acq(mem, new, old)	\
  __atomic_bool_bysize (__arch_compare_and_exchange_bool, int,	\
			mem, new, old, __ATOMIC_ACQUIRE)

# define atomic_compare_and_exchange_val_acq(mem, new, old)	\
  __atomic_val_bysize (__arch_compare_and_exchange_val, int,	\
		       mem, new, old, __ATOMIC_ACQUIRE)

/* Compare and exchange with "release" semantics, ie barrier before.  */

# define atomic_compare_and_exchange_bool_rel(mem, new, old)	\
  __atomic_bool_bysize (__arch_compare_and_exchange_bool, int,	\
			mem, new, old, __ATOMIC_RELEASE)

# define atomic_compare_and_exchange_val_rel(mem, new, old)	 \
  __atomic_val_bysize (__arch_compare_and_exchange_val, int,    \
                       mem, new, old, __ATOMIC_RELEASE)


/* Atomic exchange (without compare).  */

# define __arch_exchange_8_int(mem, newval, model)	\
  (abort (), (typeof(*mem)) 0)

# define __arch_exchange_16_int(mem, newval, model)	\
  (abort (), (typeof(*mem)) 0)

# define __arch_exchange_32_int(mem, newval, model)	\
  __atomic_exchange_n (mem, newval, model)

# if _MIPS_SIM == _ABIO32
/* We can't do an atomic 64-bit operation in O32.  */
#  define __arch_exchange_64_int(mem, newval, model)	\
  (abort (), (typeof(*mem)) 0)
# else
#  define __arch_exchange_64_int(mem, newval, model)	\
  __atomic_exchange_n (mem, newval, model)
# endif

# define atomic_exchange_acq(mem, value)				\
  __atomic_val_bysize (__arch_exchange, int, mem, value, __ATOMIC_ACQUIRE)

# define atomic_exchange_rel(mem, value)				\
  __atomic_val_bysize (__arch_exchange, int, mem, value, __ATOMIC_RELEASE)


/* Atomically add value and return the previous (unincremented) value.  */

# define __arch_exchange_and_add_8_int(mem, value, model)	\
  (abort (), (typeof(*mem)) 0)

# define __arch_exchange_and_add_16_int(mem, value, model)	\
  (abort (), (typeof(*mem)) 0)

# define __arch_exchange_and_add_32_int(mem, value, model)	\
  __atomic_fetch_add (mem, value, model)

# if _MIPS_SIM == _ABIO32
/* We can't do an atomic 64-bit operation in O32.  */
#  define __arch_exchange_and_add_64_int(mem, value, model)	\
  (abort (), (typeof(*mem)) 0)
# else
#  define __arch_exchange_and_add_64_int(mem, value, model)	\
  __atomic_fetch_add (mem, value, model)
# endif

# define atomic_exchange_and_add_acq(mem, value)			\
  __atomic_val_bysize (__arch_exchange_and_add, int, mem, value,	\
		       __ATOMIC_ACQUIRE)

# define atomic_exchange_and_add_rel(mem, value)			\
  __atomic_val_bysize (__arch_exchange_and_add, int, mem, value,	\
		       __ATOMIC_RELEASE)

#elif defined __mips16 /* !__GNUC_PREREQ (4, 7) */
/* This implementation using __sync* builtins will be removed once glibc
   requires GCC 4.7 or later to build.  */

# define atomic_compare_and_exchange_val_acq(mem, newval, oldval)	\
  __sync_val_compare_and_swap ((mem), (oldval), (newval))
# define atomic_compare_and_exchange_bool_acq(mem, newval, oldval)	\
  (!__sync_bool_compare_and_swap ((mem), (oldval), (newval)))

# define atomic_exchange_acq(mem, newval)				\
  __sync_lock_test_and_set ((mem), (newval))

# define atomic_exchange_and_add(mem, val)				\
  __sync_fetch_and_add ((mem), (val))

# define atomic_bit_test_set(mem, bit)					\
  ({ __typeof (bit) __bit = (bit);					\
     (__sync_fetch_and_or ((mem), 1 << (__bit)) & (1 << (__bit))); })

# define atomic_and(mem, mask) (void) __sync_fetch_and_and ((mem), (mask))
# define atomic_and_val(mem, mask) __sync_fetch_and_and ((mem), (mask))

# define atomic_or(mem, mask) (void) __sync_fetch_and_or ((mem), (mask))
# define atomic_or_val(mem, mask) __sync_fetch_and_or ((mem), (mask))

#else /* !__mips16 && !__GNUC_PREREQ (4, 8) */
/* This implementation using inline assembly will be removed once glibc
   requires GCC 4.8 or later to build.  */

/* Compare and exchange.  For all of the "xxx" routines, we expect a
   "__prev" and a "__cmp" variable to be provided by the enclosing scope,
   in which values are returned.  */

# define __arch_compare_and_exchange_xxx_8_int(mem, newval, oldval, rel, acq) \
  (abort (), __prev = 0, __cmp = 0, (void) __cmp)

# define __arch_compare_and_exchange_xxx_16_int(mem, newval, oldval, rel, acq) \
  (abort (), __prev = 0, __cmp = 0, (void) __cmp)

# define __arch_compare_and_exchange_xxx_32_int(mem, newval, oldval, rel, acq) \
     __asm__ __volatile__ (						      \
     ".set	push\n\t"						      \
     MIPS_PUSH_MIPS2							      \
     rel	"\n"							      \
     "1:\t"								      \
     "ll	%0,%5\n\t"						      \
     "move	%1,$0\n\t"						      \
     "bne	%0,%3,2f\n\t"						      \
     "move	%1,%4\n\t"						      \
     "sc	%1,%2\n\t"						      \
     R10K_BEQZ_INSN"	%1,1b\n"					      \
     acq	"\n\t"							      \
     ".set	pop\n"							      \
     "2:\n\t"								      \
	      : "=&r" (__prev), "=&r" (__cmp), "=m" (*mem)		      \
	      : "r" (oldval), "r" (newval), "m" (*mem)			      \
	      : "memory")

# if _MIPS_SIM == _ABIO32
/* We can't do an atomic 64-bit operation in O32.  */
# define __arch_compare_and_exchange_xxx_64_int(mem, newval, oldval, rel, acq) \
  (abort (), __prev = 0, __cmp = 0, (void) __cmp)
# else
# define __arch_compare_and_exchange_xxx_64_int(mem, newval, oldval, rel, acq) \
     __asm__ __volatile__ ("\n"						      \
     ".set	push\n\t"						      \
     MIPS_PUSH_MIPS2							      \
     rel	"\n"							      \
     "1:\t"								      \
     "lld	%0,%5\n\t"						      \
     "move	%1,$0\n\t"						      \
     "bne	%0,%3,2f\n\t"						      \
     "move	%1,%4\n\t"						      \
     "scd	%1,%2\n\t"						      \
     R10K_BEQZ_INSN"	%1,1b\n"					      \
     acq	"\n\t"							      \
     ".set	pop\n"							      \
     "2:\n\t"								      \
	      : "=&r" (__prev), "=&r" (__cmp), "=m" (*mem)		      \
	      : "r" (oldval), "r" (newval), "m" (*mem)			      \
	      : "memory")
# endif

/* For all "bool" routines, we return FALSE if exchange succesful.  */

# define __arch_compare_and_exchange_bool_8_int(mem, new, old, rel, acq) \
({ typeof (*mem) __prev __attribute__ ((unused)); int __cmp;		\
   __arch_compare_and_exchange_xxx_8_int(mem, new, old, rel, acq);	\
   !__cmp; })

# define __arch_compare_and_exchange_bool_16_int(mem, new, old, rel, acq) \
({ typeof (*mem) __prev __attribute__ ((unused)); int __cmp;		\
   __arch_compare_and_exchange_xxx_16_int(mem, new, old, rel, acq);	\
   !__cmp; })

# define __arch_compare_and_exchange_bool_32_int(mem, new, old, rel, acq) \
({ typeof (*mem) __prev __attribute__ ((unused)); int __cmp;		\
   __arch_compare_and_exchange_xxx_32_int(mem, new, old, rel, acq);	\
   !__cmp; })

# define __arch_compare_and_exchange_bool_64_int(mem, new, old, rel, acq) \
({ typeof (*mem) __prev __attribute__ ((unused)); int __cmp;		\
   __arch_compare_and_exchange_xxx_64_int(mem, new, old, rel, acq);	\
   !__cmp; })

/* For all "val" routines, return the old value whether exchange
   successful or not.  */

# define __arch_compare_and_exchange_val_8_int(mem, new, old, rel, acq)	\
({ typeof (*mem) __prev; int __cmp;					\
   __arch_compare_and_exchange_xxx_8_int(mem, new, old, rel, acq);	\
   (typeof (*mem))__prev; })

# define __arch_compare_and_exchange_val_16_int(mem, new, old, rel, acq) \
({ typeof (*mem) __prev; int __cmp;					\
   __arch_compare_and_exchange_xxx_16_int(mem, new, old, rel, acq);	\
   (typeof (*mem))__prev; })

# define __arch_compare_and_exchange_val_32_int(mem, new, old, rel, acq) \
({ typeof (*mem) __prev; int __cmp;					\
   __arch_compare_and_exchange_xxx_32_int(mem, new, old, rel, acq);	\
   (typeof (*mem))__prev; })

# define __arch_compare_and_exchange_val_64_int(mem, new, old, rel, acq) \
({ typeof (*mem) __prev; int __cmp;					\
   __arch_compare_and_exchange_xxx_64_int(mem, new, old, rel, acq);	\
   (typeof (*mem))__prev; })

/* Compare and exchange with "acquire" semantics, ie barrier after.  */

# define atomic_compare_and_exchange_bool_acq(mem, new, old)	\
  __atomic_bool_bysize (__arch_compare_and_exchange_bool, int,	\
		        mem, new, old, "", MIPS_SYNC_STR)

# define atomic_compare_and_exchange_val_acq(mem, new, old)	\
  __atomic_val_bysize (__arch_compare_and_exchange_val, int,	\
		       mem, new, old, "", MIPS_SYNC_STR)

/* Compare and exchange with "release" semantics, ie barrier before.  */

# define atomic_compare_and_exchange_bool_rel(mem, new, old)	\
  __atomic_bool_bysize (__arch_compare_and_exchange_bool, int,	\
		        mem, new, old, MIPS_SYNC_STR, "")

# define atomic_compare_and_exchange_val_rel(mem, new, old)	\
  __atomic_val_bysize (__arch_compare_and_exchange_val, int,	\
		       mem, new, old, MIPS_SYNC_STR, "")



/* Atomic exchange (without compare).  */

# define __arch_exchange_xxx_8_int(mem, newval, rel, acq) \
  (abort (), (typeof(*mem)) 0)

# define __arch_exchange_xxx_16_int(mem, newval, rel, acq) \
  (abort (), (typeof(*mem)) 0)

# define __arch_exchange_xxx_32_int(mem, newval, rel, acq) \
({ typeof (*mem) __prev; int __cmp;					      \
     __asm__ __volatile__ ("\n"						      \
     ".set	push\n\t"						      \
     MIPS_PUSH_MIPS2							      \
     rel	"\n"							      \
     "1:\t"								      \
     "ll	%0,%4\n\t"						      \
     "move	%1,%3\n\t"						      \
     "sc	%1,%2\n\t"						      \
     R10K_BEQZ_INSN"	%1,1b\n"					      \
     acq	"\n\t"							      \
     ".set	pop\n"							      \
     "2:\n\t"								      \
	      : "=&r" (__prev), "=&r" (__cmp), "=m" (*mem)		      \
	      : "r" (newval), "m" (*mem)				      \
	      : "memory");						      \
  __prev; })

# if _MIPS_SIM == _ABIO32
/* We can't do an atomic 64-bit operation in O32.  */
#  define __arch_exchange_xxx_64_int(mem, newval, rel, acq) \
  (abort (), (typeof(*mem)) 0)
# else
#  define __arch_exchange_xxx_64_int(mem, newval, rel, acq) \
({ typeof (*mem) __prev; int __cmp;					      \
     __asm__ __volatile__ ("\n"						      \
     ".set	push\n\t"						      \
     MIPS_PUSH_MIPS2							      \
     rel	"\n"							      \
     "1:\n"								      \
     "lld	%0,%4\n\t"						      \
     "move	%1,%3\n\t"						      \
     "scd	%1,%2\n\t"						      \
     R10K_BEQZ_INSN"	%1,1b\n"					      \
     acq	"\n\t"							      \
     ".set	pop\n"							      \
     "2:\n\t"								      \
	      : "=&r" (__prev), "=&r" (__cmp), "=m" (*mem)		      \
	      : "r" (newval), "m" (*mem)				      \
	      : "memory");						      \
  __prev; })
# endif

# define atomic_exchange_acq(mem, value) \
  __atomic_val_bysize (__arch_exchange_xxx, int, mem, value, "", MIPS_SYNC_STR)

# define atomic_exchange_rel(mem, value) \
  __atomic_val_bysize (__arch_exchange_xxx, int, mem, value, MIPS_SYNC_STR, "")


/* Atomically add value and return the previous (unincremented) value.  */

# define __arch_exchange_and_add_8_int(mem, newval, rel, acq) \
  (abort (), (typeof(*mem)) 0)

# define __arch_exchange_and_add_16_int(mem, newval, rel, acq) \
  (abort (), (typeof(*mem)) 0)

# define __arch_exchange_and_add_32_int(mem, value, rel, acq) \
({ typeof (*mem) __prev; int __cmp;					      \
     __asm__ __volatile__ ("\n"						      \
     ".set	push\n\t"						      \
     MIPS_PUSH_MIPS2							      \
     rel	"\n"							      \
     "1:\t"								      \
     "ll	%0,%4\n\t"						      \
     "addu	%1,%0,%3\n\t"						      \
     "sc	%1,%2\n\t"						      \
     R10K_BEQZ_INSN"	%1,1b\n"					      \
     acq	"\n\t"							      \
     ".set	pop\n"							      \
     "2:\n\t"								      \
	      : "=&r" (__prev), "=&r" (__cmp), "=m" (*mem)		      \
	      : "r" (value), "m" (*mem)					      \
	      : "memory");						      \
  __prev; })

# if _MIPS_SIM == _ABIO32
/* We can't do an atomic 64-bit operation in O32.  */
#  define __arch_exchange_and_add_64_int(mem, value, rel, acq) \
  (abort (), (typeof(*mem)) 0)
# else
#  define __arch_exchange_and_add_64_int(mem, value, rel, acq) \
({ typeof (*mem) __prev; int __cmp;					      \
     __asm__ __volatile__ (						      \
     ".set	push\n\t"						      \
     MIPS_PUSH_MIPS2							      \
     rel	"\n"							      \
     "1:\t"								      \
     "lld	%0,%4\n\t"						      \
     "daddu	%1,%0,%3\n\t"						      \
     "scd	%1,%2\n\t"						      \
     R10K_BEQZ_INSN"	%1,1b\n"					      \
     acq	"\n\t"							      \
     ".set	pop\n"							      \
     "2:\n\t"								      \
	      : "=&r" (__prev), "=&r" (__cmp), "=m" (*mem)		      \
	      : "r" (value), "m" (*mem)					      \
	      : "memory");						      \
  __prev; })
# endif

# define atomic_exchange_and_add_acq(mem, value)			\
  __atomic_val_bysize (__arch_exchange_and_add, int, mem, value,	\
		       "", MIPS_SYNC_STR)

# define atomic_exchange_and_add_rel(mem, value)			\
  __atomic_val_bysize (__arch_exchange_and_add, int, mem, value,	\
		       MIPS_SYNC_STR, "")

#endif /* !__mips16 && !__GNUC_PREREQ (4, 8) */

/* TODO: More atomic operations could be implemented efficiently; only the
   basic requirements are done.  */

#ifdef __mips16
# define atomic_full_barrier() __sync_synchronize ()

#else /* !__mips16 */
# define atomic_full_barrier() \
  __asm__ __volatile__ (".set push\n\t"					      \
			MIPS_PUSH_MIPS2					      \
			MIPS_SYNC_STR "\n\t"				      \
			".set pop" : : : "memory")
#endif /* !__mips16 */

#endif /* bits/atomic.h */
