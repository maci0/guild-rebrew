


/* fcn_004ac150: repeat gm_RandomMod(0x33) until its low 16 bits differ from si. */

int __cdecl gm_RandomMod(int);

void __cdecl fcn_004ac150(unsigned short si)
{
	int r;
	do {
		r = gm_RandomMod(0x33) & 0xffff;
	} while ((unsigned short) r == si);
}

