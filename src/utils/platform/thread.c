//
//  thread.c
//  C-ray
//
//  Created by Valtteri on 29.3.2020.
//  Copyright © 2020 Valtteri Koskivuori. All rights reserved.
//

#ifdef WINDOWS
#include <Windows.h>
#else
#include <uthread.h>
#endif

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#include "thread.h"
#include "../logging.h"

// Multiplatform thread stub
#ifdef WINDOWS
DWORD WINAPI threadStub(LPVOID arg) {
#elif defined(WASM)
void threadStub(void *arg) {
#else
void *threadStub(void *arg) {
#endif
	((struct crThread*)arg)->threadFunc(arg);
}

void checkThread(struct crThread *t) {
#ifdef WINDOWS
	WaitForSingleObjectEx(t->thread_handle, INFINITE, FALSE);
#elif defined(WASM)
	if (uthread_join(t->thread_id, NULL)) {
		logr(warning, "Thread %i frozen.", t->thread_num);
	}
#else
	// if (pthread_join(t->thread_id, NULL)) {
	// 	logr(warning, "Thread %i frozen.", t->thread_num);
	// }

	if (uthread_join(t->thread_id, NULL)) {
		logr(warning, "Thread %i frozen.", t->thread_num);
	}
#endif
}

int startThread(struct crThread *t) {
#ifdef WINDOWS
	t->thread_handle = CreateThread(NULL, 0, threadStub, t, 0, &t->thread_id);
	if (t->thread_handle == NULL) return -1;
	return 0;
#elif defined(WASM)

	// threadStub(t);
	uthread_create(&t->thread_id, threadStub, t);

	return 0;

#else
	// pthread_attr_t attribs;
	// pthread_attr_init(&attribs);
	// pthread_attr_setdetachstate(&attribs, PTHREAD_CREATE_JOINABLE);
	// int ret = pthread_create(&t->thread_id, &attribs, threadStub, t);
	// pthread_attr_destroy(&attribs);

	int ret = uthread_create(&t->thread_id, threadStub, t);

	return ret;
#endif
}


// void yieldThread() {
// 	uthread_yield();
// }