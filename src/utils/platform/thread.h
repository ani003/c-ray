//
//  thread.h
//  C-ray
//
//  Created by Valtteri on 29.3.2020.
//  Copyright © 2020 Valtteri Koskivuori. All rights reserved.
//

//Multi-platform threading
/**
 Thread information struct to communicate with main thread
 */
struct crThread {
#ifdef WINDOWS
	HANDLE thread_handle;
	DWORD thread_id;
#else
	uthread_t thread_id;
#endif
	int thread_num;
	bool threadComplete;
	
	bool paused; //SDL listens for P key pressed, which sets these, one for each thread.
	
	//Share info about the current tile with main thread
	int currentTileNum;
	int completedSamples;
	
	uint64_t totalSamples;
	
	long avgSampleTime; //Single tile pass
	
	struct renderer *renderer;
	struct texture *output;
	
	void *(*threadFunc)(void *);
};

/// Spawn a new C-ray platform abstracted thread
/// @param t Pointer to the thread to be spawned
int startThread(struct crThread *t);

/// Block until the given thread has terminated.
/// @param t Pointer to the thread to be checked.
void checkThread(struct crThread *t);

void yieldThread(void);
