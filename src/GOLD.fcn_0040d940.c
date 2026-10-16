void __cdecl fcn_00458a10(int obj, int field, int *out);
int __cdecl fcn_00446e10(int zero, int *local, int field, int value);
void __cdecl fcn_00453270(int value);

/* ADDRESS: GOLD 0x0040d940 */
int __cdecl fcn_0040d940(int *a, int *slot)
{
	int local[4];
	int obj;
	int r;

	obj = *slot;
	if (obj == 0)
		return 0;
	fcn_00458a10(obj, obj + 0x4c, local);
	r = fcn_00446e10(0, local, *slot + 0x84, *a);
	if (r != 0)
		fcn_00453270(r);
	return r;
}
