#include <unistd.h> // to use sleep in the main rutine
#include "tinySTM/src/atomic_ops/atomic_ops.h"
#define ATOMIC_OPS_joerg
#include "tinySTM/src/atomic.h"

int main() {
	long u=1000;
	while (u) {
//		--u;
		ATOMIC_FETCH_DEC_FULL(&u);
	}
//	return 0;
} 
