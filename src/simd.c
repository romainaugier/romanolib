/* SPDX-License-Identifier: BSD-3-Clause */
/* Copyright (c) 2023 - Present Romain Augier */
/* All rights reserved. */

#include <libromano/simd.h>

#include <string.h>

static int _vectorization_mode = 0;

void ROMANO_DLL_ENTRY check_vectorization() 
{
    int regs[4];

    cpuid(regs, 1);

    if(getenv("LIBROMANO_VECTORIZATION") != NULL)
    {
        char* env_val = getenv("LIBROMANO_VECTORIZATION");

        if(strcmp(env_val, "0") == 0)
        {
            return;
        } 
        else if(strcmp(env_val, "1") == 0)
        {
            _vectorization_mode = VectorizationMode_SSE;
        }
        else if(strcmp(env_val, "2") == 0)
        {
            _vectorization_mode = VectorizationMode_AVX;
        }
    }
    else
    {
        if(regs[2] & (1 << 28))
        {
            _vectorization_mode = VectorizationMode_AVX;
        }
        else if(regs[3] & (1 << 25))
        {
            _vectorization_mode = VectorizationMode_SSE;
        }
        else
        {
            return;
        }
    }
}



int simd_has_sse(void)
{
    return _vectorization_mode >= 1;
}

int simd_has_avx(void)
{
    return _vectorization_mode >= 2;
}

vectorization_mode simd_get_vectorization_mode(void)
{
    return _vectorization_mode;
}