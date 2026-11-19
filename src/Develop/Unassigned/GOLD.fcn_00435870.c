extern volatile int g_6b7fac;

/* ADDRESS: GOLD 0x00435870 */
void __cdecl fcn_00435870(char* obj, char* name, unsigned char bit)
{
	char* rec;
	int n;

	if (obj == 0) {
		return;
	}
	*(int*) (*(int*) (obj + 0x18) + 0x40) = g_6b7fac;
	rec = obj + 0x90;
	n = 3;
	do {
		if (*(char**) (rec - 0xc) != 0 && strcmp(name, *(char**) (rec - 0xc)) == 0) {
			*rec = (char) ((*rec & ~2) | ((bit & 1) << 1));
		}
		rec += 0x7c;
		n--;
	} while (n != 0);
}
