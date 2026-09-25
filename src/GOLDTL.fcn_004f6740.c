// FUNCTION: GOLDTL 0x4f6740
// SIZE: 58

#pragma pack(push, 1)
typedef struct
{
	int id;
	char p4[0xe];
	int x12;
	int x16;
	char p1a[2];
	unsigned char x1c;
	char p1d[8];
	unsigned int x25;
	char p29[4];
} Rec2d;
// SIZE 0x2d
#pragma pack(pop)

typedef struct
{
	int a;
	int b;
} Pair;
// SIZE 0x8

extern int g_773d38;
extern Rec2d g_9a3800[512];
extern Pair g_99f800[0x800];

void __cdecl fcn_004f6740(void)
{
	int i;

	g_773d38 = 0;
	for (i = 0; i < 512; i++) {
		g_9a3800[i].x16 = -1;
		g_9a3800[i].x12 = -1;
		g_9a3800[i].id = -1;
		g_9a3800[i].x25 = 0;
	}
	for (i = 0; i < 0x800; i++) {
		g_99f800[i].a = -1;
		g_99f800[i].b = -1;
	}
}
