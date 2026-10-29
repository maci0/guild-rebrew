#pragma pack(push, 2)
/* SIZE 0xe */
typedef struct {
	int day;
	unsigned short hour;
	int min;
	int sec;
} Time5;
#pragma pack(pop)

/* SIZE 0xf8 */
typedef struct {
	char pad0[4];
	unsigned char kind;
	char pad5[3];
	int owner;
	int target;
	char pad10[0x18];
	Time5 at;
	unsigned char code;
	char pad37[0x21];
	unsigned char who;
	char pad59[3];
	int other;
	char pad60[0x98];
} Msg5;

extern char g_7f4ca0[];
extern char g_7f4c00[];
extern float g_662a70;
extern float g_662a6c;
extern double g_662908;

char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
char* __cdecl gm_FindNextFilteredEntity(void);
int __cdecl fcn_0050c710(char* e, int a, int b);
char* __cdecl fcn_0050dc90(char* e);
float __cdecl gm_RandomFloat01(void);
int __cdecl gm_RandomMod(int n);
int __cdecl fcn_0050f950(int a, int b);
void __cdecl fcn_005904a0(char* s, int v);
void __cdecl fcn_004c5530(Msg5* m);
void __cdecl fcn_00500bb0(Time5* t, int a, int b, int c);
void __cdecl fcn_00546190(char* e);

/* ADDRESS: GOLDTL 0x0057b390 */
void __cdecl fcn_0057b390(char* e)
{
	int count;
	float lim;
	Msg5 m;
	char* list[0x20];
	char* u;
	char* cur;
	char* s;
	int p;
	int k;
	int n;
	int d;
	float r;

	switch (*(int*) (e + 0x70)) {
	case 0:
		u = gm_StartFilteredEntitySearch(1, 5, 0x1d);
		while (u != 0) {
			if (*(unsigned short*) (u + 0x27) != 0xffff) {
				n = fcn_0050c710(u, 0x15, 1);
				lim = (float) n * g_662a70;
				count = 0;
				for (p = 0x7f4ca0; p < 0x85a0a0; p += 0x21c) {
					if (*(unsigned short*) p != 0xffff && *(int*) (p + 0x16c) == (int) u) {
						list[count++] = (char*) p;
					}
				}
				lim += g_662a6c;
				for (k = 0; k < count; k++) {
					r = gm_RandomFloat01();
					s = list[k];
					if (r <= lim) {
						if (!(*(unsigned char*) (s + 0x1b4) & 1) &&
						    (*(unsigned char*) (s + 0x180) == 4 ||
						     *(unsigned char*) (s + 0x180) == 0x8c ||
						     *(unsigned char*) (s + 0x180) == 0x8d)) {
							fcn_005904a0(s, 1);
						}
					} else if (0.5 < r && *(int*) (s + 0x17c) == 0) {
						d = fcn_0050f950(*(unsigned short*) (u + 0x27), *(unsigned short*) s);
						if (-(int) (gm_RandomMod(0x4a) & 0xffff) < d) {
							memset(&m, 0, sizeof(m));
							m.target = *(int*) (u + 1);
							m.owner = *(unsigned short*) (e + 8);
							m.kind = 0x94;
							m.at = *(Time5*) g_7f4c00;
							m.code = 1;
							*(int*) (m.pad59) = *(int*) (s + 4);
							fcn_004c5530(&m);
						}
					}
				}
			}
			u = gm_FindNextFilteredEntity();
		}
		break;
	case 1:
		u = gm_StartFilteredEntitySearch(1, 5, 0x1d);
		while (u != 0) {
			count = 0;
			cur = fcn_0050dc90(u);
			for (p = 0x7f4ca0; p < 0x85a0a0; p += 0x21c) {
				if (*(unsigned short*) p != 0xffff && *(int*) (p + 0x16c) == (int) u) {
					list[count++] = (char*) p;
				}
			}
			fcn_0050c710(u, 0x15, 1);
			for (k = 0; k < count; k++) {
				s = list[k];
				if ((*(unsigned char*) (s + 0x1b4) & 1) &&
				    (*(unsigned char*) (s + 0x180) == 4 ||
				     *(unsigned char*) (s + 0x180) == 0x8c ||
				     *(unsigned char*) (s + 0x180) == 0x8d ||
				     *(unsigned char*) (s + 0x180) == 0) &&
				    (cur == 0 || cur != s)) {
					if (0.75 < gm_RandomFloat01()) {
						fcn_005904a0(s, 0);
					} else if (cur != 0 && (*(unsigned char*) (cur + 0x1b4) & 1) &&
						   *(int*) (s + 0x184) != 0) {
						fcn_005904a0(s, 0);
					}
				}
			}
			u = gm_FindNextFilteredEntity();
		}
		break;
	case 2:
		*(Time5*) (e + 0x52) = *(Time5*) g_7f4c00;
		fcn_00500bb0((Time5*) (e + 0x52), 0, 0x1e, 0);
		*(int*) (e + 0x70) += 1;
		return;
	case 3:
		*(Time5*) (e + 0x52) = *(Time5*) g_7f4c00;
		fcn_00500bb0((Time5*) (e + 0x52), 0, 0x1e, 0);
		*(int*) (e + 0x70) = 0;
		return;
	case -1:
	case -2:
		fcn_00546190(e);
		return;
	default:
		return;
	}
	*(Time5*) (e + 0x52) = *(Time5*) g_7f4c00;
	fcn_00500bb0((Time5*) (e + 0x52), 0, gm_RandomMod(0x14) + 0x14, 0);
	*(int*) (e + 0x70) += 1;
}
