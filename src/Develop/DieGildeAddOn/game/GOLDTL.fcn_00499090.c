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
int __cdecl fcn_00495400(int kind, int id, int n, Msg* b1, Msg* b2);
int __cdecl fcn_00502cd0(int a, int b, int c, int d);
void __cdecl fcn_004f4830(int size, Stat* st);
int __cdecl gm_RandomMod(int a);
int __cdecl fcn_004a5e60(char* p, int kind, F8 f, int c, float r, int* out);
void __cdecl gm_ResolveEntityById(int* out, int a, int b, int id);
int __cdecl fcn_00579640(char* obj, char* e);
int __cdecl fcn_0050cf50(int* p, int n);
int __cdecl gm_WalkEntityChain(unsigned short id);
int __cdecl fcn_004fa5b0(int a, char* e, void* buf);
float __cdecl fcn_00507e70(char* a, char* b, int i);
float __cdecl gm_RandomFloat01(void);
int __cdecl fcn_0055c0f0(char* obj, char* e);
int __cdecl fcn_0055c0a0(char* obj, char* e);
int __cdecl fcn_0055c050(int* p);

/* ADDRESS: GOLDTL 0x00499090 */
int __cdecl fcn_00499090(int who, char* e, int arg, Msg* o1, Msg* o2)
{
	int v0;
	int v4;
	int v8;
	int id;
	Msg b1;
	Msg b2;
	float f;
	Stat st;
	char buf[0x220];
	F8 ff;
	int r;

	v8 = fcn_0050d320(e, g_773d75);
	if (arg != 0) {
		return 0;
	}
	if (*(int*)(e + 0x170) == 0) {
		if (e[2] == 3) {
			goto flag_check;
		}
		b1.kind = 0;
		b1.a = 0;
		b1.b = 0;
		b2.kind = 0;
		b2.a = 0;
		b2.b = 0;
		r = fcn_00495400(0x17, *(unsigned short*)e, 1, &b1, &b2);
		goto check_call;
	}
	if (e[2] == 3) {
		goto flag_check;
	}
	if (fcn_00502cd0(*(int*)(*(int*)(e + 0x170) + 0x5d), 2, 6, 0x14) != 0) {
		goto find_target;
	}
	b1.kind = 2;
	b1.a = 0x14;
	b1.b = 1;
	b1.f = 0.22f;
	b2.kind = 4;
	b2.a = *(int*)(*(int*)(e + 0x170) + 1);
	b2.b = 1;
	r = fcn_00495400(0x17, *(unsigned short*)e, 1, &b1, &b2);
check_call:
	if (r == 0) {
		return 0;
	}
	*o1 = b1;
	*o2 = b2;
	return r;

flag_check:
	if ((e[0x1e8] & 2) == 0) {
		return 0;
	}
find_target:
	fcn_004f4830(0x18, &st);
	if (st.v[6] != 0 && gm_RandomMod(4) == 0 && g_77261c == 0) {
		return 0;
	}
	if (o1->kind != 0) {
		return 0;
	}
	id = -1;
	ff.mask = 0x344015;
	ff.b = 1;
	if (g_77261c != 0) {
		fcn_004a5e60(g_77261c, 4, ff, 0, 100.0f, &id);
		if (id != -1) {
			goto have_id;
		}
	}
	v8 = gm_RandomMod(0x20) & 0xffff;
	if (fcn_004a5e60(e, 6, ff, 0, (float)v8 + 19.0f, &id) == 0) {
		return 0;
	}
have_id:
	gm_ResolveEntityById(&v0, 0, 0, id);
	if (v0 == 0) {
		return 0;
	}
	if (*(unsigned short*)(v0 + 0x27) == 0xffff) {
		return 0;
	}
	if (fcn_00579640((char*)((unsigned int)*(unsigned short*)(v0 + 0x27) * 0x21c + 0x7f4ca0), e) == 0) {
		return 0;
	}
	memset(buf, 0, 0x220);
	buf[0] = 1;
	v4 = fcn_0050cf50((int*)v0, 100);
	f = (float)v4 * 0.05f;
	v4 = gm_WalkEntityChain(*(unsigned short*)e);
	v4 = (int)((float)v4 * 0.02f + f);
	r = fcn_004fa5b0(0x1b, e, buf);
	if ((r & 2) != 0) {
		v4 = v4 / 2;
	}
	if ((float)v8 * 0.44f < (float)v4) {
		return 0;
	}
	if (fcn_00507e70(e, (char*)((unsigned int)*(unsigned short*)(v0 + 0x27) * 0x21c + 0x7f4ca0), 2) + gm_RandomFloat01() < 1.0f) {
		b1.kind = 0xe;
		b1.a = 2;
		b1.b = 1;
		b1.f = 0;
		b2.kind = 0;
		b2.a = 0;
		b2.b = 0;
		r = fcn_00495400(0x17, *(unsigned short*)e, 0, &b1, &b2);
		if (r == 0) {
			return 0;
		}
		*o1 = b1;
		*o2 = b2;
		return r;
	}
	if (fcn_0055c0f0((char*)((unsigned int)*(unsigned short*)(v0 + 0x27) * 0x21c + 0x7f4ca0), e) == 0) {
		return 0;
	}
	if (fcn_0055c0a0((char*)((unsigned int)*(unsigned short*)(v0 + 0x27) * 0x21c + 0x7f4ca0), e) == 0) {
		return 0;
	}
	if (fcn_0055c050((int*)v0) == 0) {
		return 0;
	}
	if (fcn_00579640((char*)((unsigned int)*(unsigned short*)(v0 + 0x27) * 0x21c + 0x7f4ca0), e) == 0) {
		return 0;
	}
	o1->kind = 4;
	o1->a = *(int*)(v0 + 1);
	o1->d = v4;
	o1->b = 1;
	o1->f = (float)(st.v[6] * 2 + 1);
	return 0x17;
}
