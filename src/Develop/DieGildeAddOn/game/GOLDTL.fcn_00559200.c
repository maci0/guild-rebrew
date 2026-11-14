/* Build the trade/shop inventory page: a header record with the five column
 * captions, the player's name and the two total labels, then one detail record
 * per listed entity, each handed to the page builder fcn_00402340. */

#include <string.h>
#include "client_types.h"

extern unsigned char g_773d75;
extern char g_868080[];
extern char g_7f4ca0[];
extern pos14_7f4c00 g_7f4c00;

void __cdecl fcn_00500bb0(char*, int, int, int);
void __cdecl fcn_005091d0(int*, char*);
int __cdecl io_FormatTextBuffer(char*, char*, ...);
char* __cdecl fcn_0064d530(char*, const char*, unsigned int);
void __cdecl fcn_00402340(void*, int);
int __cdecl fcn_0050b710(int, unsigned char);

#pragma pack(push, 1)
typedef struct {
	int a;
	char b;
} s5_559200;
#pragma pack(pop)

/* ADDRESS: GOLDTL 0x00559200 */
void __cdecl fcn_00559200(char* o)
{
	int n;
	char g[0xbc];
	char h[0xd0];
	char text[0x100];
	char rows[8][0x24];
	int i;
	char* e;

	n = 8;
	switch (*(int*) (o + 0x70)) {
	case 1:
		fcn_00500bb0(o + 0x52, 0x18, 0, 0);
		*(unsigned short*) (o + 0x56) = 7;
		*(int*) (o + 0x58) = 0;
		*(int*) (o + 0x70) = 0;
		return;
	case 0:
		fcn_005091d0(&n, rows[0]);
		*(unsigned short*) (h + 0) = 1;
		*(unsigned short*) (h + 2) = 3;
		*(unsigned short*) (h + 4) = 0xcf;
		for (i = 0; i < 5; i++) {
			io_FormatTextBuffer(text, "%s", i + 0x16b7);
			fcn_0064d530(h + 6 + i * 0x18, text, 0x18);
			h[6 + i * 0x18 + 0x17] = 0;
		}
		strcpy(h + 0x7e, g_868080 + g_773d75 * 0x2f4);
		strcpy(h + 0x9e, "Verm\xf6gen");
		strcpy(h + 0xb6, "Gewinnpunkte");
		h[0xce] = (char) n;
		fcn_00402340(h, *(unsigned short*) (h + 4));
		for (i = 0; i < n; i++) {
			*(unsigned short*) (g + 0) = 1;
			*(unsigned short*) (g + 2) = 2;
			*(unsigned short*) (g + 4) = 0xb9;
			e = g_7f4ca0 + *(unsigned short*) rows[i] * 0x21c;
			*(int*) (g + 6) = *(int*) (e + 4);
			*(int*) (g + 0xa) = fcn_0050b710(*(int*) (rows[i] + 4), g_773d75);
			*(int*) (g + 0xe) = *(int*) (rows[i] + 0x20);
			g[0x12] = (char) n;
			if (e[2] == 6 || e[2] == 7)
				g[0x13] = 1;
			else
				g[0x13] = 2;
			*(s5_559200*) (g + 0x14) = *(s5_559200*) (e + 0x80);
			fcn_0064d530(g + 0x19, e + 0x30, 0x18);
			g[0x30] = 0;
			io_FormatTextBuffer(text, "%s", (e[9] ? 0x18f : 0x130) + (unsigned char) e[0x164]);
			fcn_0064d530(g + 0x31, text, 0x20);
			g[0x50] = 0;
			io_FormatTextBuffer(text, "%s", (e[9] ? 0x11e : 0x114) + (unsigned char) e[0xd]);
			fcn_0064d530(g + 0x51, text, 0x20);
			g[0x50] = 0;
			io_FormatTextBuffer(text, "%s", (e[9] ? 0x27b : 0x253) + (unsigned char) e[0x166]);
			fcn_0064d530(g + 0x71, text, 0x24);
			g[0x94] = 0;
			io_FormatTextBuffer(text, "%s", (e[9] ? 0x27b : 0x253) + (unsigned char) e[0x169]);
			fcn_0064d530(g + 0x95, text, 0x24);
			g[0xb8] = 0;
			fcn_00402340(g, *(unsigned short*) (g + 4));
		}
		*(pos14_7f4c00*) (o + 0x52) = g_7f4c00;
		fcn_00500bb0(o + 0x52, 1, 0, 0);
		if (*(unsigned short*) (o + 0x56) >= 0x15)
			*(int*) (o + 0x70) += 1;
		break;
	}
}
