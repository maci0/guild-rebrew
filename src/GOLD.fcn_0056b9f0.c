// FUNCTION: GOLD 0x0056b9f0
// fcn_0056b9f0 — a[i]=b; i++; return i<0x40.

int __cdecl fcn_0056b9f0(int b, char* a)
{
	int i;
	i = *(int*) (a + 0x104);
	*(int*) (a + i * 4 + 4) = b;
	i++;
	*(int*) (a + 0x104) = i;
	return i < 0x40;
}
