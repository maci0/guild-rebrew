// FUNCTION: GOLDTL 0x45f6d0
// SIZE: 95

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdarg.h>
#include "zutil.h"
#include "Develop/Units/vfs/gz_stream.h"

int __cdecl fcn_0045f630(gzFile, const voidp, unsigned);

int __cdecl fcn_0045f6d0(gzFile file, const char* format, ...)
{
	char buf[4096];
	va_list va;
	int len;

	va_start(va, format);
	(void) vsprintf(buf, format, va);
	va_end(va);
	len = strlen(buf);
	if (len <= 0) {
		return 0;
	}
	return fcn_0045f630(file, buf, (unsigned) len);
}
