typedef struct
{
	char pad00[0x24];
	int n;
	int f28;
	int f2c;
	int f30;
} F4dStream;

int __cdecl fcn_004011f0(void* stream, void* dst);
int __cdecl fcn_0041db70(int flags, const char* name);

/* ADDRESS: GOLDTL 0x0044df60 */
void __cdecl fcn_0044df60(void* stream, F4dStream* r)
{
	fcn_004011f0(stream, &r->n);
	if (r->n <= 0)
		return;
	if (r->f30 != 0)
		return;
	r->f28 = 0;
	r->f2c = 0;
	r->f30 = fcn_0041db70(0x60000, "d3_io_b:BGIPointBuffer");
}
