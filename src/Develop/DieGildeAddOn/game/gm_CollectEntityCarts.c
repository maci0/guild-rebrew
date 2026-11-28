


void* __cdecl gm_QueryEntities(int, int, int, ...);
void* __cdecl gm_NextEntityQueryMatch(void);

int __cdecl gm_CollectEntityCarts(char* a, void** out)
{
	int n;
	char* r;

	n = 0;
	r = gm_QueryEntities(n, 2, 7, 4, 0x1d);
	while (r != 0 && n < 3) {
		if (*(int*) (r + 0x1c) == *(int*) (a + 1)) {
			if (out != 0) {
				out[n] = r;
			}
			n++;
		}
		r = gm_NextEntityQueryMatch();
	}
	return n;
}
