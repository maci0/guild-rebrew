int __cdecl fcn_004287b0(int);
void __cdecl fcn_00429ab0(int, int, int);

/* ADDRESS: GOLD 0x0040b680 */
int __cdecl fcn_0040b680(int slot, int arg)
{
	int obj;

	obj = fcn_004287b0(*(int *)slot);
	if (obj == 0)
		return 0;
	*(int *)(obj + 0x104) = *(int *)(*(int *)0x6332b8 + 0x104);
	*(int *)(obj + 0xc8c) = *(int *)(*(int *)0x6332b8 + 0xc8c);
	*(int *)(obj + 0xc90) = *(int *)(*(int *)0x6332b8 + 0xc90);
	fcn_00429ab0(obj, 1, *(int *)arg);
	return obj;
}
