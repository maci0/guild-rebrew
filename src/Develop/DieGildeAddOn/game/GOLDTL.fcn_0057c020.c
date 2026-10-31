


// SIZE 0x18
typedef struct {
	unsigned char c0;
	char pad1[3];
	int id;
	char pad8[0x10];
} rec18;

// SIZE 0x21c
struct house {
	unsigned short id;
	unsigned char type;
	char pad3;
	int owner;
	char pad8[0x15e];
	unsigned char job;
	char pad167[0xb5];
};

extern char g_7f4ca0[];

int __cdecl fcn_004e8b40(int, rec18*);
unsigned short __cdecl gm_RandomMod(int);
void __cdecl fcn_004ec2d0(struct house*, int, int);
void __cdecl fcn_004c54c0(int, int, int, int);
void __cdecl io_FormatTextBuffer(char*, int, ...);
int __cdecl fcn_00545d40(int, int, char*, unsigned char, int, char*);

void __cdecl fcn_0057c020(struct house* a, struct house* b)
{
	rec18 r;
	char text1[0x400];
	char text2[0x400];
	int i;
	int d;
	int p;
	int id;

	if (fcn_004e8b40(b->job, &r) != 0 && (p = r.id) != 0) {
		fcn_004ec2d0(b, p, -20 - gm_RandomMod(0x10));
	} else if (b->type != 6 && b->type != 7 && b->type != 5) {
		fcn_004ec2d0(b, gm_RandomMod(3) + 1, gm_RandomMod(0x10) + 0x14);
	} else {
		d = -20 - gm_RandomMod(0x10);
		for (i = 0; i < 768; i++) {
			if (i != b->id && (((struct house*)g_7f4ca0)[i].type == 6 || ((struct house*)g_7f4ca0)[i].type == 7 || ((struct house*)g_7f4ca0)[i].type == 5)) {
				fcn_004c54c0(b->owner, ((struct house*)g_7f4ca0)[i].owner, d, 1);
			}
		}
	}
	if (b == a) {
		id = 0x41dd;
	} else {
		id = 0x41dc;
	}
	io_FormatTextBuffer(text1, 0x41df);
	io_FormatTextBuffer(text2, id, text1);
	fcn_00545d40(b->owner, -1, text2, 1, 0x5fb, 0);
}
