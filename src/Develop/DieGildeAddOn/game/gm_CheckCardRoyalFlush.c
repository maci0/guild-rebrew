int __cdecl gm_CheckCardFlush(int* h, int* out, int a3);
int __cdecl gm_FindCardHighStraight(int* h, int* out, int a3);

/* ADDRESS: GOLDTL 0x004a76d0 */
int __cdecl gm_CheckCardRoyalFlush(int* h, int* out, int a3)
{
	if (!a3 && gm_CheckCardFlush(h, out, 0) && gm_FindCardHighStraight(h, out, 0)) {
		return 1;
	}
	return 0;
}
