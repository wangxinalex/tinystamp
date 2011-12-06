// Initializing random variable seeds
ThLocals.seed__SRC = (unsigned) RAND_R(&CurrentThreadSeed);
ThLocals.seed__DST = (unsigned) RAND_R(&CurrentThreadSeed);
if(RandomDebug)
{
printf("Generating Random variable seeds for Thread %u...\n",ID);
printf("Seed of _SRC: %u\n", ThLocals.seed__SRC);
printf("Seed of _DST: %u\n", ThLocals.seed__DST);
}

// Initializing thread local variables (other than random variables).
ThLocals._NB = 8192;
ThLocals._k = 0;
