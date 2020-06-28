//
//  main.c
//  C-ray
//
//  Created by Valtteri Koskivuori on 12/02/2015.
//  Copyright © 2015-2020 Valtteri Koskivuori. All rights reserved.
//

#include <stdlib.h>
#include <stdbool.h>
#include "main.h"

#include "c-ray.h"

#include <uthread.h>

void the_main(int argc, char **argv) {
	crInitialize();
	crLog("C-ray v%s [%.8s], © 2015-2020 Valtteri Koskivuori\n", crGetVersion(), crGitHash());
	
	crParseArgs(argc, argv);
	crInitRenderer();
	size_t bytes = 0;
	char *input = crOptionIsSet("inputFile") ? crLoadFile(crPathArg(), &bytes) : crReadStdin(&bytes);
	crSetAssetPath(crOptionIsSet("inputFile") ? crGetFilePath(crPathArg()) : "./");


	if (input) crLog("%zi bytes of input JSON loaded from %s, parsing.\n", bytes, crOptionIsSet("inputFile") ? "file" : "stdin");
	if (!input || crLoadSceneFromBuf(input)) {
		if (input) free(input);
		crDestroyRenderer();
		// return -1;
		return;
	}

	free(input);

	crRenderSingleFrame();
	crWriteImage();
	crDestroyRenderer();
	crDestroyOptions();
	crLog("Render finished, exiting.\n");
	return;
}

int main(int argc, char **argv) {
	uthread_init_main(the_main, argc, argv);
	// the_main(argc, argv);
	return 0;
}
