extern char d2_ActiveRouteListHead[];
extern char d2_Controls[];
typedef struct
{
	int f0;
	int f4;
} F4bRec;

int __cdecl d2_FindLinkedRecordIndex(void* a, int b);
void __cdecl fcn_00466330(int idx, int v);

/* ADDRESS: GOLDTL 0x004bfbc0 */
/* ADDRESS: GOLDDE 0x004ad740 */
void __cdecl d2_UpdateRoutePointImage(F4bRec* r)
{
	int* tbl;
	int v;
	int v0;
	int idx;

	v0 = d2_FindLinkedRecordIndex((void*) *(int*) &d2_ActiveRouteListHead, r->f4);
	idx = r->f0;
	v = v0 + 0x7bb;
	tbl = (int*) *(int*) &d2_Controls;
	if (tbl[idx * 189 + 2] != v)
		fcn_00466330(idx, v);
}
