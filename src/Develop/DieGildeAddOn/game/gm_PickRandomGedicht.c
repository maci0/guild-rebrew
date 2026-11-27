


/* gm_PickRandomGedicht: repeat gm_RandomMod(0x33) until its low 16 bits differ from prev_id. */

int __cdecl gm_RandomMod(int);

void __cdecl gm_PickRandomGedicht(unsigned short prev_id)
{
	int r;
	do {
		r = gm_RandomMod(0x33) & 0xffff;
	} while ((unsigned short) r == prev_id);
}

