// FUNCTION: GOLDTL 0x5649d0
// SIZE: 434

#pragma pack(2)
// SIZE 0xe
struct pos14 {
	int a;
	int b;
	int c;
	short d;
};
#pragma pack()

// SIZE 0x21c
struct house {
	unsigned short id;
	unsigned char type;
	char pad3;
	int handle;
	char pad8[0x214];
};

// SIZE 0x2f4
struct rec {
	unsigned short v;
	char pad2[0x2f2];
};

extern struct pos14 g_7f4c00;
extern struct house g_7f4ca0[];
extern unsigned char g_773d75;
extern struct rec g_8680b4[];

void __cdecl fcn_00500bb0(struct pos14*, int, int, int);
char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
char* __cdecl fcn_00508e40(int);
char* __cdecl fcn_00502cd0(int, int, int, int);
void __cdecl fcn_0051af00(char*, int, ...);
void __cdecl fcn_00545e80(int, int, char*, int, int, int, int, int, int);
void __cdecl fcn_004f4f60(int, int, int, int, int);

void __cdecl fcn_005649d0(char* e)
{
	char* o;
	char buf[0x200];
	char* q;
	struct house* h;
	char* r;
	int v;

	*(struct pos14*) (e + 0x52) = g_7f4c00;
	*(struct pos14*) (e + 0xc4) = g_7f4c00;
	fcn_00500bb0((struct pos14*) (e + 0xc4), *(int*) (e + 0xb8) * 24, 0, 0);
	*(short*) (e + 0xc8) = 8;
	*(int*) (e + 0xca) = 0;
	*(int*) (e + 0xce) = 0;
	*(int*) (e + 0xbc) = *(int*) (e + 0xb8);
	q = gm_StartFilteredEntitySearch(1, 1, *(int*) (e + 0xac));
	if (q == 0 || (e[0x78] & 2) == 0) {
		return;
	}
	h = &g_7f4ca0[*(unsigned short*) (q + 0x27)];
	o = fcn_00508e40(*(int*) (e + 0xb0));
	if (h->type != 6 && h->type != 7) {
		return;
	}
	v = 0;
	r = fcn_00502cd0(*(int*) (q + 0x5d), 1, 0, g_8680b4[g_773d75].v);
	if (r != 0) {
		v = *(int*) (r + 0xe);
	}
	fcn_0051af00(buf, 0x18d7, *(unsigned short*) o, q, *(int*) (e + 0xb4), *(int*) (e + 0xc0), *(int*) (e + 0xb8), 0x5d, v);
	fcn_00545e80(h->handle, -1, buf, 0, 0x5ec, *(int*) (q + 1), -1, 0, 0);
	fcn_004f4f60(0xe, *(int*) (e + 0xc0), h->handle, *(int*) (e + 0xb0), *(int*) (q + 1));
}
