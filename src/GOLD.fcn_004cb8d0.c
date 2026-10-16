int __cdecl fcn_004e67a0(int);

/* ADDRESS: GOLD 0x004cb8d0 */
int __cdecl fcn_004cb8d0(int a, char *b)
{
	int r;
	int z;
	unsigned char flag;

	r = fcn_004e67a0(a + 0x10);
	z = 0;
	if (b != 0) {
		flag = (unsigned char)((r == z) + 1);
		*(unsigned char *)(b + 1) = (unsigned char)z;
		*(unsigned char *)b = flag;
		*(int *)(b + 6) = z;
	}
	return r == z;
}
