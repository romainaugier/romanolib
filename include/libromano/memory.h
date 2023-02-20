// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2023 - Present Romain Augier
// All rights reserved.

#pragma once

#if !defined(__LIBROMANO_MEMORY)
#define __LIBROMANO_MEMORY

#include <stdlib.h>

#include "libromano/libromano.h"

ROMANO_CPP_ENTER

#if defined(ROMANO_DEBUG_MEMORY)

// Memory debug utility function, just malloc with a log of where it happens 
ROMANOAPI void* debug_malloc_override(size_t size,
                                      const char* line,
                                      const char* file);

// Memory debug utility function, just free with a log of where it happens
ROMANOAPI void debug_free_override(void* ptr,
                                   const char* line,
                                   const char* file);

#define malloc(size) debug_malloc_override(size, __LINE__, __FILE__)
#define free(ptr) debug_free_override(pt, __LINE__, __FILE__)

#endif // defined(ROMANO_DEBUG_MEMORY)

ROMANO_CPP_END

#endif // __LIBROMANO_MEMORY