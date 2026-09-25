// FUNCTION: GOLD 0x4f36b0
// SIZE: 38
// FUNCTION: GOLDTL 0x4f57e0
// SIZE: 38

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

extern Rec2d g_9a3800[512];

int __cdecl fcn_004f57e0(void)
{
	int r;
	int i;

	r = -1;
	for (i = 0; i < 512; i++) {
		if (g_9a3800[i].x25 == 0) {
			r = i;
			i = 512;
		}
	}
	return r;
}
