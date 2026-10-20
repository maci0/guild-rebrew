#include <stdio.h>
#include "zlib.h"
#include "contrib/minizip/unzip.h"

#define SIZEZIPLOCALHEADER (0x1e)

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

int __cdecl fcn_004647e0(FILE*, uLong*);
int __cdecl fcn_00464870(FILE*, uLong*);

/* ADDRESS: GOLDTL 0x00465160 */
int __cdecl fcn_00465160(unz_s* s, uInt* piSizeVar, uLong* poffset_local_extrafield, uInt* psize_local_extrafield)
{
	uLong uMagic, uData, uFlags;
	uLong size_filename;
	uLong size_extra_field;
	int err = UNZ_OK;

	*piSizeVar = 0;
	*poffset_local_extrafield = 0;
	*psize_local_extrafield = 0;

	if (fseek(s->file, s->cur_file_info_internal.offset_curfile + s->byte_before_the_zipfile, SEEK_SET) != 0) {
		return UNZ_ERRNO;
	}

	if (err == UNZ_OK) {
		if (fcn_00464870(s->file, &uMagic) != UNZ_OK) {
			err = UNZ_ERRNO;
		} else if (uMagic != 0x04034b50) {
			err = UNZ_BADZIPFILE;
		}
	}

	if (fcn_004647e0(s->file, &uData) != UNZ_OK) {
		err = UNZ_ERRNO;
	}

	if (fcn_004647e0(s->file, &uFlags) != UNZ_OK) {
		err = UNZ_ERRNO;
	}

	if (fcn_004647e0(s->file, &uData) != UNZ_OK) {
		err = UNZ_ERRNO;
	} else if ((err == UNZ_OK) && (uData != s->cur_file_info.compression_method)) {
		err = UNZ_BADZIPFILE;
	}

	if ((err == UNZ_OK) && (s->cur_file_info.compression_method != 0) && (s->cur_file_info.compression_method != Z_DEFLATED)) {
		err = UNZ_BADZIPFILE;
	}

	if (fcn_00464870(s->file, &uData) != UNZ_OK) {
		err = UNZ_ERRNO;
	}

	if (fcn_00464870(s->file, &uData) != UNZ_OK) {
		err = UNZ_ERRNO;
	} else if ((err == UNZ_OK) && (uData != s->cur_file_info.crc) && ((uFlags & 8) == 0)) {
		err = UNZ_BADZIPFILE;
	}

	if (fcn_00464870(s->file, &uData) != UNZ_OK) {
		err = UNZ_ERRNO;
	} else if ((err == UNZ_OK) && (uData != s->cur_file_info.compressed_size) && ((uFlags & 8) == 0)) {
		err = UNZ_BADZIPFILE;
	}

	if (fcn_00464870(s->file, &uData) != UNZ_OK) {
		err = UNZ_ERRNO;
	} else if ((err == UNZ_OK) && (uData != s->cur_file_info.uncompressed_size) && ((uFlags & 8) == 0)) {
		err = UNZ_BADZIPFILE;
	}

	if (fcn_004647e0(s->file, &size_filename) != UNZ_OK) {
		err = UNZ_ERRNO;
	} else if ((err == UNZ_OK) && (size_filename != s->cur_file_info.size_filename)) {
		err = UNZ_BADZIPFILE;
	}

	*piSizeVar += (uInt) size_filename;

	if (fcn_004647e0(s->file, &size_extra_field) != UNZ_OK) {
		err = UNZ_ERRNO;
	}
	*poffset_local_extrafield = s->cur_file_info_internal.offset_curfile + SIZEZIPLOCALHEADER + size_filename;
	*psize_local_extrafield = (uInt) size_extra_field;

	*piSizeVar += (uInt) size_extra_field;

	return err;
}
