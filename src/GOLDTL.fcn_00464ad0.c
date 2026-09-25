

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "zlib.h"
#include "contrib/minizip/unzip.h"

#ifdef STDC
#  include <stddef.h>
#  include <string.h>
#  include <stdlib.h>
#endif
#ifdef NO_ERRNO_H
    extern int errno;
#else
#   include <errno.h>
#endif


#ifndef local
#  define local static
#endif
/* compile with -Dlocal if your debugger can't find static symbols */



#if !defined(unix) && !defined(CASESENSITIVITYDEFAULT_YES) && \
                      !defined(CASESENSITIVITYDEFAULT_NO)
#define CASESENSITIVITYDEFAULT_NO
#endif


#ifndef UNZ_BUFSIZE
#define UNZ_BUFSIZE (16384)
#endif

#ifndef UNZ_MAXFILENAMEINZIP
#define UNZ_MAXFILENAMEINZIP (256)
#endif

#ifndef ALLOC
# define ALLOC(size) (malloc(size))
#endif
#ifndef TRYFREE
# define TRYFREE(p) {if (p) free(p);}
#endif

#define SIZECENTRALDIRITEM (0x2e)
#define SIZEZIPLOCALHEADER (0x1e)


/* I've found an old Unix (a SunOS 4.1.3_U1) without all SEEK_* defined.... */

#ifndef SEEK_CUR
#define SEEK_CUR    1
#endif

#ifndef SEEK_END
#define SEEK_END    2
#endif

#ifndef SEEK_SET
#define SEEK_SET    0
#endif


/* unz_file_info_interntal contain internal info about a file in zipfile*/
// SIZE 0x4
typedef struct unz_file_info_internal_s
{
    uLong offset_curfile;/* relative offset of local header 4 bytes */
} unz_file_info_internal;


/* file_in_zip_read_info_s contain internal information about a file in zipfile,
    when reading and decompress it */
typedef struct
{
	char  *read_buffer;         /* internal buffer for compressed data */
	z_stream stream;            /* zLib stream structure for inflate */

	uLong pos_in_zipfile;       /* position in byte on the zipfile, for fseek*/
	uLong stream_initialised;   /* flag set if stream structure is initialised*/

	uLong offset_local_extrafield;/* offset of the local extra field */
	uInt  size_local_extrafield;/* size of the local extra field */
	uLong pos_local_extrafield;   /* position in the local extra field in read*/

	uLong crc32;                /* crc32 of all data uncompressed */
	uLong crc32_wait;           /* crc32 we must obtain after decompress all */
	uLong rest_read_compressed; /* number of byte to be decompressed */
	uLong rest_read_uncompressed;/*number of byte to be obtained after decomp*/
	FILE* file;                 /* io structore of the zipfile */
	uLong compression_method;   /* compression method (0==store) */
	uLong byte_before_the_zipfile;/* byte before the zipfile, (>0 for sfx)*/
} file_in_zip_read_info_s;


/* unz_s contain internal information about the zipfile
*/
typedef struct
{
	FILE* file;                 /* io structore of the zipfile */
	unz_global_info gi;       /* public global information */
	uLong byte_before_the_zipfile;/* byte before the zipfile, (>0 for sfx)*/
	uLong num_file;             /* number of the current file in the zipfile*/
	uLong pos_in_central_dir;   /* pos of the current file in the central dir*/
	uLong current_file_ok;      /* flag about the usability of the current file*/
	uLong central_pos;          /* position of the beginning of the central dir*/

	uLong size_central_dir;     /* size of the central directory  */
	uLong offset_central_dir;   /* offset of start of central directory with
								   respect to the starting disk number */

	unz_file_info cur_file_info; /* public info about the current file in zip*/
	unz_file_info_internal cur_file_info_internal; /* private info about it*/
    file_in_zip_read_info_s* pfile_in_zip_read; /* structure about the current
	                                    file if we are decompressing it */
} unz_s;

#define unzlocal_getShort fcn_004647e0
#define unzlocal_getLong fcn_00464870
#define unzlocal_DosDateToTmuDate fcn_00464e10

int fcn_004647e0(FILE* fin, uLong* pX);
int fcn_00464870(FILE* fin, uLong* pX);
void fcn_00464e10(uLong ulDosDate, tm_unz* ptm);

// FUNCTION: GOLDTL 0x00464ad0
// SIZE: 832

