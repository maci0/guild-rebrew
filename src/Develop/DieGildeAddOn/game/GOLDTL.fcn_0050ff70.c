


extern char g_7f4ca4[];
extern unsigned char* lpGebaeudePROT;
extern char g_699adc[];
extern char g_699af0[];

#include "client_packet_builder.h"
void __cdecl fcn_004c4670(int a, int b, int off, char* v);
void __cdecl fcn_004c5360(void);
void __cdecl fcn_0051af00(char* buf, int id, ...);
void __cdecl fcn_00545d40(int h, int a, char* text, int b, int c, char* snd);
void __cdecl fcn_004c5fd0(int h);

void __cdecl fcn_0050ff70(char* o, int delta)
{
	char d;
	char other[0x400];
	char same[0x400];
	unsigned char* rec;
	char* p;

	d = (char) delta;
	if (delta + o[0x5c] < 0) {
		d = -o[0x5c];
	}
	if (delta + o[0x5c] > 100) {
		d = 100 - o[0x5c];
	}
	fcn_004c4510(o, *(int*) (o + 1));
	fcn_004c4670(1, 1, 0x5c, &d);
	fcn_004c5360();
	if (*o != 0 && d + o[0x5c] <= 0) {
		rec = lpGebaeudePROT + (unsigned char) *o * 589;
		if (*rec != 0xf && *rec != 0x1c && *rec != 0x1b && *rec != 0xa && *rec != 6 && *rec < 0x17 && *rec != 0x10) {
			for (p = g_7f4ca4; (int) p < (int) (g_7f4ca4 + 0x65400); p += 0x21c) {
				if (*(unsigned char*) (p - 2) == 6 || *(unsigned char*) (p - 2) == 7) {
					if (*(unsigned short*) (p - 4) != *(unsigned short*) (o + 0x27)) {
						fcn_0051af00(other, 0x1c52, *(unsigned short*) (o + 0x27), o);
						fcn_00545d40(*(int*) p, -1, other, 0, 0x5fe, g_699af0);
					} else {
						fcn_0051af00(same, 0x1c53, o);
						fcn_00545d40(*(int*) p, -1, same, 0, 0x5fe, g_699adc);
					}
				}
			}
			fcn_004c5fd0(*(int*) (o + 1));
		}
	}
}
