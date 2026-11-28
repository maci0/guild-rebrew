


// fcn_00512500 — fcn_00501190(1,5,0xb); if non-null fcn_00511e90(r).

int __cdecl fcn_00501190(int, int, int);
int __cdecl init_AllocateGebaeudeSceneSlot(int);

/* ADDRESS: GOLDDE 0x005006b0 */
void __cdecl init_AllocateKind0bSceneSlot(void)
{
	int r;
	r = fcn_00501190(1, 5, 0xb);
	if (r != 0) {
		init_AllocateGebaeudeSceneSlot(r);
	}
}

