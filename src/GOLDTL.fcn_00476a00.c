typedef struct {
	int f0;
	char pad4[0x18];
	int f1c;
	int f20;
	char pad24[0x38];
} fcn_00476a00_req;
// SIZE 0x5c

typedef struct {
	char pad0[0x4];
	int f4;
	int f8;
} fcn_00476a00_res;

fcn_00476a00_res* __cdecl fcn_004770a0(fcn_00476a00_req*, int);
void __cdecl fcn_00476620(int, int, int, int, fcn_00476a00_req*, int, int, fcn_00476a00_res*);

// FUNCTION: GOLDTL 0x476a00
// SIZE: 79

fcn_00476a00_res* __cdecl fcn_00476a00(fcn_00476a00_req* req)
{
	fcn_00476a00_req copy;
	fcn_00476a00_res* r;

	copy = *req;
	copy.f20 = 0;
	copy.f1c = 0;
	r = fcn_004770a0(&copy, req->f0);
	fcn_00476620(0, 0, r->f4, r->f8, req, 0, 0, r);
	return r;
}
