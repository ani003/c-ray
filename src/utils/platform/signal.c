//
//  signal.c
//  C-ray
//
//  Created by Valtteri on 7.4.2020.
//  Copyright © 2020 Valtteri Koskivuori. All rights reserved.
//

#include "signal.h"
#include <signal.h>

//Signal handling
#ifndef WASM
void (*signal(int signo, void (*func )(int)))(int);
typedef void sigfunc(int);
sigfunc *signal(int, sigfunc*);
#endif

int registerHandler(enum sigtype type, void (*handler)(int)) {
	#ifndef WASM
	int sig = 0;
	switch (type) {
		case sigint:
			sig = SIGINT;
			break;
		case sigabrt:
			sig = SIGABRT;
			break;
		default:
			sig = SIGINT;
			break;
	}
	
	if (signal(sig, handler) == SIG_ERR) {
		return -1;
	}
	#endif
	return 0;
}
