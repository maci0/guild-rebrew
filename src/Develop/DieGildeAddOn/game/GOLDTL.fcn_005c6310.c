#include "client_data.h"
#include "Develop/DieGildeAddOn/game/game_player.h"
int __cdecl fcn_00500d20(void*, void*);
unsigned short* __cdecl fcn_00502cd0(int, int, int);
int __cdecl fcn_005c61e0(int);
unsigned short* __cdecl gm_NextEntityQueryMatch(void);
int __cdecl gm_StartFilteredEntitySearch(int, int, int);
void __cdecl fcn_004c5420(int, int, int, int, int);
int __cdecl fcn_0047dca0(char*);
void __cdecl fcn_004c51f0(int, int, int, int, int, int);
void __cdecl io_FormatTextBuffer(char*, int, int);
void __cdecl fcn_00545d40(int, int, char*, int, int, char*);

extern char g_7f4ca0[];
extern int g_775320;
extern int g_775324;
extern int g_775328;
extern unsigned short g_77532c;
extern int g_775330;
extern unsigned char g_773d75;

/* Ages the transient scene objects of one 32-slot block of the object table:
 * each stamped object counts down, and expired ones are released with their
 * effect and sound. */

/* ADDRESS: GOLDTL 0x005c6310 */
void __cdecl fcn_005c6310(void)
{
	char text[0x400];
	unsigned short* item;
	char* rec;
	int off;
	int n;
	int stamp;
	int left;
	int obj;

	if (g_774970 >= 0x300) {
		return;
	}
	fcn_00500d20((void*) 0x775320, &gm_GameTime);
	n = g_775330;
	off = n * 0x21c;
	for (; n < g_775330 + 0x20; n++) {
		if (off >= 0x65400) {
			break;
		}
		if (*(unsigned short*) (g_7f4ca0 + off) != 0xffff) {
			item = fcn_00502cd0(*(int*) (g_7f4ca0 + 376 + off), 1, 5);
			while (item != 0) {
				obj = fcn_005c61e0(*item);
				if (obj != 0) {
					if (*(int*) (obj + 4) > 0) {
						rec = (char*) item;
						if (*(int*) (rec + 0x21) != 0) {
							stamp = fcn_00500d20(rec + 0x2d, &gm_GameTime);
							left = *(int*) (rec + 0x1c) - stamp;
							*(int*) (rec + 0x1c) = left;
							*(pos14_7f4c00*) (rec + 0x2d) = gm_GameTime;
							if (left < 0) {
								*(int*) (rec + 0x21) = 0;
								if (*(char*) (g_7f4ca0 + 2 + off) == 6) {
									io_FormatTextBuffer(text, 0x1bc9, *item * 2 + 0x9a8);
									fcn_00545d40(*(int*) (g_7f4ca0 + 4 + off),
										-1, text, 0, 0x5ec, (char*) 0x6ac758);
								}
								if (*item == 0x178) {
									obj = gm_StartFilteredEntitySearch(1, 1, *(int*) (rec + 0x25));
									if (obj != 0) {
										fcn_004c5420(*(int*) (obj + 1), 0x5a, 2, 0, 0x20);
									}
								}
								obj = fcn_0047dca0(g_7f4ca0 + off);
								if (obj != 0 && *(char*) (g_7f4ca0 + 2 + off) != 7) {
									fcn_004c51f0(-1, *(int*) (rec + 6), *item, 1,
										g_773d75, 0);
								}
							}
						}
					} else if (*(int*) ((char*) item + 0x21) != 0) {
						*(int*) ((char*) item + 0x21) = 0;
					}
				}
				item = gm_NextEntityQueryMatch();
			}
		}
		off += 0x21c;
	}
	g_775320 = gm_GameTime.a;
	g_775324 = gm_GameTime.b;
	g_775328 = gm_GameTime.c;
	g_77532c = gm_GameTime.d;
	g_775330 = (n + 1) % 0x300;
}
