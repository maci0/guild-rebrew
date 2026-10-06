// FUNCTION: GOLDTL 0x461b10

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

int __cdecl fcn_00461b10(z_streamp z, const Bytef* dictionary, uInt dictLength)
{
	uInt length = dictLength;

	if (z == Z_NULL || z->state == Z_NULL || z->state->mode != DICT0) {
		return Z_STREAM_ERROR;
	}
	if (adler32(1L, dictionary, dictLength) != z->adler) {
		return Z_DATA_ERROR;
	}
	z->adler = 1L;

	if (length >= ((uInt) 1 << z->state->wbits)) {
		length = (1 << z->state->wbits) - 1;
		dictionary += dictLength - length;
	}
	inflate_set_dictionary(z->state->blocks, dictionary, length);
	z->state->mode = BLOCKS;
	return Z_OK;
}
