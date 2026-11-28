typedef struct Req {
	unsigned short* s;
	int id;
	int arg;
	int dir;
	int pad;
} Req;
// SIZE 0x14

extern float g_10095a4;
extern float g_10095c4;

unsigned short* __cdecl gm_QueryEntities(int a, int b, int c, int d);
float* __cdecl gm_LookupSpecialObject(int id);
int __cdecl gm_UseSpecialObject(char* e, Req* r);

/* ADDRESS: GOLDTL 0x0049a4b0 */
/* ADDRESS: GOLDDE 0x00488ef0 */
int __cdecl ai_RunUseObjectAnsehen(char* e, int* p, int* q)
{
	float* d;
	unsigned short* s;
	Req r;

	s = gm_QueryEntities(*(int*) (e + 0x178), 1, 1, p[1]);
	if (!s) {
		return 0;
	}
	d = gm_LookupSpecialObject(*s);
	if (d) {
		r.s = s;
		r.id = q[1];
		r.arg = q[2];
		r.dir = 0;
		r.pad = 0;
		if (gm_UseSpecialObject(e, &r) == 1) {
			if (r.dir == 1) {
				g_10095c4 = g_10095a4 * d[3];
				return 0x1c;
			}
			if (r.dir == -1) {
				g_10095c4 = g_10095a4 * d[3] * -0.5f;
			}
			return 0x1c;
		}
	}
	return 0;
}
