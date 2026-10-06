// FUNCTION: GOLD 0x004243d0
// fcn_004243d0 — copy string into fixed buffer 0x14611a0.

void __cdecl fcn_004243d0(char* a)
{
	char* d;
	char c;
	d = (char*) 0x14611a0;
	do {
		c = *a;
		*d = c;
		a++;
		d++;
	} while (c != 0);
}
