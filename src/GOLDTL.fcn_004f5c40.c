// FUNCTION: GOLDTL 0x4f5c40
// SIZE: 39

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

int __cdecl fcn_004f5bf0(unsigned int, int);

int __cdecl fcn_004f5c40(unsigned int key, int start, int* out)
{
	int i;

	i = fcn_004f5bf0(key, start);
	if (i >= 0) {
		*out = g_9a3800[i].id;
	}
	return i;
}
