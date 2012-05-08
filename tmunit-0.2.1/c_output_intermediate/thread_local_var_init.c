// Initializing random variable seeds
ThLocals.seed__RAND = (unsigned) RAND_R(&CurrentThreadSeed);
if(RandomDebug)
{
printf("Generating Random variable seeds for Thread %u...\n",ID);
printf("Seed of _RAND: %u\n", ThLocals.seed__RAND);
}

// Initializing thread local variables (other than random variables).
ThLocals._wp = 2;
ThLocals._t = 0;
ThLocals._rep = 0;
ThLocals._cond = 1;
ThLocals._size = 1;
ThLocals.k = 0;
