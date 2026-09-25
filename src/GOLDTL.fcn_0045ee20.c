#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "zutil.h"
#include "Develop/Units/vfs/gz_stream.h"

#define Z_BUFSIZE 16384
#define ALLOC(size) malloc(size)

extern int g_67bd70[2];

uLong __cdecl fcn_0045d600(uLong crc, const Bytef* buf, uInt len);
int __cdecl fcn_0045d770(z_streamp strm, int level, int method, int windowBits, int memLevel, int strategy, const char* version, int stream_size);
int __cdecl fcn_004615b0(z_streamp strm, int windowBits, const char* version, int stream_size);
int __cdecl fcn_0045f2c0(gz_stream* s);
void __cdecl fcn_0045f110(gz_stream* s);

// FUNCTION: GOLDTL 0x45ee20
// SIZE: 566
gzFile __cdecl fcn_0045ee20(const char* path, const char* mode, int fd)
{
	int err;
	int level = Z_DEFAULT_COMPRESSION;
	int strategy = Z_DEFAULT_STRATEGY;
	char* p = (char*) mode;
	gz_stream* s;
	char fmode[80];
	char* m = fmode;

	if (!path || !mode) {
		return Z_NULL;
	}

	s = (gz_stream*) ALLOC(sizeof(gz_stream));
	if (!s) {
		return Z_NULL;
	}

	s->stream.zalloc = (alloc_func) 0;
	s->stream.zfree = (free_func) 0;
	s->stream.opaque = (voidpf) 0;
	s->stream.next_in = s->inbuf = Z_NULL;
	s->stream.next_out = s->outbuf = Z_NULL;
	s->stream.avail_in = s->stream.avail_out = 0;
	s->file = NULL;
	s->z_err = Z_OK;
	s->z_eof = 0;
	s->crc = fcn_0045d600(0L, Z_NULL, 0);
	s->msg = NULL;
	s->transparent = 0;

	s->path = (char*) ALLOC(strlen(path) + 1);
	if (s->path == NULL) {
		return fcn_0045f2c0(s), (gzFile) Z_NULL;
	}
	strcpy(s->path, path);

	s->mode = '\0';
	do {
		if (*p == 'r') {
			s->mode = 'r';
		}
		if (*p == 'w' || *p == 'a') {
			s->mode = 'w';
		}
		if (*p >= '0' && *p <= '9') {
			level = *p - '0';
		} else if (*p == 'f') {
			strategy = Z_FILTERED;
		} else if (*p == 'h') {
			strategy = Z_HUFFMAN_ONLY;
		} else {
			*m++ = *p;
		}
	} while (*p++ && m != fmode + sizeof(fmode));
	if (s->mode == '\0') {
		return fcn_0045f2c0(s), (gzFile) Z_NULL;
	}

	if (s->mode == 'w') {
		err = fcn_0045d770(&(s->stream), level, Z_DEFLATED, -MAX_WBITS, DEF_MEM_LEVEL, strategy, ZLIB_VERSION, sizeof(z_stream));

		s->stream.next_out = s->outbuf = (Byte*) ALLOC(Z_BUFSIZE);
		if (err != Z_OK || s->outbuf == Z_NULL) {
			return fcn_0045f2c0(s), (gzFile) Z_NULL;
		}
	} else {
		s->stream.next_in = s->inbuf = (Byte*) ALLOC(Z_BUFSIZE);

		err = fcn_004615b0(&(s->stream), -MAX_WBITS, ZLIB_VERSION, sizeof(z_stream));
		if (err != Z_OK || s->inbuf == Z_NULL) {
			return fcn_0045f2c0(s), (gzFile) Z_NULL;
		}
	}
	s->stream.avail_out = Z_BUFSIZE;

	errno = 0;
	s->file = fd < 0 ? F_OPEN(path, fmode) : (FILE*) fdopen(fd, fmode);

	if (s->file == NULL) {
		return fcn_0045f2c0(s), (gzFile) Z_NULL;
	}
	if (s->mode == 'w') {
		fprintf(s->file, "%c%c%c%c%c%c%c%c%c%c", g_67bd70[0], g_67bd70[1], Z_DEFLATED, 0, 0, 0, 0, 0, 0, OS_CODE);
		s->startpos = 10L;
	} else {
		fcn_0045f110(s);
		s->startpos = (ftell(s->file) - s->stream.avail_in);
	}

	return (gzFile) s;
}
