// FUNCTION: GOLD 0x00461fc0
// FUNCTION: GOLDTL 0x45e180

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

void __cdecl fcn_0045e180(deflate_state* s)
{
	s->window_size = (ulg) 2L * s->w_size;

	s->head[s->hash_size - 1] = 0;
	zmemzero((Bytef*) s->head, (unsigned) (s->hash_size - 1) * sizeof(*s->head));

	s->max_lazy_match = g_663310[s->level].max_lazy;
	s->good_match = g_663310[s->level].good_length;
	s->nice_match = g_663310[s->level].nice_length;
	s->max_chain_length = g_663310[s->level].max_chain;

	s->strstart = 0;
	s->block_start = 0L;
	s->lookahead = 0;
	s->match_length = s->prev_length = MIN_MATCH - 1;
	s->match_available = 0;
	s->ins_h = 0;
}
