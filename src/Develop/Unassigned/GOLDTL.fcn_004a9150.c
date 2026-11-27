int __cdecl gm_CountStraftatenForEntity(int);


/* ADDRESS: GOLDTL 0x004a9150 */
int __cdecl ai_CheckAction02bPredicate(int a, char* e, int b, char* out)
{
	int n;
	int h;

	if (*(int*) (e + 0x194) < 2)
		return 0;
	n = gm_CountStraftatenForEntity(*(int*) (e + 4));
	if (n <= 0)
		return 0;
	h = *(int*) (e + 0x194) / 2;
	if (h >= n)
		h = n;
	*(int*) (out + 0x10) = h;
	return 1;
}
