typedef struct Req {
	unsigned short* s;
	int id;
	int arg;
	int dir;
	int pad;
} Req;
// SIZE 0x14

extern float g_1008574[];
extern float g_1009a64[8];

unsigned short* __cdecl gm_QueryEntities(int a, int b, int c, int d);
float* __cdecl gm_LookupSpecialObject(int id);
int __cdecl gm_UseSpecialObject(char* e, Req* r);

/* ADDRESS: GOLDTL 0x0049be10 */
/* ADDRESS: GOLDDE 0x0048a850 */
int __cdecl ai_RunUseTrank(char* entity, int* args, int* ctx)
{
	float* d;
	unsigned short* s;
	Req r;

	s = gm_QueryEntities(*(int*) (entity + 0x178), 1, 1, args[1]);
	if (!s) {
		return 0;
	}
	d = gm_LookupSpecialObject(*s);
	if (d) {
		r.s = s;
		r.id = ctx[1];
		r.arg = ctx[2];
		if (gm_UseSpecialObject(entity, &r) == 1) {
			if (r.dir == 1) {
				g_1009a64[0] = g_1008574[ctx[4] * 37 + 0] * d[3];
				g_1009a64[2] = g_1008574[ctx[4] * 37 + 2] * d[3];
				g_1009a64[4] = g_1008574[ctx[4] * 37 + 4] * d[3];
				g_1009a64[6] = g_1008574[ctx[4] * 37 + 6] * d[3];
				return 0x24;
			}
			if (r.dir == -1) {
				g_1009a64[0] = -(g_1008574[ctx[4] * 37 + 0] * d[3] * 0.5f);
				g_1009a64[2] = -(g_1008574[ctx[4] * 37 + 2] * d[3] * 0.5f);
				g_1009a64[4] = -(g_1008574[ctx[4] * 37 + 4] * d[3] * 0.5f);
				g_1009a64[6] = -(g_1008574[ctx[4] * 37 + 6] * d[3] * 0.5f);
			}
			return 0x24;
		}
	}
	return 0;
}
