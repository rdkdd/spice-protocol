/* -*- Mode: C; c-basic-offset: 4; indent-tabs-mode: nil -*- */
/*
   Copyright (C) 2010 Red Hat, Inc.

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, see <http://www.gnu.org/licenses/>.
*/

/* This file is to a large extent based on gmacros.h from glib
 * Which is LGPL and copyright:
 *
 * Modified by the GLib Team and others 1997-2000.  See the AUTHORS
 * file for a list of people on the GLib Team.  See the ChangeLog
 * files for a list of changes.  These files are distributed with
 * GLib at ftp://ftp.gtk.org/pub/gtk/.
 */

#ifndef _H_SPICE_MACROS
#define _H_SPICE_MACROS

/* We include stddef.h to get the system's definition of NULL */
#include <stddef.h>

#include <spice/types.h>

#if    __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 96)
#define SPICE_GNUC_PURE __attribute__((__pure__))
#define SPICE_GNUC_MALLOC __attribute__((__malloc__))
#else
#define SPICE_GNUC_PURE
#define SPICE_GNUC_MALLOC
#endif

#if     __GNUC__ >= 4
#define SPICE_GNUC_NULL_TERMINATED __attribute__((__sentinel__))
#else
#define SPICE_GNUC_NULL_TERMINATED
#endif

#ifndef __has_feature
#define __has_feature(x) 0  /* Compatibility with non-clang compilers. */
#endif

#if     (!defined(__clang__) && ((__GNUC__ > 4) || (__GNUC__ == 4 && __GNUC_MINOR__ >= 3))) || \
        (defined(__clang__) && __has_feature(__alloc_size__))
#define SPICE_GNUC_ALLOC_SIZE(x) __attribute__((__alloc_size__(x)))
#define SPICE_GNUC_ALLOC_SIZE2(x,y) __attribute__((__alloc_size__(x,y)))
#else
#define SPICE_GNUC_ALLOC_SIZE(x)
#define SPICE_GNUC_ALLOC_SIZE2(x,y)
#endif

#if     __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ > 4)
#define SPICE_GNUC_PRINTF( format_idx, arg_idx ) __attribute__((__format__ (__printf__, format_idx, arg_idx)))
#define SPICE_GNUC_SCANF( format_idx, arg_idx ) __attribute__((__format__ (__scanf__, format_idx, arg_idx)))
#define SPICE_GNUC_FORMAT( arg_idx ) __attribute__((__format_arg__ (arg_idx)))
#define SPICE_GNUC_NORETURN __attribute__((__noreturn__))
#define SPICE_GNUC_CONST __attribute__((__const__))
#define SPICE_GNUC_UNUSED __attribute__((__unused__))
#define SPICE_GNUC_NO_INSTRUMENT __attribute__((__no_instrument_function__))
#else   /* !__GNUC__ */
#define SPICE_GNUC_PRINTF( format_idx, arg_idx )
#define SPICE_GNUC_SCANF( format_idx, arg_idx )
#define SPICE_GNUC_FORMAT( arg_idx )
#define SPICE_GNUC_NORETURN
#define SPICE_GNUC_CONST
#define SPICE_GNUC_UNUSED
#define SPICE_GNUC_NO_INSTRUMENT
#endif  /* !__GNUC__ */

#if    __GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 1)
#define SPICE_GNUC_DEPRECATED  __attribute__((__deprecated__))
#else
#define SPICE_GNUC_DEPRECATED
#endif /* __GNUC__ */

#if     __GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 3)
#  define SPICE_GNUC_MAY_ALIAS __attribute__((may_alias))
#else
#  define SPICE_GNUC_MAY_ALIAS
#endif

#if    __GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4)
#define SPICE_GNUC_WARN_UNUSED_RESULT __attribute__((warn_unused_result))
#else
#define SPICE_GNUC_WARN_UNUSED_RESULT
#endif /* __GNUC__ */


/* Guard C code in headers, while including them from C++ */
#ifdef  __cplusplus
# define SPICE_BEGIN_DECLS  extern "C" {
# define SPICE_END_DECLS    }
#else
# define SPICE_BEGIN_DECLS
# define SPICE_END_DECLS
#endif

