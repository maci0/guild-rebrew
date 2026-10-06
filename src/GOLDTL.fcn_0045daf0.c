// FUNCTION: GOLDTL 0x45daf0

#include "deflate.h"

typedef enum { need_more, block_done, finish_started, finish_done } block_state;

typedef block_state (*compress_func)(deflate_state* s, int flush);

// SIZE 0xc
typedef struct config_s {
	ush good_length;
	ush max_lazy;
	ush nice_length;
	ush max_chain;
	compress_func func;
} config;

extern config g_663310[10];

int __cdecl fcn_0045daf0(z_streamp strm, int level, int strategy)
{
	deflate_state* s;
	compress_func func;
	int err = Z_OK;

	if (strm == Z_NULL || strm->state == Z_NULL) {
		return Z_STREAM_ERROR;
	}
	s = strm->state;

	if (level == Z_DEFAULT_COMPRESSION) {
		level = 6;
	}
	if (level < 0 || level > 9 || strategy < 0 || strategy > Z_HUFFMAN_ONLY) {
		return Z_STREAM_ERROR;
	}
	func = g_663310[s->level].func;

	if (func != g_663310[level].func && strm->total_in != 0) {
		err = deflate(strm, Z_PARTIAL_FLUSH);
	}
	if (s->level != level) {
		s->level = level;
		s->max_lazy_match = g_663310[level].max_lazy;
		s->good_match = g_663310[level].good_length;
		s->nice_match = g_663310[level].nice_length;
		s->max_chain_length = g_663310[level].max_chain;
	}
	s->strategy = strategy;
	return err;
}
