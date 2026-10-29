extern unsigned char* lpGebaeudePROT;

/* ADDRESS: GOLDTL 0x00504ef0 */
int __cdecl fcn_00504ef0(int type, int* out)
{
	int n;
	int i;

	n = 0;
	for (i = 0; i < 0x58; i++) {
		if (lpGebaeudePROT[i * 0x24d] == type) {
			out[n] = i;
			n++;
		}
	}
	return n;
}
