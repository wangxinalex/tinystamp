# 1 "list_atomic.c"
# 1 "/home/jbs/src/tinystamp/libatomic_ops-1.1/tests//"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "list_atomic.c"
# 1 "../src/atomic_ops.h" 1
# 27 "../src/atomic_ops.h"
# 1 "/usr/include/assert.h" 1 3 4
# 37 "/usr/include/assert.h" 3 4
# 1 "/usr/include/features.h" 1 3 4
# 356 "/usr/include/features.h" 3 4
# 1 "/usr/include/sys/cdefs.h" 1 3 4
# 353 "/usr/include/sys/cdefs.h" 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 354 "/usr/include/sys/cdefs.h" 2 3 4
# 357 "/usr/include/features.h" 2 3 4
# 380 "/usr/include/features.h" 3 4
# 1 "/usr/include/gnu/stubs.h" 1 3 4



# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 5 "/usr/include/gnu/stubs.h" 2 3 4




# 1 "/usr/include/gnu/stubs-64.h" 1 3 4
# 10 "/usr/include/gnu/stubs.h" 2 3 4
# 381 "/usr/include/features.h" 2 3 4
# 38 "/usr/include/assert.h" 2 3 4
# 28 "../src/atomic_ops.h" 2
# 189 "../src/atomic_ops.h"
# 1 "../src/atomic_ops/sysdeps/gcc/x86_64.h" 1
# 24 "../src/atomic_ops/sysdeps/gcc/x86_64.h"
# 1 "../src/atomic_ops/sysdeps/gcc/../all_aligned_atomic_load_store.h" 1
# 27 "../src/atomic_ops/sysdeps/gcc/../all_aligned_atomic_load_store.h"
# 1 "../src/atomic_ops/sysdeps/gcc/../aligned_atomic_load_store.h" 1
# 28 "../src/atomic_ops/sysdeps/gcc/../aligned_atomic_load_store.h"
static __inline unsigned long
AO_load(volatile unsigned long *addr)
{
  ((void) (0));


  return *(unsigned long *)addr;
}



static __inline void
AO_store(volatile unsigned long *addr, unsigned long new_val)
{
  ((void) (0));
  (*(unsigned long *)addr) = new_val;
}
# 28 "../src/atomic_ops/sysdeps/gcc/../all_aligned_atomic_load_store.h" 2
# 1 "../src/atomic_ops/sysdeps/gcc/../char_atomic_load_store.h" 1
# 28 "../src/atomic_ops/sysdeps/gcc/../char_atomic_load_store.h"
static __inline unsigned char
AO_char_load(volatile unsigned char *addr)
{


  return (*(unsigned char *)addr);
}



static __inline void
AO_char_store(volatile unsigned char *addr, unsigned char new_val)
{
  (*(unsigned char *)addr) = new_val;
}
# 29 "../src/atomic_ops/sysdeps/gcc/../all_aligned_atomic_load_store.h" 2
# 1 "../src/atomic_ops/sysdeps/gcc/../short_aligned_atomic_load_store.h" 1
# 28 "../src/atomic_ops/sysdeps/gcc/../short_aligned_atomic_load_store.h"
static __inline unsigned short
AO_short_load(volatile unsigned short *addr)
{
  ((void) (0));


  return (*(unsigned short *)addr);
}



static __inline void
AO_short_store(volatile unsigned short *addr, unsigned short new_val)
{
  ((void) (0));
  (*(unsigned short *)addr) = new_val;
}
# 30 "../src/atomic_ops/sysdeps/gcc/../all_aligned_atomic_load_store.h" 2
# 1 "../src/atomic_ops/sysdeps/gcc/../int_aligned_atomic_load_store.h" 1
# 28 "../src/atomic_ops/sysdeps/gcc/../int_aligned_atomic_load_store.h"
static __inline unsigned int
AO_int_load(volatile unsigned int *addr)
{
  ((void) (0));


  return (*(unsigned int *)addr);
}



static __inline void
AO_int_store(volatile unsigned int *addr, unsigned int new_val)
{
  ((void) (0));
  (*(unsigned int *)addr) = new_val;
}
# 30 "../src/atomic_ops/sysdeps/gcc/../all_aligned_atomic_load_store.h" 2
# 25 "../src/atomic_ops/sysdeps/gcc/x86_64.h" 2
# 33 "../src/atomic_ops/sysdeps/gcc/x86_64.h"
# 1 "../src/atomic_ops/sysdeps/gcc/../ordered_except_wr.h" 1
# 30 "../src/atomic_ops/sysdeps/gcc/../ordered_except_wr.h"
# 1 "../src/atomic_ops/sysdeps/gcc/../read_ordered.h" 1
# 30 "../src/atomic_ops/sysdeps/gcc/../read_ordered.h"
static __inline void
AO_nop_read()
{
  __asm__ __volatile__("" : : : "memory");
}





