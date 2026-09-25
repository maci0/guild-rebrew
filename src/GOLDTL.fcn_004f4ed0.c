// FUNCTION: GOLDTL 0x004f4ed0
// SIZE: 144

extern unsigned char* g_90e094;
extern unsigned char* g_868050;
extern float g_662910;
extern float g_662a6c;

int __cdecl fcn_0050c710(unsigned char* rec, int a, int b);

float __cdecl fcn_004f4ed0(unsigned short* key)
{
	unsigned char* rec;
	int best;
	int v;
	int i;

	best = 0;
	rec = g_90e094;
	for (i = 0; i < 256; i++, rec += 0xa9) {
		if (rec[0] != 0 && *(unsigned short*) (rec + 0x27) == *key && g_868050[rec[0] * 0x24d] == 7) {
			v = fcn_0050c710(rec, 10, 1);
			if (v == 0x4b) {
				return g_662a6c;
			}
			if (v > best) {
				best = v;
			}
		}
	}
	return best * g_662910;
}
