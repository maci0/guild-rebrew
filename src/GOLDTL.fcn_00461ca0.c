// FUNCTION: GOLDTL 0x461ca0
// SIZE: 163

#include "zutil.h"
#include "inftrees.h"


int __cdecl fcn_00461d50(uIntf*, uInt, uInt, const uIntf*, const uIntf*, inflate_huft* FAR*, uIntf*, inflate_huft*, uInt*, uIntf*);

int __cdecl fcn_00461ca0(uIntf* c, uIntf* bb, inflate_huft* FAR* tb, inflate_huft* hp, z_streamp z)
{
	int r;
	uInt hn = 0;
	uIntf* v;

	if ((v = (uIntf*) ZALLOC(z, 19, sizeof(uInt))) == Z_NULL) {
		return Z_MEM_ERROR;
	}
	r = fcn_00461d50(c, 19, 19, (uIntf*) Z_NULL, (uIntf*) Z_NULL, tb, bb, hp, &hn, v);
	if (r == Z_DATA_ERROR) {
		z->msg = (char*) "oversubscribed dynamic bit lengths tree";
	} else if (r == Z_BUF_ERROR || *bb == 0) {
		z->msg = (char*) "incomplete dynamic bit lengths tree";
		r = Z_DATA_ERROR;
	}
	ZFREE(z, v);
	return r;
}
