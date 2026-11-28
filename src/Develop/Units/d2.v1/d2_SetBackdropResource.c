extern void* g_7725a8;
extern int g_67d3cc;

void __cdecl d2_ClearBackdropResource(void);
int __cdecl d2_ResolveResourceEntry(int idx, void** out, int* out_idx);
void __cdecl d2_AddRefcount(int idx);

/* ADDRESS: GOLDTL 0x00469e30 */
/* ADDRESS: GOLDDE 0x0045d750 */
void __cdecl d2_SetBackdropResource(int idx)
{
	if (g_7725a8) {
		d2_ClearBackdropResource();
	}
	d2_ResolveResourceEntry(idx, &g_7725a8, &g_67d3cc);
	d2_AddRefcount(g_67d3cc);
}
