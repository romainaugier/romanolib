/* SPDX-License-Identifier: BSD-3-Clause */
/* Copyright (c) 2023 - Present Romain Augier */
/* All rights reserved. */

#pragma once

#if !defined(__LIBROMANO)
#define __LIBROMANO

#if defined(_MSC_VER)
#define ROMANO_MSVC
#pragma warning(disable:4711) /* function selected for automatic inline expansion */
#elif defined(__GNUC__)
#define ROMANO_GCC
#elif defined(__clang__)
#define ROMANO_CLANG
#endif /* defined(_MSC_VER) */

#if !defined(ROMANO_VERSION_STR)
#define ROMANO_VERSION_STR "Debug"
#endif /* !defined(ROMANO_VERSION_STR) */

#include <stddef.h>
#include <stdint.h>

#if INTPTR_MAX == INT64_MAX || defined(__x86_64__)
#define ROMANO_X64
#define ROMANO_SIZEOF_PTR 8
#elif INTPTR_MAX == INT32_MAX
#define ROMANO_X86
#define ROMANO_SIZEOF_PTR 4
#endif /* INTPTR_MAX == INT64_MAX || defined(__x86_64__) */

#if defined(_WIN32)
#define ROMANO_WIN
#if !defined(WIN32_LEAN_AND_MEAN)
#define WIN32_LEAN_AND_MEAN
#endif /* !defined(WIN32_LEAN_AND_MEAN) */
#if defined(ROMANO_X64)
#define ROMANO_PLATFORM_STR "WIN64"
#else
#define ROMANO_PLATFORM_STR "WIN32"
#endif /* defined(ROMANO_x64) */
#elif defined(__linux__)
#define ROMANO_LINUX
#if defined(ROMANO_X64)
#define ROMANO_PLATFORM_STR "LINUX64"
#else
#define ROMANO_PLATFORM_STR "LINUX32"
#endif /* defined(ROMANO_X64) */
#elif defined(__APPLE__)
#define ROMANO_APPLE
#if defined(ROMANO_X64)
#define ROMANO_PLATFORM_STR "APPLE64"
#else
#define ROMANO_PLATFORM_STR "APPLE32"
#endif /* defined(ROMANO_X64) */
#elif defined(__OpenBSD__)
#define ROMANO_OPENBSD
#if defined(ROMANO_X64)
#define ROMANO_PLATFORM_STR "OPENBSD64"
#else
#define ROMANO_PLATFORM_STR "OPENBSD32"
#endif /* defined(ROMANO_X64) */
#elif defined(__NetBSD__) 
#define ROMANO_NETBSD
#elif defined(__FreeBSD__) 
#define ROMANO_FREEBSD
#elif defined(__DragonFly__)
#define ROMANO_DRAGONFLY
#endif /* defined(_WIN32) */

#define ROMANO_BYTE_ORDER_UNDEFINED 0
#define ROMANO_BYTE_ORDER_LITTLE_ENDIAN __ORDER_LITTLE_ENDIAN__
#define ROMANO_BYTE_ORDER_BIG_ENDIAN __ORDER_BIG_ENDIAN__

#define ROMANO_BYTE_ORDER __BYTE_ORDER__

#if defined(__STDC__)
#  if defined(__STDC_VERSION__)
#    if (__STDC_VERSION__ >= 201710L)
#      define ROMANO_C_STANDARD 2018
#    elif (__STDC_VERSION__ >= 201112L)
#      define ROMANO_C_STANDARD 2011
#    elif (__STDC_VERSION__ >= 199901L)
#      define ROMANO_C_STANDARD 1999
#    elif (__STDC_VERSION__ >= 199409L)
#      define ROMANO_C_STANDARD 1995
#    endif
#  else
#      define ROMANO_C_STANDARD 1990
#  endif
#else
#      define ROMANO_C_STANDARD 1972
#endif /* defined(__STDC__) */

#if ROMANO_C_STANDARD >= 1999
#define ROMANO_RESTRICT restrict
#elif defined(ROMANO_MSVC)
#define ROMANO_RESTRICT __restrict
#else
#define ROMANO_RESTRICT 
#endif /* ROMANO_C_STANDARD >= 1999 */