#ifndef	FALSE
#define	FALSE	(0)
#endif

#ifndef	TRUE
#define	TRUE	(!FALSE)
#endif

#undef	MAX
#define MAX(a, b)  (((a) > (b)) ? (a) : (b))

#undef	MIN
#define MIN(a, b)  (((a) < (b)) ? (a) : (b))

#undef	ABS
#define ABS(a)     (((a) < 0) ? -(a) : (a))

/* Count the number of elements in an array. The array must be defined
 * as such; using this with a dynamically allocated array will give
 * incorrect results.
 */
#define SPICE_N_ELEMENTS(arr) (sizeof (arr) / sizeof ((arr)[0]))

#define SPICE_ALIGN(a, size) (((a) + ((size) - 1)) & ~((size) - 1))

/* Provide convenience macros for handling structure
 * fields through their offsets.
 */

#if defined(__GNUC__)  && __GNUC__ >= 4
#  define SPICE_OFFSETOF(struct_type, member) \
    ((long) offsetof (struct_type, member))
#else
#  define SPICE_OFFSETOF(struct_type, member)	\
    ((long) ((uint8_t*) &((struct_type*) 0)->member))
#endif

/* The SPICE_USE_SAFER_CONTAINEROF macro is used to avoid
 * compilation breakage with older spice-server releases which
 * triggered some errors without an additional patch.
 */
#if defined(__GNUC__) && defined(SPICE_USE_SAFER_CONTAINEROF) && \
    (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4))
#define SPICE_CONTAINEROF(ptr, struct_type, member) ({ \
    const typeof( ((struct_type *)0)->member ) *__mptr = (ptr);    \
    ((struct_type *)(void *)((uint8_t *)(__mptr) - SPICE_OFFSETOF(struct_type, member))); })
#else
#define SPICE_CONTAINEROF(ptr, struct_type, member) \
    ((struct_type *)(void *)((uint8_t *)(ptr) - SPICE_OFFSETOF(struct_type, member)))
#endif

#define SPICE_MEMBER_P(struct_p, struct_offset)   \
    ((gpointer) ((guint8*) (struct_p) + (glong) (struct_offset)))
#define SPICE_MEMBER(member_type, struct_p, struct_offset)   \
    (*(member_type*) SPICE_STRUCT_MEMBER_P ((struct_p), (struct_offset)))

/* Provide simple macro statement wrappers:
 *   SPICE_STMT_START { statements; } SPICE_STMT_END;
 * This can be used as a single statement, like:
 *   if (x) SPICE_STMT_START { ... } SPICE_STMT_END; else ...
 * This intentionally does not use compiler extensions like GCC's '({...})' to
 * avoid portability issue or side effects when compiled with different compilers.
 */
#if !(defined (SPICE_STMT_START) && defined (SPICE_STMT_END))
#  define SPICE_STMT_START  do
#  define SPICE_STMT_END    while (0)
#endif

/*
 * The SPICE_LIKELY and SPICE_UNLIKELY macros let the programmer give hints to
 * the compiler about the expected result of an expression. Some compilers
 * can use this information for optimizations.
 *
 * The _SPICE_BOOLEAN_EXPR macro is intended to trigger a gcc warning when
 * putting assignments in g_return_if_fail ().
 */
#if defined(__GNUC__) && (__GNUC__ > 2) && defined(__OPTIMIZE__)
#define _SPICE_BOOLEAN_EXPR(expr)               \
 __extension__ ({                               \
   int _g_boolean_var_;                         \
   if (expr)                                    \
      _g_boolean_var_ = 1;                      \
   else                                         \
      _g_boolean_var_ = 0;                      \
   _g_boolean_var_;                             \
})
#define SPICE_LIKELY(expr) (__builtin_expect (_SPICE_BOOLEAN_EXPR(expr), 1))
#define SPICE_UNLIKELY(expr) (__builtin_expect (_SPICE_BOOLEAN_EXPR(expr), 0))
#else
#define SPICE_LIKELY(expr) (expr)
#define SPICE_UNLIKELY(expr) (expr)
#endif