static __inline unsigned long
AO_load_read(volatile unsigned long *addr)
{
  unsigned long result = AO_load(addr);
  __asm__ __volatile__("" : : : "memory");
  return result;
}
# 56 "../src/atomic_ops/sysdeps/gcc/../read_ordered.h"
static __inline unsigned long
AO_char_load_read(volatile unsigned char *addr)
{
  unsigned long result = AO_char_load(addr);
  __asm__ __volatile__("" : : : "memory");
  return result;
}
# 72 "../src/atomic_ops/sysdeps/gcc/../read_ordered.h"
static __inline unsigned long
AO_short_load_read(volatile unsigned short *addr)
{
  unsigned long result = AO_short_load(addr);
  __asm__ __volatile__("" : : : "memory");
  return result;
}
# 88 "../src/atomic_ops/sysdeps/gcc/../read_ordered.h"
static __inline unsigned long
AO_int_load_read(volatile unsigned int *addr)
{
  unsigned long result = AO_int_load(addr);
  __asm__ __volatile__("" : : : "memory");
  return result;
}
# 31 "../src/atomic_ops/sysdeps/gcc/../ordered_except_wr.h" 2

static __inline void
AO_nop_write()
{
  __asm__ __volatile__("" : : : "memory");


}





static __inline void
AO_store_write(volatile unsigned long *addr, unsigned long val)
{
  __asm__ __volatile__("" : : : "memory");
  AO_store(addr, val);
}
# 59 "../src/atomic_ops/sysdeps/gcc/../ordered_except_wr.h"
static __inline void
AO_char_store_write(volatile unsigned char *addr, unsigned char val)
{
  __asm__ __volatile__("" : : : "memory");
  AO_char_store(addr, val);
}
# 74 "../src/atomic_ops/sysdeps/gcc/../ordered_except_wr.h"
static __inline void
AO_short_store_write(volatile unsigned short *addr, unsigned short val)
{
  __asm__ __volatile__("" : : : "memory");
  AO_short_store(addr, val);
}
# 89 "../src/atomic_ops/sysdeps/gcc/../ordered_except_wr.h"
static __inline void
AO_int_store_write(volatile unsigned int *addr, unsigned int val)
{
  __asm__ __volatile__("" : : : "memory");
  AO_int_store(addr, val);
}
# 34 "../src/atomic_ops/sysdeps/gcc/x86_64.h" 2

# 1 "../src/atomic_ops/sysdeps/gcc/../test_and_set_t_is_char.h" 1
# 30 "../src/atomic_ops/sysdeps/gcc/../test_and_set_t_is_char.h"
typedef enum {AO_BYTE_TS_clear = 0, AO_BYTE_TS_set = 0xff} AO_BYTE_TS_val;
# 36 "../src/atomic_ops/sysdeps/gcc/x86_64.h" 2
# 58 "../src/atomic_ops/sysdeps/gcc/x86_64.h"
static __inline unsigned long
AO_fetch_and_add_full (volatile unsigned long *p, unsigned long incr)
{
  unsigned long result;

  __asm__ __volatile__ ("lock; xaddq %0, %1" :
   "=r" (result), "=m" (*p) : "0" (incr), "m" (*p)
   : "memory");
  return result;
}



static __inline unsigned char
AO_char_fetch_and_add_full (volatile unsigned char *p, unsigned char incr)
{
  unsigned char result;

  __asm__ __volatile__ ("lock; xaddb %0, %1" :
   "=r" (result), "=m" (*p) : "0" (incr), "m" (*p)
   : "memory");
  return result;
}



static __inline unsigned short
AO_short_fetch_and_add_full (volatile unsigned short *p, unsigned short incr)
{
  unsigned short result;

  __asm__ __volatile__ ("lock; xaddw %0, %1" :
   "=r" (result), "=m" (*p) : "0" (incr), "m" (*p)
   : "memory");
  return result;
}



static __inline unsigned short
AO_int_fetch_and_add_full (volatile unsigned int *p, unsigned int incr)
{
  unsigned int result;

  __asm__ __volatile__ ("lock; xaddl %0, %1" :
   "=r" (result), "=m" (*p) : "0" (incr), "m" (*p)
   : "memory");
  return result;
}




