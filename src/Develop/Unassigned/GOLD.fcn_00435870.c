extern int SonnenstrahlenStartZeit;

/* ADDRESS: GOLD 0x00435870 */
void __cdecl fcn_00435870(char* a0, char* name, unsigned char bit)
{
	char* rec;
	int n;

	if (a0 == 0) {
		return;
	}
	*(int*) (*(int*) (a0 + 0x18) + 0x40) = SonnenstrahlenStartZeit;
	rec = a0 + 0x90;
	n = 3;
	do {
		if (*(char**) (rec - 0xc) != 0 && strcmp(name, *(char**) (rec - 0xc)) == 0) {
			*rec = (char) ((*rec & ~2) | ((bit & 1) << 1));
		}
		rec += 0x7c;
		n--;
	} while (n != 0);
}
