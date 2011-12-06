/*
 * 
 * Author(s):
 *   Derin Harmanci <derin.harmanci@unine.ch>
 *
 * Copyright (c) 2008.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation, version 2
 * of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include "rng.h"

static unsigned long next = 1;

/* RAND_MAX assumed to be 32767 */
int myrand(void) {
#ifdef VERBOSE
    printf("Executing myrand()..\n");
#endif
    next = next * 1103515245 + 12345;
    return((unsigned)(next/65536) % 32768);
}

void mysrand(unsigned seed) {
#ifdef VERBOSE
    printf("Executing mysrand()..\n");
#endif
    next = seed;
}


/* RAND_MAX assumed to be 32767 */
int myrand_r(unsigned *SeedPtr) {
#ifdef VERBOSE
    printf("Executing myrand_r()..\n");
#endif
    *SeedPtr = *SeedPtr * 1103515245 + 12345;
    return((unsigned)(*SeedPtr/65536) % 32768);
}
