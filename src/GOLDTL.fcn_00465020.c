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

int __cdecl fcn_00465630(unzFile file);
int __cdecl fcn_00465160(unz_s* s, uInt* piSizeVar, uLong* poffset_local_extrafield, uInt* psize_local_extrafield);
int __cdecl fcn_004615b0(z_streamp z, int w, const char* version, int stream_size);

/* ADDRESS: GOLD 0x004680f0 */
/* ADDRESS: GOLDTL 0x00465020 */
int __cdecl fcn_00465020(unzFile file)
{
	int err = UNZ_OK;
	int Store;
	uInt iSizeVar;
	unz_s* s;
	file_in_zip_read_info_s* pfile_in_zip_read_info;
	uLong offset_local_extrafield;
	uInt size_local_extrafield;

	if (file == NULL) {
		return UNZ_PARAMERROR;
	}
	s = (unz_s*) file;
	if (!s->current_file_ok) {
		return UNZ_PARAMERROR;
	}

	if (s->pfile_in_zip_read != NULL) {
		fcn_00465630(file);
	}

	if (fcn_00465160(s, &iSizeVar, &offset_local_extrafield, &size_local_extrafield) != UNZ_OK) {
		return UNZ_BADZIPFILE;
	}

	pfile_in_zip_read_info = (file_in_zip_read_info_s*) ALLOC(sizeof(file_in_zip_read_info_s));
	if (pfile_in_zip_read_info == NULL) {
		return UNZ_INTERNALERROR;
	}

	pfile_in_zip_read_info->read_buffer = (char*) ALLOC(UNZ_BUFSIZE);
	pfile_in_zip_read_info->offset_local_extrafield = offset_local_extrafield;
	pfile_in_zip_read_info->size_local_extrafield = size_local_extrafield;
	pfile_in_zip_read_info->pos_local_extrafield = 0;

	if (pfile_in_zip_read_info->read_buffer == NULL) {
		TRYFREE(pfile_in_zip_read_info);
		return UNZ_INTERNALERROR;
	}

	pfile_in_zip_read_info->stream_initialised = 0;

	if ((s->cur_file_info.compression_method != 0) && (s->cur_file_info.compression_method != Z_DEFLATED)) {
		err = UNZ_BADZIPFILE;
	}
	Store = s->cur_file_info.compression_method == 0;

	pfile_in_zip_read_info->crc32_wait = s->cur_file_info.crc;
	pfile_in_zip_read_info->crc32 = 0;
	pfile_in_zip_read_info->compression_method = s->cur_file_info.compression_method;
	pfile_in_zip_read_info->file = s->file;
	pfile_in_zip_read_info->byte_before_the_zipfile = s->byte_before_the_zipfile;

	pfile_in_zip_read_info->stream.total_out = 0;

	if (!Store) {
		pfile_in_zip_read_info->stream.zalloc = (alloc_func) 0;
		pfile_in_zip_read_info->stream.zfree = (free_func) 0;
		pfile_in_zip_read_info->stream.opaque = (voidpf) 0;

		err = fcn_004615b0(&pfile_in_zip_read_info->stream, -MAX_WBITS, ZLIB_VERSION, sizeof(z_stream));
		if (err == Z_OK) {
			pfile_in_zip_read_info->stream_initialised = 1;
		}
	}
	pfile_in_zip_read_info->rest_read_compressed = s->cur_file_info.compressed_size;
	pfile_in_zip_read_info->rest_read_uncompressed = s->cur_file_info.uncompressed_size;

	pfile_in_zip_read_info->pos_in_zipfile = s->cur_file_info_internal.offset_curfile + SIZEZIPLOCALHEADER + iSizeVar;

	pfile_in_zip_read_info->stream.avail_in = (uInt) 0;

	s->pfile_in_zip_read = pfile_in_zip_read_info;
	return UNZ_OK;
}
