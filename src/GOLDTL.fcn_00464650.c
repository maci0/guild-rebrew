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

static const char unz_copyright[] = " unzip 0.15 Copyright 1998 Gilles Vollant ";

uLong __cdecl fcn_00464900(FILE* fin);
int __cdecl fcn_00464870(FILE* fin, uLong* pX);
int __cdecl fcn_004647e0(FILE* fin, uLong* pX);
int __cdecl fcn_00464e60(unzFile file);

/* ADDRESS: GOLD 0x00467830 */
/* ADDRESS: GOLDTL 0x00464650 */
unzFile __cdecl fcn_00464650(const char* path)
{
	unz_s us;
	unz_s* s;
	uLong central_pos, uL;
	FILE* fin;

	uLong number_disk;
	uLong number_disk_with_CD;
	uLong number_entry_CD;

	int err = UNZ_OK;

	if (unz_copyright[0] != ' ') {
		return NULL;
	}

	fin = fopen(path, "rb");
	if (fin == NULL) {
		return NULL;
	}

	central_pos = fcn_00464900(fin);
	if (central_pos == 0) {
		err = UNZ_ERRNO;
	}

	if (fseek(fin, central_pos, SEEK_SET) != 0) {
		err = UNZ_ERRNO;
	}

	if (fcn_00464870(fin, &uL) != UNZ_OK) {
		err = UNZ_ERRNO;
	}

	if (fcn_004647e0(fin, &number_disk) != UNZ_OK) {
		err = UNZ_ERRNO;
	}

	if (fcn_004647e0(fin, &number_disk_with_CD) != UNZ_OK) {
		err = UNZ_ERRNO;
	}

	if (fcn_004647e0(fin, &us.gi.number_entry) != UNZ_OK) {
		err = UNZ_ERRNO;
	}

	if (fcn_004647e0(fin, &number_entry_CD) != UNZ_OK) {
		err = UNZ_ERRNO;
	}

	if ((number_entry_CD != us.gi.number_entry) || (number_disk_with_CD != 0) || (number_disk != 0)) {
		err = UNZ_BADZIPFILE;
	}

	if (fcn_00464870(fin, &us.size_central_dir) != UNZ_OK) {
		err = UNZ_ERRNO;
	}

	if (fcn_00464870(fin, &us.offset_central_dir) != UNZ_OK) {
		err = UNZ_ERRNO;
	}

	if (fcn_004647e0(fin, &us.gi.size_comment) != UNZ_OK) {
		err = UNZ_ERRNO;
	}

	if ((central_pos < us.offset_central_dir + us.size_central_dir) && (err == UNZ_OK)) {
		err = UNZ_BADZIPFILE;
	}

	if (err != UNZ_OK) {
		fclose(fin);
		return NULL;
	}

	us.file = fin;
	us.byte_before_the_zipfile = central_pos - (us.offset_central_dir + us.size_central_dir);
	us.central_pos = central_pos;
	us.pfile_in_zip_read = NULL;

	s = (unz_s*) ALLOC(sizeof(unz_s));
	*s = us;
	fcn_00464e60((unzFile) s);
	return (unzFile) s;
}
