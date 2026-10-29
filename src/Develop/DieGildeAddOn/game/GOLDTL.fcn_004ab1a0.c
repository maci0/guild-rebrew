#include <string.h>

typedef struct Rec18 {
	char pad0[8];
	unsigned char x8;
	char pad9[0xf];
} Rec18;

typedef struct Msg {
	unsigned char type;
	char pad1[3];
	unsigned int object;
	char pad8[8];
	unsigned int param;
	char pad14[4];
} Msg;

int __cdecl gm_AccumulateTyped2(void*);
void* __cdecl gm_StartFilteredEntitySearch(int, ...);
void* __cdecl gm_FindNextFilteredEntity(void);
void* __cdecl fcn_00502cd0(int, ...);
int __cdecl gm_RandomMod(int);
float __cdecl gm_RandomFloat01(void);
int __cdecl fcn_004e8b40(int, Rec18*);
int __cdecl fcn_004f7120(unsigned int, void*, void*, void*, void*);

/* ADDRESS: GOLDTL 0x004ab1a0 */
unsigned int __cdecl fcn_004ab1a0(int* a0, Msg* a1, Msg* a2)
{
	Rec18 rec;
	int found[16];
	int v6;
	int n;
	int i;
	int k;
	int tries;
	int g;
	unsigned int out2;
	unsigned int out1;
	unsigned char* ent;
	unsigned char* obj;

	if ((*(unsigned int*) ((char*) a0 + 0x1cc) & 0x2000000) == 0) {
		g = *(unsigned int*) 0x7f4c04;
		if ((unsigned short) g >= 0x15 &&
		    (g & 0xffff) % 3 == *(unsigned int*) ((char*) a0 + 4) % 3) {
			v6 = gm_AccumulateTyped2(a0);
			for (k = 0; k < 16; k++) {
				found[k] = 0;
			}
			n = 0;
			ent = (unsigned char*) gm_StartFilteredEntitySearch(1, 5, 0x16);
			if (ent != 0) {
				do {
					if (*(unsigned short*) (ent + 0x27) != 0xffff &&
					    *(unsigned short*) (ent + 0x27) != *(unsigned short*) a0 &&
					    *((unsigned char*) (*(unsigned int*) 0x868050) + (unsigned int) *ent * 0x24d + 0x247) > 1 &&
					    (obj = (unsigned char*) fcn_00502cd0(*(unsigned int*) (ent + 0x5d), 1, 0, 0x120)) != 0 &&
					    (obj = (unsigned char*) fcn_00502cd0(*(unsigned int*) (obj + 0x14), 1, 0, 300)) != 0) {
						found[n * 2] = (int) ent;
						found[n * 2 + 1] = (int) obj;
						n++;
					}
					ent = (unsigned char*) gm_FindNextFilteredEntity();
				} while (ent != 0);
				if (n != 0) {
					k = gm_RandomMod(n) & 0xffff;
					ent = (unsigned char*) found[k * 2];
					obj = (unsigned char*) found[k * 2 + 1];
					i = gm_RandomMod(3) & 0xffff;
					tries = 3;
					do {
						if (fcn_004f7120(*(unsigned int*) (obj + 0x1c + i * 4),
								 (void*) ((unsigned int) *(unsigned short*) (ent + 0x27) * 0x21c + 0x7f4ca0),
								 &a0, &out2, &out1) != 0 &&
						    !((float) v6 * *(float*) 0x662b10 < (float) (int) a0)) {
							fcn_004e8b40(*(unsigned char*) ((out2 & 0xffff) * 0x21c + 0x7f4e06), &rec);
							if ((unsigned short) gm_RandomMod(0xc) > (unsigned short) rec.x8) {
								return 0;
							}
							if (gm_RandomFloat01() < *(float*) 0x6628cc) {
								memset(a1, 0, 0x18);
								memset(a2, 0, 0x18);
							} else {
								a1->type = 0x13;
								a1->object = *(unsigned int*) (obj + 0x1c + i * 4);
								a1->param = (unsigned int) a0;
								a2->type = 4;
								a2->object = *(unsigned int*) (ent + 1);
							}
							return 1;
						}
						i = (i + 1) % 3;
						tries--;
					} while (tries != 0);
				}
			}
		}
	}
	return 0;
}
