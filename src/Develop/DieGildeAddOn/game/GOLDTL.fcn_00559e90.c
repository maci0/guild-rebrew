


// SIZE 0x10
struct job {
	int house;
	int item;
	unsigned char f8;
	unsigned char flags;
	char pada[6];
};

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;

int __cdecl fcn_004c4450(int);
void __cdecl fcn_00500bb0(pos14_7f4c00*, int, int, int);
int __cdecl fcn_00559660(struct job*);
void __cdecl fcn_00559aa0(struct job*);
int __cdecl fcn_00559760(struct job*, int, int);
int __cdecl fcn_004c5620(int, char*);
void __cdecl fcn_00546190(char*);

void __cdecl fcn_00559e90(char* u)
{
	int n;
	int i;

	if (*(int*) (u + 0x70) != -1 && *(int*) (u + 0x70) != -2) {
		if (u[0x78] & 4) {
			return;
		}
		if (*(int*) (u + 0x84) != -1 && fcn_004c4450(*(int*) (u + 0x84)) == 0) {
			return;
		}
		*(pos14_7f4c00*) (u + 0x52) = g_7f4c00;
		fcn_00500bb0((pos14_7f4c00*) (u + 0x52), 0, 5, 0);
		n = 0;
		*(int*) (u + 0x84) = -1;
		if (*(unsigned short*) (u + 0x56) >= 0x11) {
			for (i = 0; i < 10; i++) {
				if (fcn_00559660(&((struct job*) (u + 0xac))[i]) == 2) {
					n++;
				}
			}
			if (n == 0) {
				*(unsigned short*) (u + 0x56) = (unsigned short) n;
				(*(int*) (u + 0x52))++;
			}
			fcn_004c5620(0, u);
			return;
		}
		for (i = 0; i < 10; i++) {
			if (((struct job*) (u + 0xac))[i].flags & 4) {
				fcn_00559660(&((struct job*) (u + 0xac))[i]);
			} else {
				fcn_00559aa0(&((struct job*) (u + 0xac))[i]);
			}
			if (((struct job*) (u + 0xac))[i].flags & 1) {
				n++;
			}
		}
		for (i = 0; i < 10; i++) {
			*(int*) (u + 0x84) = fcn_00559760(&((struct job*) (u + 0xac))[i], n, 0);
			if (*(int*) (u + 0x84) != -1) {
				*(pos14_7f4c00*) (u + 0x52) = g_7f4c00;
				fcn_00500bb0((pos14_7f4c00*) (u + 0x52), 0, 1, 0);
				break;
			}
		}
		fcn_004c5620(0, u);
	} else {
		fcn_00546190(u);
	}
}
