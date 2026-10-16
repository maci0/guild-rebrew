void __cdecl fcn_004bf360(int*);

/* ADDRESS: GOLD 0x004bf3b0 */
void __cdecl fcn_004bf3b0(void)
{
	int p;
	for (p = 0xf812a0; p < 0xf812e0; p += 8) {
		if (*(int*) p != -1)
			fcn_004bf360((int*) p);
	}
}
