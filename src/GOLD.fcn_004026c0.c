/* ADDRESS: GOLD 0x004026c0 */
int __cdecl fcn_004026c0(int id, int flag)
{
	int n;
	int p;
	int e;

	n = 0;
	for (p = 0x1468ae0; p < 0x14696e0; p += 4) {
		e = *(int *)p;
		if (e == 0)
			continue;
		if (id != -1 && *(int *)(e + 0x88) != id * 992 + 0xfd7ba0)
			continue;
		if (flag == 0 && *(int *)(*(int *)(e + 0x34) + 0x218) == 1)
			continue;
		n++;
	}
	return n;
}
