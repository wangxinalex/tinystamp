// Initializing random variable seeds
ThLocals.seed__R = (unsigned) RAND_R(&CurrentThreadSeed);
if(RandomDebug)
{
printf("Generating Random variable seeds for Thread %u...\n",ID);
printf("Seed of _R: %u\n", ThLocals.seed__R);
}

// Initializing thread local variables (other than random variables).
ThLocals._i = 0;
