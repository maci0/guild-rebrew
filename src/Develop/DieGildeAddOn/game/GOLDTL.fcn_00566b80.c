extern char g_7f4ca0[];
extern unsigned char g_773d75;

unsigned short* __cdecl gm_StartFilteredEntitySearch(int, ...);
int __cdecl fcn_0050b750(int a, unsigned char k);
void __cdecl fcn_004c54c0(int a1, int a2, int a3, int a4);
void __cdecl io_FormatTextBuffer(char* buf, int text, ...);
void __cdecl fcn_00546190(char* u);
int __cdecl he_MessageBoxQuickjump(int id, int arg, char* text1, unsigned char flags, int value, int x, int y, char* name, char* text2);

/* ADDRESS: GOLDTL 0x00566b80 */
void __cdecl fcn_00566b80(char* obj)
{
	char buf[0x100];
	char* e;
	int n;
	int step;
	int i;
	int v;
	int id;

	v = *(int*) (obj + 0x70);
	if (v < -2) {
		return;
	}
	if (v >= 0) {
		if (v != 0) {
			return;
		}
		e = (char*) gm_StartFilteredEntitySearch(1, 1, *(int*) (obj + 0x10));
		if (e != 0) {
			n = fcn_0050b750(1000, g_773d75);
			step = (*(int*) (obj + 0xac) / n) * 0x14;
			for (i = 0; i < 768; i++) {
				if (*(unsigned short*) (g_7f4ca0 + i * 0x21c) != 0xffff && *(char**) (g_7f4ca0 + i * 0x21c + 0x16c) == e) {
					id = *(int*) (g_7f4ca0 + (unsigned int) *(unsigned short*) (obj + 8) * 0x21c + 4);
					fcn_004c54c0(id, *(int*) (g_7f4ca0 + i * 0x21c + 4), step, 0);
				}
			}
			if (*(unsigned char*) (g_7f4ca0 + (unsigned int) *(unsigned short*) (obj + 8) * 0x21c + 2) == 6
			    || *(unsigned char*) (g_7f4ca0 + (unsigned int) *(unsigned short*) (obj + 8) * 0x21c + 2) == 7) {
				io_FormatTextBuffer(buf, 0x19ab, e);
				id = *(int*) (g_7f4ca0 + (unsigned int) *(unsigned short*) (obj + 8) * 0x21c + 4);
				he_MessageBoxQuickjump(id, id, buf, 0, 0x5ec, *(int*) (e + 1), -1, 0, 0);
			}
		}
	}
	fcn_00546190(obj);
}
