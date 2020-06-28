//
//  includes.h
//  C-ray
//
//  Created by Valtteri Koskivuori on 28/02/2015.
//  Copyright © 2015-2020 Valtteri Koskivuori. All rights reserved.
//

#pragma once

//Global constants
#define MAX_CRAY_VERTEX_COUNT 3
#define PIOVER180 0.017453292519943295769236907684886f
#define PI        3.141592653589793238462643383279502f
#define CRAY_MATERIAL_NAME_SIZE 256
#define CRAY_MESH_FILENAME_LENGTH 500

//Some macros
#define min(a,b) (((a) < (b)) ? (a) : (b))
#define max(a,b) (((a) > (b)) ? (a) : (b))
#define invsqrt(x) (1.0f / sqrtf(x))
#if defined(__GNUC__) || defined(__clang__)
#define unlikely(x) __builtin_expect(x, false)
#define likely(x)   __builtin_expect(x, true)
#else
#define unlikely(x) (x)
#define likely(x)   (x)
#endif

//Master include file
#ifdef __linux__
#include <signal.h>
#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE 500
#endif
#endif

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <float.h>
#include <stdint.h>

#ifdef WINDOWS
	#include <Windows.h>
	#include <time.h>
#else
	#include <uthread.h>
	#include <sys/time.h> //for gettimeofday()
#endif


