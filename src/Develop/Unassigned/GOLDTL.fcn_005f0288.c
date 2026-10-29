/* Native ABI is __thiscall (self in ecx, two stack arguments, ret 8).
 * MSVC 6 C rejects __thiscall (C4234), so __fastcall carries self in ecx;
 * its unused edx slot is the dummy parameter. */
/* ADDRESS: GOLDTL 0x005f0288 */
void __fastcall fcn_005f0288(void* self, int dummy, char* a1, int a2)
{
	int idx;

	if ((*((unsigned char*) self + 1) & 0x10) != 0) {
		idx = *(int*) ((char*) self + 0x38);
		if (idx != 0) {
			*(int*) (a1 + idx * 4 + 8) = a2;
		}
	}
}