int fcn_00464ad0(file, pfile_info, pfile_info_internal, szFileName, fileNameBufferSize, extraField, extraFieldBufferSize, szComment,  commentBufferSize)
	unzFile file;
	unz_file_info *pfile_info;
	unz_file_info_internal *pfile_info_internal;
	char *szFileName;
	uLong fileNameBufferSize;
	void *extraField;
	uLong extraFieldBufferSize;
	char *szComment;
	uLong commentBufferSize;
{
	unz_s* s;
	unz_file_info file_info;
	int err=UNZ_OK;
	long lSeek=0;

	if (file==NULL)
		return UNZ_PARAMERROR;
	s=(unz_s*)file;
	if (fseek(s->file,s->pos_in_central_dir+s->byte_before_the_zipfile,SEEK_SET)!=0)
		err=UNZ_ERRNO;


	/* we check the magic */
	if (err==UNZ_OK) {
		uLong uMagic;
		if (unzlocal_getLong(s->file,&uMagic) != UNZ_OK)
			err=UNZ_ERRNO;
		else if (uMagic!=0x02014b50)
			err=UNZ_BADZIPFILE;
	}

	if (unzlocal_getShort(s->file,&file_info.version) != UNZ_OK)
		err=UNZ_ERRNO;

	if (unzlocal_getShort(s->file,&file_info.version_needed) != UNZ_OK)
		err=UNZ_ERRNO;

	if (unzlocal_getShort(s->file,&file_info.flag) != UNZ_OK)
		err=UNZ_ERRNO;

	if (unzlocal_getShort(s->file,&file_info.compression_method) != UNZ_OK)
		err=UNZ_ERRNO;

	if (unzlocal_getLong(s->file,&file_info.dosDate) != UNZ_OK)
		err=UNZ_ERRNO;

    unzlocal_DosDateToTmuDate(file_info.dosDate,&file_info.tmu_date);

	if (unzlocal_getLong(s->file,&file_info.crc) != UNZ_OK)
		err=UNZ_ERRNO;

	if (unzlocal_getLong(s->file,&file_info.compressed_size) != UNZ_OK)
		err=UNZ_ERRNO;

	if (unzlocal_getLong(s->file,&file_info.uncompressed_size) != UNZ_OK)
		err=UNZ_ERRNO;

	if (unzlocal_getShort(s->file,&file_info.size_filename) != UNZ_OK)
		err=UNZ_ERRNO;

	if (unzlocal_getShort(s->file,&file_info.size_file_extra) != UNZ_OK)
		err=UNZ_ERRNO;

	if (unzlocal_getShort(s->file,&file_info.size_file_comment) != UNZ_OK)
		err=UNZ_ERRNO;

	if (unzlocal_getShort(s->file,&file_info.disk_num_start) != UNZ_OK)
		err=UNZ_ERRNO;

	if (unzlocal_getShort(s->file,&file_info.internal_fa) != UNZ_OK)
		err=UNZ_ERRNO;

	if (unzlocal_getLong(s->file,&file_info.external_fa) != UNZ_OK)
		err=UNZ_ERRNO;

	{
		unz_file_info_internal file_info_internal;

		if (unzlocal_getLong(s->file,&file_info_internal.offset_curfile) != UNZ_OK)
			err=UNZ_ERRNO;

		lSeek+=file_info.size_filename;
		if ((err==UNZ_OK) && (szFileName!=NULL))
		{
			uLong uSizeRead ;
			if (file_info.size_filename<fileNameBufferSize)
			{
				*(szFileName+file_info.size_filename)='\0';
				uSizeRead = file_info.size_filename;
			}
			else
				uSizeRead = fileNameBufferSize;

			if ((file_info.size_filename>0) && (fileNameBufferSize>0))
				if (fread(szFileName,(uInt)uSizeRead,1,s->file)!=1)
					err=UNZ_ERRNO;
			lSeek -= uSizeRead;
		}

		
		if ((err==UNZ_OK) && (extraField!=NULL))
		{
			uLong uSizeRead ;
			if (file_info.size_file_extra<extraFieldBufferSize)
				uSizeRead = file_info.size_file_extra;
			else
				uSizeRead = extraFieldBufferSize;

			if (lSeek!=0)
				if (fseek(s->file,lSeek,SEEK_CUR)==0)
					lSeek=0;
				else
					err=UNZ_ERRNO;
			if ((file_info.size_file_extra>0) && (extraFieldBufferSize>0))
				if (fread(extraField,(uInt)uSizeRead,1,s->file)!=1)
					err=UNZ_ERRNO;
			lSeek += file_info.size_file_extra - uSizeRead;
		}
		else
			lSeek+=file_info.size_file_extra; 

		
		if ((err==UNZ_OK) && (szComment!=NULL))
		{
			uLong uSizeRead ;
			if (file_info.size_file_comment<commentBufferSize)
			{
				*(szComment+file_info.size_file_comment)='\0';
				uSizeRead = file_info.size_file_comment;
			}
			else
				uSizeRead = commentBufferSize;

			if (lSeek!=0)
				if (fseek(s->file,lSeek,SEEK_CUR)==0)
					lSeek=0;
				else
					err=UNZ_ERRNO;
			if ((file_info.size_file_comment>0) && (commentBufferSize>0))
				if (fread(szComment,(uInt)uSizeRead,1,s->file)!=1)
					err=UNZ_ERRNO;
			lSeek+=file_info.size_file_comment - uSizeRead;
		}
		else
			lSeek+=file_info.size_file_comment;

		if ((err==UNZ_OK) && (pfile_info!=NULL))
			*pfile_info=file_info;

		if ((err==UNZ_OK) && (pfile_info_internal!=NULL))
			*pfile_info_internal=file_info_internal;
	}

	return err;
}
