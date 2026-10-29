extern char g_149d120[][0x74];

int __cdecl fcn_0065f220(const char* a, const char* b);

/* ADDRESS: GOLDTL 0x0042d630 */
int __cdecl fcn_0042d630(const char* name)
{
	int i;

	for (i = 0; i < 128; i++) {
		if (fcn_0065f220(g_149d120[i], name) == 0 && g_149d120[i][0] != 0) {
			return i;
		}
	}
	return -1;
}
