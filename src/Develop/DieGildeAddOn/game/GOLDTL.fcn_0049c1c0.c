extern unsigned char g_773d75;

char* __cdecl fcn_00503d10(int id);
char* __cdecl fcn_00502cd0(int a, int b, int c, int d);
int __cdecl gm_GetMsgField(char* g, char* s);
int __cdecl fcn_0050d320(int a, unsigned char k);
float __cdecl fcn_0050bb50(int id, unsigned char k);

/* ADDRESS: GOLDTL 0x0049c1c0 */
int __cdecl fcn_0049c1c0(int a1, int a2, int k, char* it, char* out)
{
	char* g;
	char* s;
	int n;

	if (k == 2 && it[0] == 2) {
		g = fcn_00503d10(*(int*) (it + 4));
		if (g) {
			s = fcn_00502cd0(*(int*) (g + 0x14), 1, 0, *(int*) (it + 4));
			if (s && gm_GetMsgField(g, s) >= 1) {
				n = fcn_0050d320(a2, g_773d75);
				if (*(float*) (it + 0x14) > 0.0f && *(float*) (it + 0x14) < 1.0f) {
					n = (int) (n * *(float*) (it + 0x14));
				}
				if (n >= (int) fcn_0050bb50(*(int*) (it + 4), g_773d75)) {
					out[0] = 1;
					*(int*) (out + 4) = *(int*) (g + 2);
					*(int*) (out + 8) = 1;
					return 0xc;
				}
			}
		}
	}
	return 0;
}
