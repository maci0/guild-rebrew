// FUNCTION: GOLDTL 0x4ab0d0
// SIZE: 206

#pragma pack(push, 1)
// SIZE 0xe
typedef struct {
	int a;
	int b;
	int c;
	short d;
} Stamp0e;

// SIZE 0xf8
typedef struct {
	int hdr;
	unsigned char type;
	char pad0[3];
	int from;
	int to;
	char pad1[0x18];
	Stamp0e stamp;
	unsigned char mode;
	char pad2[0x25];
	int to2;
	int with;
	char pad3[0x94];
} MsgF8;
#pragma pack(pop)

extern Stamp0e g_7f4c00;

void __cdecl fcn_004c5530(MsgF8* m);
void __cdecl fcn_005100f0(int id, int v);

#pragma optimize("y", off)
int __cdecl fcn_004ab0d0(char* a1, char* a2, char* a3)
{
	MsgF8 m;
	int flen;
	MsgF8* fdest;

	flen = sizeof(m);
	fdest = &m;
	__asm {
		mov edi, fdest
		mov ebx, flen
		xor eax, eax
		lea ecx, [edi+edi*2]
		and ecx, 3
		sub ebx, ecx
		jle short L1
		rep stosb
		mov ecx, ebx
		and ebx, 3
		shr ecx, 2
		rep stosd
	L1:
		add ecx, ebx
		rep stosb
	}
	m.type = 0x74;
	m.mode = 2;
	m.from = *(int*) (a1 + 4);
	m.to = *(int*) (a2 + 4);
	m.stamp = g_7f4c00;
	m.to2 = *(int*) (a2 + 4);
	m.with = *(int*) (a3 + 4);
	fcn_004c5530(&m);
	fcn_005100f0(*(int*) (a1 + 4), -1);
	return 1;
}
#pragma optimize("", on)
