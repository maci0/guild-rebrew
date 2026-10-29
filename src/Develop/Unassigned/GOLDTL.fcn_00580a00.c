int __cdecl fcn_00580a30();

/* ADDRESS: GOLDTL 0x00580a00 */
int __cdecl fcn_00580a00(int a1, int a2)
{
	if (a1 != 5) {
		return -2;
	}
	*(int*) 0x6a81dc = *(int*) a2;
	*(char*) 0x6a81e0 = *(char*) (a2 + 4);
	return fcn_00580a30();
}
