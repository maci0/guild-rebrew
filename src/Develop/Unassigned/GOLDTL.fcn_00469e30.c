extern void* g_7725a8;
extern int g_67d3cc;

void __cdecl fcn_00469e70(void);
int __cdecl fcn_00466260(int idx, void** out, int* out_idx);
void __cdecl d2_AddRefcount(int idx);

/* ADDRESS: GOLDTL 0x00469e30 */
void __cdecl fcn_00469e30(int idx)
{
	if (g_7725a8) {
		fcn_00469e70();
	}
	fcn_00466260(idx, &g_7725a8, &g_67d3cc);
	d2_AddRefcount(g_67d3cc);
}
