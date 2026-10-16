int __cdecl fcn_00411be0(int);
void __cdecl fcn_004478e0(int, int);
void __cdecl d3_DestroyObject(int);

/* ADDRESS: GOLD 0x00417560 */
void __cdecl fcn_00417560(int obj)
{
	int id;
	int saved;
	int cur;

	id = -1;
	saved = *(int *)0x633444;
	cur = *(int *)(obj + 0x208);
	if (cur != *(int *)0x5fb5b0) {
		id = fcn_00411be0(cur);
		fcn_004478e0(id, 1);
	}
	d3_DestroyObject(obj);
	*(int *)0x631124 = 0;
	if (id != -1)
		fcn_004478e0(saved, 1);
}
