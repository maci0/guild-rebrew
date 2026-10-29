

#include "zutil.h"
#include "infblock.h"

typedef enum {
	METHOD,
	FLAG,
	DICT4,
	DICT3,
	DICT2,
	DICT1,
	DICT0,
	BLOCKS,
	CHECK4,
	CHECK3,
	CHECK2,
	CHECK1,
	DONE,
	BAD
} inflate_mode;

// SIZE 0x18
struct internal_state {
	inflate_mode mode;
	union {
		uInt method;
		struct {
			uLong was;
			uLong need;
		} check;
		uInt marker;
	} sub;
	int nowrap;
	uInt wbits;
	inflate_blocks_statef* blocks;
};

extern const Byte g_6633d4[4];

int __cdecl fcn_00461ba0(z_streamp z)
{
	uInt n;
	Bytef* p;
	uInt m;
	uLong r;
	uLong w;

	if (z == Z_NULL || z->state == Z_NULL) {
		return Z_STREAM_ERROR;
	}
	if (z->state->mode != BAD) {
		z->state->mode = BAD;
		z->state->sub.marker = 0;
	}
	if ((n = z->avail_in) == 0) {
		return Z_BUF_ERROR;
	}
	p = z->next_in;
	m = z->state->sub.marker;

	while (n && m < 4) {
		if (*p == g_6633d4[m]) {
			m++;
		} else if (*p) {
			m = 0;
		} else {
			m = 4 - m;
		}
		p++, n--;
	}

	z->total_in += p - z->next_in;
	z->next_in = p;
	z->avail_in = n;
	z->state->sub.marker = m;

	if (m != 4) {
		return Z_DATA_ERROR;
	}
	r = z->total_in;
	w = z->total_out;
	inflateReset(z);
	z->total_in = r;
	z->total_out = w;
	z->state->mode = BLOCKS;
	return Z_OK;
}
