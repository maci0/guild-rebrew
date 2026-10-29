/* The inventory start at 0x49d059 is the branch target of the je at
   0x49d03b, not an independent function. The real function entry is
   0x49d030 and its extent runs to the ret at 0x49d0c8 (152 bytes). */
extern int fcn_004f4830(int idx, void* out);
extern int fcn_004a4680(int* a1, int* a2, int a3, int a4, void* s);
extern int fcn_004a4410(int* a1, int* a2, int a3, int a4, int z, int a6, int a7);

/* ADDRESS: GOLDTL 0x0049d030 */
int __cdecl fcn_0049d030(int* a1, int* a2, int a3, int a4, int a5, int a6, int a7)
{
	char s[0x24];
	int* p1;
	int* p2;

	p1 = a1;
	p2 = a2;
	if (a5 != 0) {
		*p1 = (int) 0xf149f2ca;
		*p2 = (int) 0xf149f2ca;
		return 0;
	}
	*p1 = 0;
	*p2 = 0;
	fcn_004f4830(0x16, s);
	if (*(int*) (s + 0x18) != 0) {
		return fcn_004a4680(p1, p2, a3, a4, s);
	}
	return fcn_004a4410(p1, p2, a3, a4, 0, a6, a7);
}