static __inline void
AO_or_full (volatile unsigned long *p, unsigned long incr)
{
  __asm__ __volatile__ ("lock; orq %1, %0" :
   "=m" (*p) : "r" (incr), "m" (*p) : "memory");
}



static __inline AO_BYTE_TS_val
AO_test_and_set_full(volatile unsigned char *addr)
{
  unsigned char oldval;

  __asm__ __volatile__("xchgb %0, %1"
  : "=r"(oldval), "=m"(*addr)
  : "0"(0xff), "m"(*addr) : "memory");
  return (AO_BYTE_TS_val)oldval;
}




static __inline int
AO_compare_and_swap_full(volatile unsigned long *addr,
          unsigned long old, unsigned long new_val)
{
  char result;
  __asm__ __volatile__("lock; cmpxchgq %3, %0; setz %1"
             : "=m"(*addr), "=q"(result)
         : "m"(*addr), "r" (new_val), "a"(old) : "memory");
  return (int) result;
}
# 190 "../src/atomic_ops.h" 2
# 279 "../src/atomic_ops.h"
# 1 "../src/atomic_ops/generalize.h" 1
# 146 "../src/atomic_ops/generalize.h"
   static __inline void AO_nop(void) {}




   static __inline void
   AO_nop_full()
   {
     unsigned char dummy = (unsigned long)AO_BYTE_TS_clear;
     AO_test_and_set_full(&dummy);
   }
