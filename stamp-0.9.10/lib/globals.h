#ifndef GLOBALS_H
#define GLOBALS_H 1

static volatile char*    global_kill;           // array of flabbits to kill threads
static THREAD_LOCAL_T    global_threadId;

#endif