#ifdef _MSC_VER
#define SPICE_UINT64_CONSTANT(x) (x ## UI64)
#define SPICE_INT64_CONSTANT(x) (x ## I64)
#else
#if LONG_MAX == 2147483647L
#define SPICE_UINT64_CONSTANT(x) (x ## ULL)
#define SPICE_INT64_CONSTANT(x) (x ## LL)
#else
#define SPICE_UINT64_CONSTANT(x) (x ## UL)
#define SPICE_INT64_CONSTANT(x) (x ## L)
#endif
#endif

/* Little/Bit endian byte swapping */

#define SPICE_BYTESWAP16_CONSTANT(val)	((uint16_t) ( \
    (uint16_t) ((uint16_t) (val) >> 8) |	\
    (uint16_t) ((uint16_t) (val) << 8)))

#define SPICE_BYTESWAP32_CONSTANT(val)	((uint32_t) ( \
    (((uint32_t) (val) & (uint32_t) 0x000000ffU) << 24) | \
    (((uint32_t) (val) & (uint32_t) 0x0000ff00U) <<  8) | \
    (((uint32_t) (val) & (uint32_t) 0x00ff0000U) >>  8) | \
    (((uint32_t) (val) & (uint32_t) 0xff000000U) >> 24)))

#define SPICE_BYTESWAP64_CONSTANT(val)	((uint64_t) ( \
      (((uint64_t) (val) &						\
	(uint64_t) SPICE_UINT64_CONSTANT(0x00000000000000ff)) << 56) |	\
      (((uint64_t) (val) &						\
	(uint64_t) SPICE_UINT64_CONSTANT(0x000000000000ff00)) << 40) |	\
      (((uint64_t) (val) &						\
	(uint64_t) SPICE_UINT64_CONSTANT(0x0000000000ff0000)) << 24) |	\
      (((uint64_t) (val) &						\
	(uint64_t) SPICE_UINT64_CONSTANT(0x00000000ff000000)) <<  8) |	\
      (((uint64_t) (val) &						\
	(uint64_t) SPICE_UINT64_CONSTANT(0x000000ff00000000)) >>  8) |	\
      (((uint64_t) (val) &						\
	(uint64_t) SPICE_UINT64_CONSTANT(0x0000ff0000000000)) >> 24) |	\
      (((uint64_t) (val) &						\
	(uint64_t) SPICE_UINT64_CONSTANT(0x00ff000000000000)) >> 40) |	\
      (((uint64_t) (val) &						\
	(uint64_t) SPICE_UINT64_CONSTANT(0xff00000000000000)) >> 56)))

/* Arch specific stuff for speed
 */
#if defined (__GNUC__) && (__GNUC__ >= 2) && defined (__OPTIMIZE__)
#  if defined (__i386__)
#    define SPICE_BYTESWAP16_IA32(val) \
       (__extension__						\
	({ register uint16_t __v, __x = ((uint16_t) (val));	\
	   if (__builtin_constant_p (__x))			\
	     __v = SPICE_BYTESWAP16_CONSTANT (__x);		\
	   else							\
	     __asm__ ("rorw $8, %w0"				\
		      : "=r" (__v)				\
		      : "0" (__x)				\
		      : "cc");					\
	    __v; }))
#    if !defined (__i486__) && !defined (__i586__) \
	&& !defined (__pentium__) && !defined (__i686__) \
	&& !defined (__pentiumpro__) && !defined (__pentium4__)
#       define SPICE_BYTESWAP32_IA32(val) \
	  (__extension__					\
	   ({ register uint32_t __v, __x = ((uint32_t) (val));	\
	      if (__builtin_constant_p (__x))			\
		__v = SPICE_BYTESWAP32_CONSTANT (__x);	\
	      else						\
		__asm__ ("rorw $8, %w0\n\t"			\
			 "rorl $16, %0\n\t"			\
			 "rorw $8, %w0"				\
			 : "=r" (__v)				\
			 : "0" (__x)				\
			 : "cc");				\
	      __v; }))
#    else /* 486 and higher has bswap */
#       define SPICE_BYTESWAP32_IA32(val) \
	  (__extension__					\
	   ({ register uint32_t __v, __x = ((uint32_t) (val));	\
	      if (__builtin_constant_p (__x))			\
		__v = SPICE_BYTESWAP32_CONSTANT (__x);	\
	      else						\
		__asm__ ("bswap %0"				\
			 : "=r" (__v)				\
			 : "0" (__x));				\
	      __v; }))
