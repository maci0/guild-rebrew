#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "zlib.h"
#include "contrib/minizip/unzip.h"

#define UNZ_BUFSIZE (16384)
#define UNZ_MAXFILENAMEINZIP (256)
#define ALLOC(size) (malloc(size))
#define TRYFREE(p) \
	{ \
		if (p) \
			free(p); \
	}
#define SIZECENTRALDIRITEM (0x2e)
#define SIZEZIPLOCALHEADER (0x1e)
#define BUFREADCOMMENT (0x400)

// SIZE 0x4
typedef struct unz_file_info_internal_s {
	uLong offset_curfile;
} unz_file_info_internal;

// SIZE 0x7c
typedef struct {
	char* read_buffer;
	z_stream stream;

	uLong pos_in_zipfile;
	uLong stream_initialised;

	uLong offset_local_extrafield;
	uInt size_local_extrafield;
	uLong pos_local_extrafield;

	uLong crc32;
	uLong crc32_wait;
	uLong rest_read_compressed;
	uLong rest_read_uncompressed;
	FILE* file;
	uLong compression_method;
	uLong byte_before_the_zipfile;
} file_in_zip_read_info_s;

// SIZE 0x80
typedef struct {
	FILE* file;
	unz_global_info gi;
	uLong byte_before_the_zipfile;
	uLong num_file;
	uLong pos_in_central_dir;
	uLong current_file_ok;
	uLong central_pos;

	uLong size_central_dir;
	uLong offset_central_dir;

	unz_file_info cur_file_info;
	unz_file_info_internal cur_file_info_internal;
	file_in_zip_read_info_s* pfile_in_zip_read;
} unz_s;

// FUNCTION: GOLD 0x00467ae0
// SIZE: 295
// FUNCTION: GOLDTL 0x464900
// SIZE: 295
uLong __cdecl fcn_00464900(FILE* fin)
{
	unsigned char* buf;
	uLong uSizeFile;
	uLong uBackRead;
	uLong uMaxBack = 0xffff;
	uLong uPosFound = 0;

	if (fseek(fin, 0, SEEK_END) != 0) {
		return 0;
	}

	uSizeFile = ftell(fin);

	if (uMaxBack > uSizeFile) {
		uMaxBack = uSizeFile;
	}

	buf = (unsigned char*) ALLOC(BUFREADCOMMENT + 4);
	if (buf == NULL) {
		return 0;
	}

	uBackRead = 4;
	while (uBackRead < uMaxBack) {
		uLong uReadSize, uReadPos;
		int i;
		if (uBackRead + BUFREADCOMMENT > uMaxBack) {
			uBackRead = uMaxBack;
		} else {
			uBackRead += BUFREADCOMMENT;
		}
		uReadPos = uSizeFile - uBackRead;

		uReadSize = ((BUFREADCOMMENT + 4) < (uSizeFile - uReadPos)) ? (BUFREADCOMMENT + 4) : (uSizeFile - uReadPos);
		if (fseek(fin, uReadPos, SEEK_SET) != 0) {
			break;
		}

		if (fread(buf, (uInt) uReadSize, 1, fin) != 1) {
			break;
		}

		for (i = (int) uReadSize - 3; (i--) > 0;) {
			if (((*(buf + i)) == 0x50) && ((*(buf + i + 1)) == 0x4b) && ((*(buf + i + 2)) == 0x05) && ((*(buf + i + 3)) == 0x06)) {
				uPosFound = uReadPos + i;
				break;
			}
		}

		if (uPosFound != 0) {
			break;
		}
	}
	TRYFREE(buf);
	return uPosFound;
}
