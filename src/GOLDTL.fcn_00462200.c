#include "zutil.h"
#include "inftrees.h"

// SIZE 0x4
struct internal_state {
	int dummy;
};

extern const uInt g_663408[31];
extern const uInt g_663488[31];
extern const uInt g_663508[30];
extern const uInt g_663580[30];

int __cdecl fcn_00461d50(uIntf* b, uInt n, uInt s, const uIntf* d, const uIntf* e, inflate_huft* FAR* t, uIntf* m, inflate_huft* hp, uInt* hn, uIntf* v);

// FUNCTION: GOLDTL 0x462200
// SIZE: 393
int __cdecl fcn_00462200(uInt nl, uInt nd, uIntf* c, uIntf* bl, uIntf* bd, inflate_huft* FAR* tl, inflate_huft* FAR* td, inflate_huft* hp, z_streamp z)
{
	int r;
	uInt hn = 0;
	uIntf* v;

	if ((v = (uIntf*) ZALLOC(z, 288, sizeof(uInt))) == Z_NULL) {
		return Z_MEM_ERROR;
	}

	r = fcn_00461d50(c, nl, 257, g_663408, g_663488, tl, bl, hp, &hn, v);
	if (r != Z_OK || *bl == 0) {
		if (r == Z_DATA_ERROR) {
			z->msg = (char*) "oversubscribed literal/length tree";
		} else if (r != Z_MEM_ERROR) {
			z->msg = (char*) "incomplete literal/length tree";
			r = Z_DATA_ERROR;
		}
		ZFREE(z, v);
		return r;
	}

	r = fcn_00461d50(c + nl, nd, 0, g_663508, g_663580, td, bd, hp, &hn, v);
	if (r != Z_OK || (*bd == 0 && nl > 257)) {
		if (r == Z_DATA_ERROR) {
			z->msg = (char*) "oversubscribed distance tree";
		} else if (r == Z_BUF_ERROR) {
			z->msg = (char*) "incomplete distance tree";
			r = Z_DATA_ERROR;
		} else if (r != Z_MEM_ERROR) {
			z->msg = (char*) "empty distance tree with lengths";
			r = Z_DATA_ERROR;
		}
		ZFREE(z, v);
		return r;
	}

	ZFREE(z, v);
	return Z_OK;
}
