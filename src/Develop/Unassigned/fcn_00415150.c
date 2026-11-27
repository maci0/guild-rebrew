void __cdecl d3_GetAnimFrameOffset(char* a1, char* a2, int idx, int a4, float* out);

/* ADDRESS: GOLDTL 0x00415150 */
int __cdecl fcn_00415150(char *this_, char *firstOut, char *secondOut)
{
	char *p;

	p = *(char **)(this_ + 0x1EC);
	if (p != 0 && *(int *)(p + 0x484) != 0) {
		p += 0x41C;
		d3_GetAnimFrameOffset(this_, p, *(int *)p, firstOut, secondOut);
		return 1;
	}
	*(int *)firstOut = *(int *)(this_ + 0x4C);
	*(int *)(firstOut + 4) = *(int *)(this_ + 0x50);
	*(int *)(firstOut + 8) = *(int *)(this_ + 0x54);
	*(int *)secondOut = *(int *)(this_ + 0x84);
	*(int *)(secondOut + 4) = *(int *)(this_ + 0x88);
	*(int *)(secondOut + 8) = *(int *)(this_ + 0x8C);
	return 1;
}
