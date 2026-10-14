extern char g_6b89a4[];
extern char g_6b89a0[];

void __cdecl m_pool_free(int* pool, void* p);

/* ADDRESS: GOLD 0x00457c20 */
/* ADDRESS: GOLDTL 0x00454560 */
void __cdecl fcn_00454560(char** n)
{
	char* p;
	char* nx;
	unsigned int i;

	if (n != 0) {
		p = n[0xf];
		while (p != 0) {
			nx = *(char**) (p + 4);
			m_pool_free(&(*(int*)g_6b89a4), p);
			p = nx;
		}
		for (i = 0; i < 4; i++) {
			if (n[i] != 0) {
				fcn_00454560((char**) n[i]);
			}
		}
		m_pool_free(&(*(int*)g_6b89a0), n);
	}
}
