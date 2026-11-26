typedef struct Req {
	unsigned short* s;
	int id;
	int arg;
	int dir;
	int pad;
} Req;
// SIZE 0x14

extern float g_100af14;
extern float g_100af34;
extern unsigned char g_773d75;

char* __cdecl fcn_00502cd0(int a, int b, int c, ...);
float* __cdecl fcn_005c61e0(int id);
int __cdecl gm_UseSpecialObject(char* e, Req* r);
char* __cdecl gm_StartFilteredEntitySearch(int arg_count, ...);
int __cdecl cm_SendSellObjekt(int a, int b, int c, int d, unsigned char k, int n);
void __cdecl cm_RequestChangeBits(int id, int a2, int a3, int a4, int a5);

/* ADDRESS: GOLDTL 0x0048ef30 */
int __cdecl ai_RunAlchemistryItems(char* e, char* p, char* q)
{
	float* d;
	char* s;
	char* t;
	Req request;

	if (*p == 2) {
		if (*(int*) (p + 0x10) == 1) {
			cm_SendSellObjekt(*(int*) (e + 4), -1, *(int*) (p + 4), 1, g_773d75, 0);
			cm_RequestChangeBits(*(int*) (e + 4), 0x1cc, 4, 0x40000000, 0);
			return 0x48;
		}
		if (*(int*) (p + 0x10) != 2 || *q != 4) {
			return 0;
		}
		t = gm_StartFilteredEntitySearch(2, 1, *(int*) (q + 0xc), 5, 0x1e);
		if (t == 0) {
			return 0;
		}
		s = fcn_00502cd0(*(int*) (t + 0x5d), 2, 6, 0, 0x2a);
		if (s == 0) {
			return 0;
		}
		t = fcn_00502cd0(*(int*) (s + 0x14), 2, 6, 0, *(int*) (p + 4));
		if (t == 0 || *(int*) (t + 0xe) <= 1) {
			return 0;
		}
		cm_SendSellObjekt(*(int*) (e + 4), *(int*) (s + 2), *(int*) (p + 4), 1, g_773d75, 0);
		return 0x48;
	}
	if (*p != 1) {
		return 0;
	}
	s = fcn_00502cd0(*(int*) (e + 0x178), 1, 1, *(int*) (p + 4));
	if (!s) {
		return 0;
	}
	d = fcn_005c61e0(*(unsigned short*) s);
	if (d) {
		request.s = (unsigned short*) s;
		request.id = *(int*) (q + 4);
		request.arg = *(int*) (q + 8);
		request.dir = 0;
		request.pad = 0;
		if (gm_UseSpecialObject(e, &request) == 1) {
			if (request.dir == 1) {
				g_100af34 = g_100af14 * d[3];
				return 0x1c;
			}
			if (request.dir == -1) {
				g_100af34 = g_100af14 * d[3] * -0.5f;
			}
			return 0x1c;
		}
	}
	return 0;
}