#    endif /* processor specific 32-bit stuff */
#    define SPICE_BYTESWAP64_IA32(val) \
       (__extension__							\
	({ union { uint64_t __ll;					\
		   uint32_t __l[2]; } __w, __r;				\
	   __w.__ll = ((uint64_t) (val));				\
	   if (__builtin_constant_p (__w.__ll))				\
	     __r.__ll = SPICE_BYTESWAP64_CONSTANT (__w.__ll);		\
	   else								\
	     {								\
	       __r.__l[0] = SPICE_BYTESWAP32 (__w.__l[1]);		\
	       __r.__l[1] = SPICE_BYTESWAP32 (__w.__l[0]);		\
	     }								\
	   __r.__ll; }))
     /* Possibly just use the constant version and let gcc figure it out? */
#    define SPICE_BYTESWAP16(val) (SPICE_BYTESWAP16_IA32 (val))
#    define SPICE_BYTESWAP32(val) (SPICE_BYTESWAP32_IA32 (val))
#    define SPICE_BYTESWAP64(val) (SPICE_BYTESWAP64_IA32 (val))
#  elif defined (__ia64__)
#    define SPICE_BYTESWAP16_IA64(val) \
       (__extension__						\
	({ register uint16_t __v, __x = ((uint16_t) (val));	\
	   if (__builtin_constant_p (__x))			\
	     __v = SPICE_BYTESWAP16_CONSTANT (__x);		\
	   else							\
	     __asm__ __volatile__ ("shl %0 = %1, 48 ;;"		\
				   "mux1 %0 = %0, @rev ;;"	\
				    : "=r" (__v)		\
				    : "r" (__x));		\
	    __v; }))
#    define SPICE_BYTESWAP32_IA64(val) \
       (__extension__						\
	 ({ register uint32_t __v, __x = ((uint32_t) (val));	\
	    if (__builtin_constant_p (__x))			\
	      __v = SPICE_BYTESWAP32_CONSTANT (__x);		\
	    else						\
	     __asm__ __volatile__ ("shl %0 = %1, 32 ;;"		\
				   "mux1 %0 = %0, @rev ;;"	\
				    : "=r" (__v)		\
				    : "r" (__x));		\
	    __v; }))
#    define SPICE_BYTESWAP64_IA64(val) \
       (__extension__						\
	({ register uint64_t __v, __x = ((uint64_t) (val));	\
	   if (__builtin_constant_p (__x))			\
	     __v = SPICE_BYTESWAP64_CONSTANT (__x);		\
	   else							\
	     __asm__ __volatile__ ("mux1 %0 = %1, @rev ;;"	\
				   : "=r" (__v)			\
				   : "r" (__x));		\
	   __v; }))
#    define SPICE_BYTESWAP16(val) (SPICE_BYTESWAP16_IA64 (val))
#    define SPICE_BYTESWAP32(val) (SPICE_BYTESWAP32_IA64 (val))
#    define SPICE_BYTESWAP64(val) (SPICE_BYTESWAP64_IA64 (val))
#  elif defined (__x86_64__)
#    define SPICE_BYTESWAP32_X86_64(val) \
       (__extension__						\
	 ({ register uint32_t __v, __x = ((uint32_t) (val));	\
	    if (__builtin_constant_p (__x))			\
	      __v = SPICE_BYTESWAP32_CONSTANT (__x);		\
	    else						\
	     __asm__ ("bswapl %0"				\
		      : "=r" (__v)				\
		      : "0" (__x));				\
	    __v; }))
#    define SPICE_BYTESWAP64_X86_64(val) \
       (__extension__						\
	({ register uint64_t __v, __x = ((uint64_t) (val));	\
	   if (__builtin_constant_p (__x))			\
	     __v = SPICE_BYTESWAP64_CONSTANT (__x);		\
	   else							\
	     __asm__ ("bswapq %0"				\
		      : "=r" (__v)				\
		      : "0" (__x));				\
	   __v; }))
     /* gcc seems to figure out optimal code for this on its own */
