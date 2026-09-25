#include "zutil.h"
#include "infblock.h"

// SIZE 0x4
struct inflate_blocks_state {
	int dummy;
};

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

uLong __cdecl fcn_0045d3f0(uLong adler, const Bytef* buf, uInt len);
inflate_blocks_statef* __cdecl fcn_0045fcd0(z_streamp z, check_func c, uInt w);
int __cdecl fcn_00461560(z_streamp z);
int __cdecl fcn_00461510(z_streamp z);

// FUNCTION: GOLDTL 0x4615b0
// SIZE: 270
int __cdecl fcn_004615b0(z_streamp z, int w, const char* version, int stream_size)
{
	if (version == Z_NULL || version[0] != ZLIB_VERSION[0] || stream_size != sizeof(z_stream)) {
		return Z_VERSION_ERROR;
	}

	if (z == Z_NULL) {
		return Z_STREAM_ERROR;
	}
	z->msg = Z_NULL;
	if (z->zalloc == Z_NULL) {
		z->zalloc = zcalloc;
		z->opaque = (voidpf) 0;
	}
	if (z->zfree == Z_NULL) {
		z->zfree = zcfree;
	}
	if ((z->state = (struct internal_state FAR*) ZALLOC(z, 1, sizeof(struct internal_state))) == Z_NULL) {
		return Z_MEM_ERROR;
	}
	z->state->blocks = Z_NULL;

	z->state->nowrap = 0;
	if (w < 0) {
		w = -w;
		z->state->nowrap = 1;
	}

	if (w < 8 || w > 15) {
		fcn_00461560(z);
		return Z_STREAM_ERROR;
	}
	z->state->wbits = (uInt) w;

	if ((z->state->blocks = fcn_0045fcd0(z, z->state->nowrap ? Z_NULL : fcn_0045d3f0, (uInt) 1 << w)) == Z_NULL) {
		fcn_00461560(z);
		return Z_MEM_ERROR;
	}

	fcn_00461510(z);
	return Z_OK;
}
