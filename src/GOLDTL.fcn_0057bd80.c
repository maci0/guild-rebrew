// FUNCTION: GOLD 0x00573840
// FUNCTION: GOLDTL 0x57bd80

// SIZE 0x21c
struct house {
	unsigned short id;
	char pad2[0x21a];
};

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern char g_7f4ca0[];

int __cdecl fcn_004c4450(int);
char* __cdecl fcn_00508e40(int);
int __cdecl fcn_004c5620(int, char*);
void __cdecl fcn_00546190(char*);
void __cdecl fcn_0057c630(struct house*, int);
void __cdecl fcn_0057bed0(struct house*, char*, int);
void __cdecl fcn_00500bb0(pos14_7f4c00*, int, int, int);
unsigned short __cdecl fcn_0042e410(int);

void __cdecl fcn_0057bd80(char* u)
{
	char* h2;
	struct house* h;

	if (*(int*) (u + 0x70) != -1 && *(int*) (u + 0x70) != -2) {
		if (u[0x78] & 4) {
			return;
		}
		if (*(int*) (u + 0x84) != -1 && fcn_004c4450(*(int*) (u + 0x84)) == 0) {
			return;
		}
		*(int*) (u + 0x84) = -1;
		*(pos14_7f4c00*) (u + 0x52) = g_7f4c00;
		h2 = fcn_00508e40(*(int*) (u + 0xb0));
		if (h2 == 0 || ((struct house*)g_7f4ca0)[*(unsigned short*) (u + 8)].id == 0xffff) {
			*(int*) (u + 0x84) = fcn_004c5620(-1, u);
			return;
		}
		h = &((struct house*)g_7f4ca0)[*(unsigned short*) (u + 8)];
		switch (*(int*) (u + 0x70)) {
		case 0:
			fcn_0057bed0(h, h2, *(int*) (u + 0xac));
			fcn_00500bb0((pos14_7f4c00*) (u + 0x52), 0x18, 0, 0);
			*(short*) (u + 0x56) = 6;
			*(int*) (u + 0x58) = fcn_0042e410(4) * 15 + 5;
			*(int*) (u + 0x84) = fcn_004c5620(1, u);
			break;
		case 1:
			fcn_0057c630(h, *(int*) (u + 0xac));
			*(int*) (u + 0x84) = fcn_004c5620(-1, u);
			break;
		}
	} else {
		fcn_00546190(u);
	}
}
