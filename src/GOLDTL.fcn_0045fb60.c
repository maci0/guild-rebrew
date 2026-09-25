// FUNCTION: GOLDTL 0x45fb60
// SIZE: 234

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdarg.h>
#include "zutil.h"
#include "Develop/Units/vfs/gz_stream.h"

const char* __cdecl fcn_0045fb60(gzFile file, int* errnum)
{
	char* m;
	gz_stream* s = (gz_stream*) file;

	if (s == NULL) {
		*errnum = Z_STREAM_ERROR;
		return (const char*) ERR_MSG(Z_STREAM_ERROR);
	}
	*errnum = s->z_err;
	if (*errnum == Z_OK) {
		return (const char*) "";
	}
	m = (char*) (*errnum == Z_ERRNO ? "" : s->stream.msg);

	if (m == NULL || *m == '\0') {
		m = (char*) ERR_MSG(s->z_err);
	}
	if (s->msg != NULL) {
		free(s->msg);
	}
	s->msg = (char*) ALLOC(strlen(s->path) + strlen(m) + 3);
	strcpy(s->msg, s->path);
	strcat(s->msg, ": ");
	strcat(s->msg, m);
	return (const char*) s->msg;
}
