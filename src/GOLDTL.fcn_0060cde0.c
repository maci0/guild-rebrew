/* ADDRESS: GOLDTL 0x0060cde0 */
/* Native ABI is __thiscall (self in ecx, three stack arguments, ret 0xc).
 * MSVC 6 C rejects __thiscall (C4234), so __fastcall carries self in ecx;
 * its unused edx slot is the dummy parameter. */
int __fastcall fcn_0060cde0(void* self, int d1, char* base, int index,
	unsigned short slot)
{
	int* tab120;
	int* tab118;
	int stride;
	int idx;

	tab120 = *(int**) ((char*) self + 0x120);
	tab118 = *(int**) ((char*) self + 0x118);
	stride = *(int*) ((char*) self + 0xc);
	idx = tab120[slot];
	tab118[idx] = index;
	memcpy(*(char**) ((char*) self + 0x114) + stride * idx,
		base + stride * index, stride);
	tab120[slot]--;
	return 0;
}
