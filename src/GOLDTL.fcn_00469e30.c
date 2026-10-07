extern void* g_7725a8;
extern int g_67d3cc;

void __cdecl fcn_00469e70(void);
int __cdecl fcn_00466260(int idx, void** out, int* out_idx);
void __cdecl fcn_00469900(int idx);

// FUNCTION: GOLDTL 0x469e30
void __cdecl fcn_00469e30(int idx)
{
	if (g_7725a8) {
		fcn_00469e70();
	}
	fcn_00466260(idx, &g_7725a8, &g_67d3cc);
	fcn_00469900(g_67d3cc);
}
