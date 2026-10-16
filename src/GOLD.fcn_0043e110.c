void __cdecl fcn_0043b6b0(int, int);
void __cdecl fcn_00452e30(int, int);

/* ADDRESS: GOLD 0x0043e110 */
unsigned char __cdecl fcn_0043e110(int obj, unsigned char flag)
{
	if (flag != 0) {
		if (*(int *)(obj + 0x218) == 5 && *(unsigned char *)obj == 0x72) {
			*(int *)(obj + 0x218) = 6;
			*(int *)(obj + 0x40) = *(int *)0x6333cc;
			fcn_0043b6b0(obj, 0);
			return 1;
		}
	} else if (*(int *)(obj + 0x218) == 6) {
		*(int *)(obj + 0x218) = 5;
		fcn_00452e30(obj, 0);
		fcn_0043b6b0(obj, 0);
	}
	return 1;
}
