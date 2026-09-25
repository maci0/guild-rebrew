// FUNCTION: GOLD 0x00511b00
// SIZE: 235
// FUNCTION: GOLDTL 0x00515250
// SIZE: 235

// SIZE 0x21c
typedef struct {
	short slot;
	unsigned char type;
	char pad3[9];
	unsigned char faith;
	char padd[0x21c - 0xd];
} Entity;

// SIZE 0x2f4
typedef struct {
	char name[0x2f4];
} Variant;

extern Entity g_7f4ca0[768];
extern Variant g_868060[4];
extern unsigned char g_7747b0;
extern Entity* g_773dac;
extern Entity* g_773db0;
extern Entity* g_773db4[];

void __cdecl fcn_004432d0(int, int);
void __cdecl fcn_005016c0(void);
void __cdecl fcn_005016f0(int);
void __cdecl fcn_0041d9e0(char*);
void __cdecl fcn_00515010(void);
void __cdecl fcn_00510100(void);

void __cdecl fcn_00515250(void)
{
	Entity** p;
	int i;
	int n;

	fcn_004432d0(0, 0);
	if ((g_7747b0 & 0x40) == 0) {
		fcn_005016c0();
		for (i = 0; i < 4; i++) {
			if (g_868060[i].name[0] == 0) {
				break;
			}
			fcn_005016f0(i);
		}
	}
	n = 2;
	for (i = 1; i < 768; i++) {
		if (n == 0) {
			break;
		}
		if (g_7f4ca0[i].type == 0xc) {
			if (g_7f4ca0[i].faith == 0) {
				g_773dac = &g_7f4ca0[i];
				n--;
			} else if (g_7f4ca0[i].faith == 1) {
				g_773db0 = &g_7f4ca0[i];
				n--;
			}
		}
	}
	p = g_773db4;
	for (i = 0; i < 768; i++) {
		if (g_7f4ca0[i].type == 0xb) {
			*p++ = &g_7f4ca0[i];
		}
	}
	if (g_773dac == 0) {
		fcn_0041d9e0("init_LocalData(): gm_RichterKatholisch==NULL");
	}
	if (g_773db0 == 0) {
		fcn_0041d9e0("init_LocalData(): gm_RichterEvangelisch==NULL");
	}
	if ((g_7747b0 & 0x44) == 0) {
		fcn_00515010();
	}
	fcn_00510100();
}
