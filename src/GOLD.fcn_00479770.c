typedef struct {
	int f0;
	char pad4[0x18];
	int f1c;
	int f20;
	char pad24[0x1c];
} req40;

typedef struct {
	char pad0[4];
	int f4;
	int f8;
} res_small;

res_small *__cdecl fcn_00478cb0(req40 *, int);
void __cdecl fcn_00476620(int, int, int, int, req40 *, int, int, res_small *);

/* ADDRESS: GOLD 0x00479770 */
res_small *__cdecl fcn_00479770(req40 *req)
{
	req40 copy;
	res_small *r;

	copy = *req;
	copy.f20 = 0;
	copy.f1c = 0;
	r = fcn_00478cb0(&copy, req->f0);
	fcn_00476620(0, 0, r->f4, r->f8, req, 0, 0, r);
	return r;
}
