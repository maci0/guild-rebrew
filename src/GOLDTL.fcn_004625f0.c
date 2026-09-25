// FUNCTION: GOLDTL 0x4625f0
// SIZE: 173

#include <stdio.h>
#include "zlib.h"

void __cdecl fcn_00462500(const char*);
const char* __cdecl fcn_0045fb60(gzFile, int*);
int __cdecl fcn_0045fae0(gzFile);

void __cdecl fcn_004625f0(gzFile in, FILE* out)
{
	char buf[16384];
	int len;
	int err;

	for (;;) {
		len = gzread(in, buf, sizeof(buf));
		if (len < 0) {
			fcn_00462500(fcn_0045fb60(in, &err));
		}
		if (len == 0) {
			break;
		}
		if ((int) fwrite(buf, 1, (unsigned) len, out) != len) {
			fcn_00462500("failed fwrite");
		}
	}
	if (fclose(out)) {
		fcn_00462500("failed fclose");
	}
	if (fcn_0045fae0(in) != Z_OK) {
		fcn_00462500("failed gzclose");
	}
}
