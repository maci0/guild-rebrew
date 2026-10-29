int __cdecl fcn_004f4830(int, void*);
int __cdecl fcn_004a4680(void*, void*, int, int, void*);
int __cdecl fcn_004a4410(void*, void*, int, int, int, int, int);

/* ADDRESS: GOLDTL 0x0049ca80 */
int __cdecl fcn_0049ca80(int* p1, int* p2, int a3, int a4, int a5, int a6, int a7)
{
	char local[0x24];

	if (a5 != 0) {
		*p1 = (int) 0xf149f2ca;
		*p2 = (int) 0xf149f2ca;
		return 0;
	}
	*p1 = 0;
	*p2 = 0;
	fcn_004f4830(3, local);
	if (*(int*) (local + 0x18) != 0) {
		return fcn_004a4680(p1, p2, a3, a4, local);
	}
	return fcn_004a4410(p1, p2, a3, a4, 0, a6, a7);
}
