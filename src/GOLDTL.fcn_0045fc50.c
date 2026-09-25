// FUNCTION: GOLDTL 0x45fc50
// SIZE: 123

#include "zutil.h"
#include "infblock.h"
#include "inftrees.h"
#include "infcodes.h"
#include "infutil.h"

void __cdecl fcn_0045fc50(inflate_blocks_statef* s, z_streamp z, uLongf* c)
{
	if (c != Z_NULL) {
		*c = s->check;
	}
	if (s->mode == BTREE || s->mode == DTREE) {
		ZFREE(z, s->sub.trees.blens);
	}
	if (s->mode == CODES) {
		inflate_codes_free(s->sub.decode.codes, z);
	}
	s->mode = TYPE;
	s->bitk = 0;
	s->bitb = 0;
	s->read = s->write = s->window;
	if (s->checkfn != Z_NULL) {
		z->adler = s->check = (*s->checkfn)(0L, (const Bytef*) Z_NULL, 0);
	}
}
