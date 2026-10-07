// FUNCTION: GOLDTL 0x464500

#include "zlib.h"

int __cdecl fcn_00464500(Bytef* dest, uLongf* destLen, const Bytef* source, uLong sourceLen)
{
	z_stream stream;
	int err;

	stream.next_in = (Bytef*) source;
	stream.avail_in = (uInt) sourceLen;
	if ((uLong) stream.avail_in != sourceLen) {
		return Z_BUF_ERROR;
	}
	stream.next_out = dest;
	stream.avail_out = (uInt) *destLen;
	if ((uLong) stream.avail_out != *destLen) {
		return Z_BUF_ERROR;
	}
	stream.zalloc = (alloc_func) 0;
	stream.zfree = (free_func) 0;

	err = inflateInit(&stream);
	if (err != Z_OK) {
		return err;
	}
	err = inflate(&stream, Z_FINISH);
	if (err != Z_STREAM_END) {
		inflateEnd(&stream);
		return err == Z_OK ? Z_BUF_ERROR : err;
	}
	*destLen = stream.total_out;

	err = inflateEnd(&stream);
	return err;
}
