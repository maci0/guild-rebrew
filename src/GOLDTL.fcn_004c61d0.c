


typedef struct {
	unsigned short id;
	char pad2[0xe];
	int f10;
	int f14;
	int f18;
	int f1c;
	float f20;
	float f24;
	float f28;
	float f2c;
	int f30;
	int f34;
	float f38;
	char pad3c[0x44];
} slot80;
// SIZE 0x80

#pragma pack(1)
typedef struct {
	char kind;
	char pad1[0xf];
	unsigned char f10;
	unsigned short f11;
	int f13;
	int f17;
	int f1b;
	float f1f;
	float f23;
	float f27;
	float f2b;
	char pad2f[0x6d];
} msg9c;
// SIZE 0x9c
#pragma pack()

slot80* __cdecl fcn_005027d0(int, int);
int __cdecl fcn_004c4330(msg9c*);

int __cdecl fcn_004c61d0(slot80* e, unsigned char kind)
{
	slot80 l;
	msg9c m;
	slot80* s;

	s = fcn_005027d0(kind, e->id);
	l = *e;
	m.kind = 0x40;
	l.f10 -= s->f10;
	l.f14 -= s->f14;
	l.f18 -= s->f18;
	l.f20 -= s->f20;
	l.f24 -= s->f24;
	l.f2c -= s->f2c;
	l.f38 -= s->f38;
	m.f10 = kind;
	m.f11 = e->id;
	m.f13 = l.f10;
	m.f17 = l.f14;
	m.f1b = l.f18;
	m.f1f = l.f20;
	m.f23 = l.f24;
	m.f27 = l.f2c;
	m.f2b = l.f38;
	return fcn_004c4330(&m);
}
