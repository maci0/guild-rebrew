#include "deflate.h"

int __cdecl fcn_0045df20(z_streamp strm);
int __cdecl fcn_0045da70(z_streamp strm);

// FUNCTION: GOLDTL 0x45d770
// SIZE: 505
int __cdecl fcn_0045d770(z_streamp strm, int level, int method, int windowBits, int memLevel, int strategy, const char* version, int stream_size)
{
	deflate_state* s;
	int noheader = 0;
	static const char* my_version = ZLIB_VERSION;

	ushf* overlay;

	if (version == Z_NULL || version[0] != my_version[0] || stream_size != sizeof(z_stream)) {
		return Z_VERSION_ERROR;
	}
	if (strm == Z_NULL) {
		return Z_STREAM_ERROR;
	}

	strm->msg = Z_NULL;
	if (strm->zalloc == Z_NULL) {
		strm->zalloc = zcalloc;
		strm->opaque = (voidpf) 0;
	}
	if (strm->zfree == Z_NULL) {
		strm->zfree = zcfree;
	}

	if (level == Z_DEFAULT_COMPRESSION) {
		level = 6;
	}

	if (windowBits < 0) {
		noheader = 1;
		windowBits = -windowBits;
	}
	if (memLevel < 1 || memLevel > MAX_MEM_LEVEL || method != Z_DEFLATED || windowBits < 8 || windowBits > 15 || level < 0 || level > 9 || strategy < 0 || strategy > Z_HUFFMAN_ONLY) {
		return Z_STREAM_ERROR;
	}
	s = (deflate_state*) ZALLOC(strm, 1, sizeof(deflate_state));
	if (s == Z_NULL) {
		return Z_MEM_ERROR;
	}
	strm->state = (struct internal_state FAR*) s;
	s->strm = strm;

	s->noheader = noheader;
	s->w_bits = windowBits;
	s->w_size = 1 << s->w_bits;
	s->w_mask = s->w_size - 1;

	s->hash_bits = memLevel + 7;
	s->hash_size = 1 << s->hash_bits;
	s->hash_mask = s->hash_size - 1;
	s->hash_shift = ((s->hash_bits + MIN_MATCH - 1) / MIN_MATCH);

	s->window = (Bytef*) ZALLOC(strm, s->w_size, 2 * sizeof(Byte));
	s->prev = (Posf*) ZALLOC(strm, s->w_size, sizeof(Pos));
	s->head = (Posf*) ZALLOC(strm, s->hash_size, sizeof(Pos));

	s->lit_bufsize = 1 << (memLevel + 6);

	overlay = (ushf*) ZALLOC(strm, s->lit_bufsize, sizeof(ush) + 2);
	s->pending_buf = (uchf*) overlay;
	s->pending_buf_size = (ulg) s->lit_bufsize * (sizeof(ush) + 2L);

	if (s->window == Z_NULL || s->prev == Z_NULL || s->head == Z_NULL || s->pending_buf == Z_NULL) {
		strm->msg = (char*) ERR_MSG(Z_MEM_ERROR);
		fcn_0045df20(strm);
		return Z_MEM_ERROR;
	}
	s->d_buf = overlay + s->lit_bufsize / sizeof(ush);
	s->l_buf = s->pending_buf + (1 + sizeof(ush)) * s->lit_bufsize;

	s->level = level;
	s->strategy = strategy;
	s->method = (Byte) method;

	return fcn_0045da70(strm);
}
