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

extern int g_775320;
extern int g_775324;
extern int g_775328;
extern int g_77532c;
extern int g_775330;
extern int g_7f4c00;
extern int g_7f4c04;
extern int g_7f4c08;
extern int g_7f4c0c;
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
	int base;
	int off;
	int n;
	int stamp;
	int left;
	int obj;

	if (*(unsigned short*) 0x774970 >= 0x300) {
		return;
	}
	fcn_00500d20((void*) 0x775320, (void*) 0x7f4c00);
	base = g_775330;
	off = base * 0x21c;
	for (n = base; n < base + 0x20; n++) {
		if (off >= 0x65400) {
			break;
		}
		if (*(short*) ((char*) 0x7f4ca0 + off) != -1) {
			g_775330 = base;
			item = fcn_00502cd0(*(int*) ((char*) 0x7f4e18 + off), 1, 5);
			while (item != 0) {
				obj = fcn_005c61e0(*item);
				if (obj != 0) {
					if (*(int*) (obj + 4) >= 1) {
						rec = (char*) item;
						if (*(int*) (rec + 0x21) != 0) {
							stamp = fcn_00500d20(rec + 0x2d, (void*) 0x7f4c00);
							left = *(int*) (rec + 0x1c);
							*(int*) (rec + 0x1c) = left - stamp;
							*(int*) (rec + 0x2d) = g_7f4c00;
							*(int*) (rec + 0x31) = g_7f4c04;
							*(int*) (rec + 0x35) = g_7f4c08;
							*(unsigned short*) (rec + 0x39) = (unsigned short) g_7f4c0c;
							if (left - stamp <= -1) {
								*(int*) (rec + 0x21) = 0;
								if (*(char*) ((char*) 0x7f4ca2 + off) == 6) {
									io_FormatTextBuffer(text, 0x1bc9, *item * 2 + 0x9a8);
									fcn_00545d40(*(int*) ((char*) 0x7f4ca4 + off),
										-1, text, 0, 0x5ec, (char*) 0x6ac758);
								}
								if (*item == 0x178) {
									obj = gm_StartFilteredEntitySearch(1, 1, *(int*) (rec + 0x25));
									if (obj != 0) {
										fcn_004c5420(*(int*) (obj + 1), 0x5a, 2, 0, 0x20);
									}
								}
								obj = fcn_0047dca0((char*) 0x7f4ca0 + off);
								if (obj != 0 && *(char*) ((char*) 0x7f4ca2 + off) != 7) {
									fcn_004c51f0(-1, *(int*) (rec + 6), *item, 1,
										((obj >> 8) & 0xffffff) | (g_773d75 << 24), 0);
								}
							}
						}
					} else if (*(int*) ((char*) item + 0x21) != 0) {
						*(int*) ((char*) item + 0x21) = 0;
					}
				}
				item = gm_NextEntityQueryMatch();
			}
			base = g_775330;
		}
		off += 0x21c;
	}
	g_775320 = g_7f4c00;
	g_775324 = g_7f4c04;
	g_775328 = g_7f4c08;
	g_77532c = g_7f4c0c;
	g_775330 = (n + 1) % 0x300;
}
