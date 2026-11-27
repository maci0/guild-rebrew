extern char* g_104049c;
extern unsigned int g_10404a0;
#include "Develop/DieGildeAddOn/game/game_data.h"

void __cdecl d3_ReleaseTextureInterface(char*);
void __cdecl d3_ReleaseTexture(int);

/* ADDRESS: GOLDTL 0x0045bfb0 */
void __cdecl d3_ReleaseTexture(int obj)
{
	char* o;
	char* p;
	unsigned int i;
	unsigned int j;
	int idx;
	int nidx;

	o = (char*) obj;
	if (o == 0 || *(int*) (o + 0x40) <= 0) {
		return;
	}
	if (*(int*) (o + 0x5c) > 0 && *(char*) (o + 0x5d) == 0) {
		p = g_104049c;
		for (i = 0; i < g_10404a0; i++, p += 0x70) {
			if (*(int*) (p + 0x40) > 0 && *(int*) (p + 0x48) == *(int*) (o + 0x48) &&
			    *(unsigned char*) (p + 0x5d) > 0) {
				d3_ReleaseTexture((int) p);
			}
		}
	}
	*(int*) (o + 0x40) = *(int*) (o + 0x40) - 1;
	if (*(int*) (o + 0x40) > 0) {
		return;
	}
	if (*(char*) (o + 0x54) & 2) {
		*(int*) (o + 0x50) = 0;
	} else {
		idx = (int) (o - g_104049c) / 0x70;
		p = g_104049c;
		for (i = 0; i < g_10404a0; i++, p += 0x70) {
			if (*(int*) (p + 0x40) > 0 && (*(char*) (p + 0x54) & 2) &&
			    *(int*) (p + 0x44) == idx) {
				*(char*) (p + 0x54) = *(char*) (p + 0x54) & 0xfd;
				*(int*) (p + 0x44) = *(int*) (o + 0x44);
				nidx = (int) (p - g_104049c) / 0x70;
				for (j = i + 1, p += 0x70; j < g_10404a0; j++, p += 0x70) {
					if (*(int*) (p + 0x40) > 0 && (*(char*) (p + 0x54) & 2) &&
					    *(int*) (p + 0x44) == idx) {
						*(int*) (p + 0x44) = nidx;
					}
				}
				break;
			}
		}
		if (i == g_10404a0) {
			d3_ReleaseTextureInterface(o);
		}
	}
	*(int*) (o + 0x40) = 0;
	g_10405c4 = g_10405c4 - 1;
}
