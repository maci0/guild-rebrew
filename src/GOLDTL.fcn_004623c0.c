#include "zutil.h"
#include "infblock.h"
#include "inftrees.h"
#include "infcodes.h"
#include "infutil.h"

// SIZE 0x4
struct inflate_codes_state {
	int dummy;
};

// FUNCTION: GOLDTL 0x4623c0
// SIZE: 306
int __cdecl fcn_004623c0(inflate_blocks_statef* s, z_streamp z, int r)
{
	uInt n;
	Bytef* p;
	Bytef* q;

	p = z->next_out;
	q = s->read;

	n = (uInt) ((q <= s->write ? s->write : s->end) - q);
	if (n > z->avail_out) {
		n = z->avail_out;
	}
	if (n && r == Z_BUF_ERROR) {
		r = Z_OK;
	}

	z->avail_out -= n;
	z->total_out += n;

	if (s->checkfn != Z_NULL) {
		z->adler = s->check = (*s->checkfn)(s->check, q, n);
	}

	zmemcpy(p, q, n);
	p += n;
	q += n;

	if (q == s->end) {
		q = s->window;
		if (s->write == s->end) {
			s->write = s->window;
		}

		n = (uInt) (s->write - q);
		if (n > z->avail_out) {
			n = z->avail_out;
		}
		if (n && r == Z_BUF_ERROR) {
			r = Z_OK;
		}

		z->avail_out -= n;
		z->total_out += n;

		if (s->checkfn != Z_NULL) {
			z->adler = s->check = (*s->checkfn)(s->check, q, n);
		}

		zmemcpy(p, q, n);
		p += n;
		q += n;
	}

	z->next_out = p;
	s->read = q;

	return r;
}
