void __cdecl fcn_00431d70(char* a1, char* a2, int idx, int a4, float* out);

/* ADDRESS: GOLDTL 0x00415150 */
int __cdecl fcn_00415150(char *this_, char *a2, char *a3)
{
	char *p;

	p = *(char **)(this_ + 0x1EC);
	if (p != 0 && *(int *)(p + 0x484) != 0) {
		p += 0x41C;
		fcn_00431d70(this_, p, *(int *)p, a2, a3);
		return 1;
	}
	*(int *)a2 = *(int *)(this_ + 0x4C);
	*(int *)(a2 + 4) = *(int *)(this_ + 0x50);
	*(int *)(a2 + 8) = *(int *)(this_ + 0x54);
	*(int *)a3 = *(int *)(this_ + 0x84);
	*(int *)(a3 + 4) = *(int *)(this_ + 0x88);
	*(int *)(a3 + 8) = *(int *)(this_ + 0x8C);
	return 1;
}
