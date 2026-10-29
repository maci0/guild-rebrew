/* Native ABI is __thiscall with one stack argument (ret 4).  MSVC 6 C
 * rejects __thiscall (C4234), so __fastcall carries self in ecx and its
 * unused edx slot is the dummy parameter.  The stored 10-byte extent was
 * clamped mid-instruction; the function runs to ret 4 at 0x006052f9. */
/* ADDRESS: GOLDTL 0x006052b9 */
int __fastcall fcn_006052b9(void *self, int d1, void *a1)
{
	unsigned i;
	int *p;

	i = *(unsigned *)((char *)self + 0x108) + 1;
	if (i >= *(unsigned *)((char *)self + 0x104))
		return 0;
	do {
		p = (int *)(*(char **)((char *)self + 0xfc) + i * 8);
		if (*(char *)(*(char **)((char *)self + 0x100) + i) == 0)
			*p = ((int *)a1)[*p];
		i++;
	} while (i < *(unsigned *)((char *)self + 0x104));
	return 0;
}