#if defined(ROMANO_WIN)
#if defined(ROMANO_MSVC)
#define ROMANO_EXPORT __declspec(dllexport)
#define ROMANO_IMPORT __declspec(dllimport)
#elif defined(ROMANO_GCC) || defined(ROMANO_CLANG)
#define ROMANO_EXPORT __attribute__((dllexport))
#define ROMANO_IMPORT __attribute__((dllimport))
#endif /* defined(ROMANO_MSVC) */
#elif defined(ROMANO_LINUX)
#define ROMANO_EXPORT __attribute__((visibility("default")))
#define ROMANO_IMPORT
#endif /* defined(ROMANO_WIN) */

#if defined(ROMANO_MSVC)
#define ROMANO_FORCE_INLINE __forceinline
#define ROMANO_LIB_ENTRY
#define ROMANO_LIB_EXIT
#elif defined(ROMANO_GCC)
#define ROMANO_FORCE_INLINE inline __attribute__((always_inline)) 
#define ROMANO_LIB_ENTRY __attribute__((constructor))
#define ROMANO_LIB_EXIT __attribute__((destructor))
#elif defined(ROMANO_CLANG)
#define ROMANO_FORCE_INLINE __attribute__((always_inline))
#define ROMANO_LIB_ENTRY __attribute__((constructor))
#define ROMANO_LIB_EXIT __attribute__((destructor))
#endif /* defined(ROMANO_MSVC) */

#if defined(ROMANO_GCC) || defined(ROMANO_CLANG)
#define	ROMANO_LIKELY(x)	__builtin_expect((x) != 0, 1)
#define	ROMANO_UNLIKELY(x)	__builtin_expect((x) != 0, 0)
#else
#define	ROMANO_LIKELY(x) (x)
#define	ROMANO_UNLIKELY(x) (x)
#endif /* defined(ROMANO_GCC) || defined(ROMANO_CLANG) */

#if defined(ROMANO_BUILD_SHARED)
#define ROMANO_API ROMANO_EXPORT
#else
#define ROMANO_API ROMANO_IMPORT
#endif /* defined(ROMANO_BUILD_SHARED) */

#if defined __cplusplus
#define ROMANO_CPP_ENTER extern "C" {
#define ROMANO_CPP_END }
#else
#define ROMANO_CPP_ENTER
#define ROMANO_CPP_END
#endif /* DEFINED __cplusplus */

#if !defined NULL
#define NULL (void*)0
#endif /* !defined NULL */

#if defined(ROMANO_WIN)
#define ROMANO_FUNCTION __FUNCTION__
#elif defined(ROMANO_GCC) || defined(ROMANO_CLANG)
#define ROMANO_FUNCTION __PRETTY_FUNCTION__
#endif /* ROMANO_WIN */

#define ROMANO_STATIC_FUNCTION static

#define CONCAT_(prefix, suffix)     prefix##suffix
#define CONCAT(prefix, suffix)      CONCAT_(prefix, suffix)

#define STATIC_ASSERT(expr)                             \
    struct CONCAT(__outscope_assert_, __COUNTER__)      \
    {                                                   \
        char                                            \
        outscope_assert                                 \
        [2*(expr)-1];                                   \
                                                        \
    } CONCAT(__outscope_assert_, __COUNTER__)

#define ROMANO_NOT_IMPLEMENTED "Function "ROMANO_FUNCTION" not implemented" 

#if defined(ROMANO_MSVC)
#define ROMANO_PACKED_STRUCT(__struct__) __pragma(pack(push, 1)) __struct__ __pragma(pack(pop))
#elif defined(ROMANO_GCC) || defined(ROMANO_CLANG)
#define ROMANO_PACKED_STRUCT(__struct__) __struct__ __attribute__((__packed__))
#else
#define ROMANO_PACKED_STRUCT(__struct__) __struct__
#endif /* defined(ROMANO_MSVC) */

#if defined(ROMANO_MSVC)
#define dump_struct(s) 
#elif defined(ROMANO_CLANG)
#define dump_struct(s) __builtin_dump_struct(s, printf)
#elif defined(ROMANO_GCC)
#define dump_struct(s) 
#endif /* defined(ROMANO_MSVC) */

#if defined(DEBUG_BUILD)
#define ROMANO_DEBUG 1
#else
#define ROMANO_DEBUG 0
#endif /* defined(DEBUG_BUILD) */

#endif /* !defined(__LIBROMANO) */
