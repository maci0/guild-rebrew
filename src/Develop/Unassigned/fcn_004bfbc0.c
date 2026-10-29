typedef struct
{
	int f0;
	int f4;
} F4bRec;

int __cdecl fcn_004be300(void* a, int b);
void __cdecl fcn_00466330(int idx, int v);

/* ADDRESS: GOLDTL 0x004bfbc0 */
void __cdecl fcn_004bfbc0(F4bRec* r)
{
	int* tbl;
	int v;
	int v0;
	int idx;

	v0 = fcn_004be300((void*) *(int*) 0x772908, r->f4);
	idx = r->f0;
	v = v0 + 0x7bb;
	tbl = (int*) *(int*) 0x1015ea0;
	if (tbl[idx * 189 + 2] != v)
		fcn_00466330(idx, v);
}
