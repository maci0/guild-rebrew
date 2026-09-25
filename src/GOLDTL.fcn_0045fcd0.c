// FUNCTION: GOLDTL 0x45fcd0
// SIZE: 160

#include "zutil.h"
#include "infblock.h"
#include "inftrees.h"
#include "infcodes.h"
#include "infutil.h"

void __cdecl fcn_0045fc50(inflate_blocks_statef*, z_streamp, uLongf*);

inflate_blocks_statef* __cdecl fcn_0045fcd0(z_streamp z, check_func c, uInt w)
{
	inflate_blocks_statef* s;

	if ((s = (inflate_blocks_statef*) ZALLOC(z, 1, sizeof(struct inflate_blocks_state))) == Z_NULL) {
		return s;
	}
	if ((s->hufts = (inflate_huft*) ZALLOC(z, sizeof(inflate_huft), MANY)) == Z_NULL) {
		ZFREE(z, s);
		return Z_NULL;
	}
	if ((s->window = (Bytef*) ZALLOC(z, 1, w)) == Z_NULL) {
		ZFREE(z, s->hufts);
		ZFREE(z, s);
		return Z_NULL;
	}
	s->end = s->window + w;
	s->checkfn = c;
	s->mode = TYPE;
	fcn_0045fc50(s, z, Z_NULL);
	return s;
}
