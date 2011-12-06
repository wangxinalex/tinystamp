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

#ifndef __TM_INTERFACE_______
#define __TM_INTERFACE_______


#if defined ( NO_STM )
   #include "no_stm.h"
#elif defined ( TINY_STM_NEW )
   #include "tinySTM_new.h"
#elif defined ( NEXTGEN )
   #include "tinySTM_new.h"
#elif defined ( TINY_STM_OLD )
   #include "tinySTM_old.h"
#elif defined ( TL2 )
   #include "tl2_interface.h"
#elif defined ( RSTM )
   #include "rstm.h"
#elif defined ( ENNALS )
   #include "ennals_stm.h"
#elif defined ( SWISS_TM )
   #include "swisstm.h"
#elif defined ( WSTM )
   #include "wstm.h"
#endif


#endif


