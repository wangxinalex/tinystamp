// Initializing random variable seeds
ThLocals.seed__NB = (unsigned) RAND_R(&CurrentThreadSeed);
if(RandomDebug)
{
printf("Generating Random variable seeds for Thread %u...\n",ID);
printf("Seed of _NB: %u\n", ThLocals.seed__NB);
}

// Initializing thread local variables (other than random variables).
ThLocals._SIZE = 3;
ThLocals._f = 0;
ThLocals._v = 0;
ThLocals._k = 0;
