#include <string.h>

typedef struct Stat {
	int v[9];
} Stat;
/* SIZE 0x24 */

typedef struct Msg {
	unsigned char kind;
	char pad1[3];
	int a;
	int b;
	int c;
	int d;
	float f;
} Msg;
/* SIZE 0x18 */

typedef struct F8 {
	int mask;
	int b;
} F8;
/* SIZE 0x8 */

extern unsigned char g_773d75;
extern char* g_77261c;
extern char g_7f4ca0[];

int __cdecl fcn_0050d320(char* e, unsigned char flag);
int __cdecl ai_SelectBestMethod(int kind, int id, int n, Msg* b1, Msg* b2);
int __cdecl fcn_00502cd0(int a, int b, int c, int d, int e);
void __cdecl fcn_004f4830(int size, Stat* st);
unsigned short __cdecl gm_RandomMod(int a);
int __cdecl fcn_004a5e60(char* p, int kind, F8 f, int c, float r, int* out);
void __cdecl gm_ResolveEntityById(int* out, int a, int b, int id);
int __cdecl fcn_00579640(char* obj, char* e);
int __cdecl gm_CalculateGebaeudeValue(int* p, int n);
int __cdecl gm_WalkEntityChain(unsigned short id);
int __cdecl fcn_004fa5b0(int a, char* e, void* buf);
float __cdecl fcn_00507e70(char* a, char* b, int i);
float __cdecl gm_RandomFloat01(void);
int __cdecl he_HasNoActiveEvent04b(char* obj, char* e);
int __cdecl he_HasNoActiveAction0x2e(char* obj, char* e);
int __cdecl fcn_0055c050(int* p);

/* ADDRESS: GOLDTL 0x00499090 */
int __cdecl fcn_00499090(int who, char* e, int arg, Msg* o1, Msg* o2)
{
	int targetRec;
	int v4;
	int v8;
	int id;
	Msg b1;
	Msg b2;
	Stat st;
	int buf[0x88];
	char* owner;
	F8 ff;
	int r;

	v8 = fcn_0050d320(e, g_773d75);
	if (arg != 0) {
		return 0;
	}
	if (*(int*)(e + 0x170) == 0 && e[2] != 3) {
		b1.kind = 0;
		b1.a = 0;
		b1.b = 0;
		b2.kind = 0;
		b2.a = 0;
		b2.b = 0;
		r = ai_SelectBestMethod(0x17, *(unsigned short*)e, 1, &b1, &b2);
		if (r != 0) {
			*o1 = b1;
			*o2 = b2;
		}
		return r;
	}
	if (e[2] == 3) {
		if ((e[0x1e8] & 2) == 0) {
			return 0;
		}
	} else if (fcn_00502cd0(*(int*)(*(int*)(e + 0x170) + 0x5d), 2, 6, 0, 0x14) == 0) {
		b1.kind = 2;
		b1.a = 0x14;
		b1.b = 1;
		b1.f = 0.22f;
		b2.kind = 4;
		b2.a = *(int*)(*(int*)(e + 0x170) + 1);
		b2.b = 1;
		r = ai_SelectBestMethod(0x17, *(unsigned short*)e, 1, &b1, &b2);
		if (r != 0) {
			*o1 = b1;
			*o2 = b2;
		}
		return r;
	}
	fcn_004f4830(0x18, &st);
	if (st.v[6] != 0 && gm_RandomMod(4) == 0 && g_77261c == 0) {
		return 0;
	}
	if (o1->kind == 0) {
		ff.mask = 0x344015;
		ff.b = 1;
		id = -1;
		if (g_77261c != 0) {
			fcn_004a5e60(g_77261c, 4, ff, 0, 100.0f, &id);
		}
		if (id != -1 || fcn_004a5e60(e, 6, ff, 0, (float)gm_RandomMod(0x20) + 19.0f, &id) != 0) {
			gm_ResolveEntityById(&targetRec, 0, 0, id);
			if (targetRec != 0) {
				if (*(unsigned short*)(targetRec + 0x27) != 0xffff) {
					if (fcn_00579640(g_7f4ca0 + *(unsigned short*)(targetRec + 0x27) * 0x21c, e) != 0) {
						memset(buf, 0, 0x220);
						buf[0] = 1;
						v4 = (int)((float)gm_CalculateGebaeudeValue((int*)targetRec, 100) * 0.05f + (float)gm_WalkEntityChain(*(unsigned short*)e) * 0.02f);
						owner = g_7f4ca0 + *(unsigned short*)(targetRec + 0x27) * 0x21c;
						if ((fcn_004fa5b0(0x1b, e, buf) & 2) != 0) {
							v4 = v4 / 2;
						}
						if (!((float)v8 * 0.44f < (float)v4)) {
							if (!(fcn_00507e70(e, owner, 2) + gm_RandomFloat01() >= 1.0f)) {
								b1.kind = 0xe;
								b1.a = 2;
								b1.b = 1;
								b1.f = 0;
								b2.kind = 0;
								b2.a = 0;
								b2.b = 0;
								r = ai_SelectBestMethod(0x17, *(unsigned short*)e, 0, &b1, &b2);
								if (r != 0) {
									*o1 = b1;
									*o2 = b2;
								}
								return r;
							}
							if (he_HasNoActiveEvent04b(g_7f4ca0 + *(unsigned short*)(targetRec + 0x27) * 0x21c, e) != 0) {
								if (he_HasNoActiveAction0x2e(g_7f4ca0 + *(unsigned short*)(targetRec + 0x27) * 0x21c, e) != 0) {
									if (fcn_0055c050((int*)targetRec) != 0) {
										if (fcn_00579640(g_7f4ca0 + *(unsigned short*)(targetRec + 0x27) * 0x21c, e) != 0) {
											o1->kind = 4;
											o1->a = *(int*)(targetRec + 1);
											o1->d = v4;
											o1->b = 1;
											o1->f = (float)(st.v[6] * 2 + 1);
											return 0x17;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	return 0;
}
