/* ADDRESS: GOLD 0x0041d1c0 */
int __stdcall fcn_0041d1c0(int obj, int key)
{
	if ((*(unsigned char *)(obj + 0x4c) & 0x40) != 0) {
		if (*(int *)(obj + 0x54) == key) {
			if (*(int *)(obj + 0xc) == 0x320 && *(int *)(obj + 8) == 0x258)
				*(unsigned char *)0x631225 = 1;
			if (*(int *)(obj + 0xc) == 0x400 && *(int *)(obj + 8) == 0x300)
				*(unsigned char *)0x631226 = 1;
			if (*(int *)(obj + 0xc) == 0x480 && *(int *)(obj + 8) == 0x360)
				*(unsigned char *)0x631227 = 1;
		}
	}
	return 1;
}