# 1060 "../src/atomic_ops/generalize.h"
# 1 "../src/atomic_ops/generalize-small.h" 1
# 1061 "../src/atomic_ops/generalize.h" 2
# 280 "../src/atomic_ops.h" 2
# 2 "list_atomic.c" 2
# 15 "list_atomic.c"
void list_atomic(void)
{
  unsigned long *addr, val, newval, oldval;
  unsigned char tsaddr;
  long incr;


    "AO_nop(): ";
    AO_nop();




    "AO_load(addr):";
    AO_load(addr);




    "AO_store(addr, val):";
    AO_store(addr, val);




    "AO_test_and_set(tsaddr):";
    AO_test_and_set_full(tsaddr);




    "AO_fetch_and_add1(addr):";
    AO_fetch_and_add_full(addr, 1);




    "AO_fetch_and_sub1(addr):";
    AO_fetch_and_add_full(addr, (unsigned long)(-1));




    "AO_fetch_and_add(addr, incr):";
    AO_fetch_and_add_full(addr, incr);




    "AO_compare_and_swap(addr, oldval, newval):";
    AO_compare_and_swap_full(addr, oldval, newval);



}
# 86 "list_atomic.c"
void list_atomic_release(void)
{
  unsigned long *addr, val, newval, oldval;
  unsigned char tsaddr;
  long incr;





    "No AO_nop_release";





    "No AO_load_release";


    "AO_store_release(addr, val):";
    AO_store_write(addr, val);




    "AO_test_and_set_release(tsaddr):";
    AO_test_and_set_full(tsaddr);




    "AO_fetch_and_add1_release(addr):";
    AO_fetch_and_add_full(addr, 1);




    "AO_fetch_and_sub1_release(addr):";
    AO_fetch_and_add_full(addr, (unsigned long)(-1));




    "AO_fetch_and_add_release(addr, incr):";
    AO_fetch_and_add_full(addr, incr);




    "AO_compare_and_swap_release(addr, oldval, newval):";
    AO_compare_and_swap_full(addr, oldval, newval);



}
# 157 "list_atomic.c"
void list_atomic_acquire(void)
{
  unsigned long *addr, val, newval, oldval;
  unsigned char tsaddr;
  long incr;





    "No AO_nop_acquire";


    "AO_load_acquire(addr):";
    AO_load_read(addr);







    "No AO_store_acquire";


    "AO_test_and_set_acquire(tsaddr):";
    AO_test_and_set_full(tsaddr);




    "AO_fetch_and_add1_acquire(addr):";
    AO_fetch_and_add_full(addr, 1);




    "AO_fetch_and_sub1_acquire(addr):";
    AO_fetch_and_add_full(addr, (unsigned long)(-1));




    "AO_fetch_and_add_acquire(addr, incr):";
    AO_fetch_and_add_full(addr, incr);




    "AO_compare_and_swap_acquire(addr, oldval, newval):";
    AO_compare_and_swap_full(addr, oldval, newval);



}
# 228 "list_atomic.c"
void list_atomic_read(void)
{
  unsigned long *addr, val, newval, oldval;
  unsigned char tsaddr;
  long incr;


    "AO_nop_read(): ";
    AO_nop_full();




    "AO_load_read(addr):";
    AO_load_read(addr);







    "No AO_store_read";


    "AO_test_and_set_read(tsaddr):";
    AO_test_and_set_full(tsaddr);




    "AO_fetch_and_add1_read(addr):";
    AO_fetch_and_add_full(addr, 1);




    "AO_fetch_and_sub1_read(addr):";
    AO_fetch_and_add_full(addr, (unsigned long)(-1));




    "AO_fetch_and_add_read(addr, incr):";
    AO_fetch_and_add_full(addr, incr);




    "AO_compare_and_swap_read(addr, oldval, newval):";
    AO_compare_and_swap_full(addr, oldval, newval);



}
# 299 "list_atomic.c"
void list_atomic_write(void)
{
  unsigned long *addr, val, newval, oldval;
  unsigned char tsaddr;
  long incr;


    "AO_nop_write(): ";
    AO_nop_full();







    "No AO_load_write";


    "AO_store_write(addr, val):";
    AO_store_write(addr, val);




    "AO_test_and_set_write(tsaddr):";
    AO_test_and_set_full(tsaddr);




    "AO_fetch_and_add1_write(addr):";
    AO_fetch_and_add_full(addr, 1);




    "AO_fetch_and_sub1_write(addr):";
    AO_fetch_and_add_full(addr, (unsigned long)(-1));




    "AO_fetch_and_add_write(addr, incr):";
    AO_fetch_and_add_full(addr, incr);




    "AO_compare_and_swap_write(addr, oldval, newval):";
    AO_compare_and_swap_full(addr, oldval, newval);



}
# 370 "list_atomic.c"
void list_atomic_full(void)
{
  unsigned long *addr, val, newval, oldval;
  unsigned char tsaddr;
  long incr;


    "AO_nop_full(): ";
    AO_nop_full();




    "AO_load_full(addr):";
    (AO_nop_full(), AO_load_read(addr));




    "AO_store_full(addr, val):";
    (AO_store_write(addr, val), AO_nop_full());




    "AO_test_and_set_full(tsaddr):";
    AO_test_and_set_full(tsaddr);




    "AO_fetch_and_add1_full(addr):";
    AO_fetch_and_add_full(addr,1);




    "AO_fetch_and_sub1_full(addr):";
    AO_fetch_and_add_full(addr,(unsigned long)(-1));




    "AO_fetch_and_add_full(addr, incr):";
    AO_fetch_and_add_full(addr, incr);




    "AO_compare_and_swap_full(addr, oldval, newval):";
    AO_compare_and_swap_full(addr, oldval, newval);



}
# 441 "list_atomic.c"
void list_atomic_release_write(void)
{
  unsigned long *addr, val, newval, oldval;
  unsigned char tsaddr;
  long incr;





    "No AO_nop_release_write";





    "No AO_load_release_write";


    "AO_store_release_write(addr, val):";
    AO_store_write(addr, val);




    "AO_test_and_set_release_write(tsaddr):";
    AO_test_and_set_full(tsaddr);




    "AO_fetch_and_add1_release_write(addr):";
    AO_fetch_and_add_full(addr, 1);




    "AO_fetch_and_sub1_release_write(addr):";
    AO_fetch_and_add_full(addr, (unsigned long)(-1));




    "AO_fetch_and_add_release_write(addr, incr):";
    AO_fetch_and_add_full(addr, incr);




    "AO_compare_and_swap_release_write(addr, oldval, newval):";
    AO_compare_and_swap_full(addr, oldval, newval);



}
# 512 "list_atomic.c"
void list_atomic_acquire_read(void)
{
  unsigned long *addr, val, newval, oldval;
  unsigned char tsaddr;
  long incr;





    "No AO_nop_acquire_read";


    "AO_load_acquire_read(addr):";
    AO_load_read(addr);







    "No AO_store_acquire_read";


    "AO_test_and_set_acquire_read(tsaddr):";
    AO_test_and_set_full(tsaddr);




    "AO_fetch_and_add1_acquire_read(addr):";
    AO_fetch_and_add_full(addr, 1);




    "AO_fetch_and_sub1_acquire_read(addr):";
    AO_fetch_and_add_full(addr, (unsigned long)(-1));




    "AO_fetch_and_add_acquire_read(addr, incr):";
    AO_fetch_and_add_full(addr, incr);




    "AO_compare_and_swap_acquire_read(addr, oldval, newval):";
    AO_compare_and_swap_full(addr, oldval, newval);



}