#    define SPICE_BYTESWAP16(val) (SPICE_BYTESWAP16_CONSTANT (val))
#    define SPICE_BYTESWAP32(val) (SPICE_BYTESWAP32_X86_64 (val))
#    define SPICE_BYTESWAP64(val) (SPICE_BYTESWAP64_X86_64 (val))
#  else /* generic gcc */
#    define SPICE_BYTESWAP16(val) (SPICE_BYTESWAP16_CONSTANT (val))
#    define SPICE_BYTESWAP32(val) (SPICE_BYTESWAP32_CONSTANT (val))
#    define SPICE_BYTESWAP64(val) (SPICE_BYTESWAP64_CONSTANT (val))
#  endif
#else /* generic */
#  define SPICE_BYTESWAP16(val) (SPICE_BYTESWAP16_CONSTANT (val))
#  define SPICE_BYTESWAP32(val) (SPICE_BYTESWAP32_CONSTANT (val))
#  define SPICE_BYTESWAP64(val) (SPICE_BYTESWAP64_CONSTANT (val))
#endif /* generic */


/* detect endianess */
#undef SPICE_ENDIAN
#define SPICE_ENDIAN_LITTLE 4321
#define SPICE_ENDIAN_BIG    1234
#define SPICE_ENDIAN_PDP    2143

/* gcc already defined these, use them */
#if defined(__BYTE_ORDER__) && defined(__ORDER_LITTLE_ENDIAN__) \
    && defined(__ORDER_BIG_ENDIAN__) && defined(__ORDER_PDP_ENDIAN__)
#  if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#    define SPICE_ENDIAN SPICE_ENDIAN_LITTLE
#  elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#    define SPICE_ENDIAN SPICE_ENDIAN_BIG
#  elif __BYTE_ORDER__ == __ORDER_PDP_ENDIAN__
#    define SPICE_ENDIAN SPICE_ENDIAN_PDP
#  else
#    error __BYTE_ORDER__ not defined correctly
#  endif
#endif

/* use suggestions at http://sourceforge.net/p/predef/wiki/Endianness/ */
#ifndef SPICE_ENDIAN
#  if defined(__LITTLE_ENDIAN__) || defined(__ARMEL__) \
      || defined(__THUMBEL__) || defined(__AARCH64EL__) \
      || defined(_MIPSEL) || defined(__MIPSEL) || defined(__MIPSEL__) \
      || defined(__amd64__) || defined(__x86_64__) || defined(__i386__)
#    define SPICE_ENDIAN SPICE_ENDIAN_LITTLE
#  endif
#  if defined(__BIG_ENDIAN__) || defined(__ARMEB__) \
      || defined(__THUMBEB__) || defined(__AARCH64EB__) \
      || defined(_MIPSEB) || defined(__MIPSEB) || defined(__MIPSEB__)
#    ifdef SPICE_ENDIAN
#      error Both little and big endian detected
#    endif
#    define SPICE_ENDIAN SPICE_ENDIAN_BIG
#  endif
#endif

/* MS compiler */
#if !defined(SPICE_ENDIAN) && defined(_MSC_VER)
/* Windows support only little endian arm */
#  if defined(_M_IX86) || defined(_M_AMD64) || defined(_M_X64) \
      || defined(_M_ARM)
#    define SPICE_ENDIAN SPICE_ENDIAN_LITTLE
#  endif
#endif

#if !defined(SPICE_ENDIAN)
#error Unable to detect processor endianess
#endif

#if SPICE_ENDIAN == SPICE_ENDIAN_PDP
#error PDP endianess not supported by Spice
#endif


#if SPICE_ENDIAN == SPICE_ENDIAN_LITTLE
#define SPICE_MAGIC_CONST(s) \
    ((uint32_t)((s[0]&0xffu)|((s[1]&0xffu)<<8)|((s[2]&0xffu)<<16)|((s[3]&0xffu)<<24)))
#else
#define SPICE_MAGIC_CONST(s) \
    ((uint32_t)((s[3]&0xffu)|((s[2]&0xffu)<<8)|((s[1]&0xffu)<<16)|((s[0]&0xffu)<<24)))
#endif

#endif /* _H_SPICE_MACROS */
