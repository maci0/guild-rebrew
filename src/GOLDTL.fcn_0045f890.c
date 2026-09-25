#include <stdio.h>
#include <string.h>
#include "zutil.h"
#include "Develop/Units/vfs/gz_stream.h"

#define Z_BUFSIZE 16384
#define ALLOC(size) malloc(size)

int __cdecl fcn_0045f630(gzFile file, const voidp buf, unsigned len);
int __cdecl fcn_0045f9e0(gzFile file);
int __cdecl gzread(gzFile file, voidp buf, unsigned len);

// FUNCTION: GOLD 0x463490
// SIZE: 332
// FUNCTION: GOLDTL 0x45f890
// SIZE: 332
z_off_t __cdecl fcn_0045f890(gzFile file, z_off_t offset, int whence)
{
	gz_stream* s = (gz_stream*) file;

	if (s == NULL || whence == SEEK_END || s->z_err == Z_ERRNO || s->z_err == Z_DATA_ERROR) {
		return -1L;
	}

	if (s->mode == 'w') {
		if (whence == SEEK_SET) {
			offset -= s->stream.total_in;
		}
		if (offset < 0) {
			return -1L;
		}

		if (s->inbuf == Z_NULL) {
			s->inbuf = (Byte*) ALLOC(Z_BUFSIZE);
			zmemzero(s->inbuf, Z_BUFSIZE);
		}
		while (offset > 0) {
			uInt size = Z_BUFSIZE;
			if (offset < Z_BUFSIZE) {
				size = (uInt) offset;
			}

			size = fcn_0045f630(file, s->inbuf, size);
			if (size == 0) {
				return -1L;
			}

			offset -= size;
		}
		return (z_off_t) s->stream.total_in;
	}

	if (whence == SEEK_CUR) {
		offset += s->stream.total_out;
	}
	if (offset < 0) {
		return -1L;
	}

	if (s->transparent) {
		s->stream.avail_in = 0;
		s->stream.next_in = s->inbuf;
		if (fseek(s->file, offset, SEEK_SET) < 0) {
			return -1L;
		}

		s->stream.total_in = s->stream.total_out = (uLong) offset;
		return offset;
	}

	if ((uLong) offset >= s->stream.total_out) {
		offset -= s->stream.total_out;
	} else if (fcn_0045f9e0(file) < 0) {
		return -1L;
	}

	if (offset != 0 && s->outbuf == Z_NULL) {
		s->outbuf = (Byte*) ALLOC(Z_BUFSIZE);
	}
	while (offset > 0) {
		int size = Z_BUFSIZE;
		if (offset < Z_BUFSIZE) {
			size = (int) offset;
		}

		size = gzread(file, s->outbuf, (uInt) size);
		if (size <= 0) {
			return -1L;
		}
		offset -= size;
	}
	return (z_off_t) s->stream.total_out;
}
