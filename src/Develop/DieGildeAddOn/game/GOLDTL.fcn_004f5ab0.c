extern char g_6b5c60[];
extern char g_7f4ca4[];


unsigned char* __cdecl fcn_00508e40(int);
void __cdecl fcn_0051af00(void*, int, ...);
void __cdecl fcn_00545d40(int, int, void*, int, int, void*);

void __cdecl fcn_004f5ab0(int a1, int a2, int a3)
{
	char buf[0x200];
	unsigned char* p;
	int i;
	char* e;

	p = 0;
	for (i = 0x9a3816; i < 0x9a9216; i += 0x2d) {
		if (*(int*) (i - 0x16) == a1) {
			p = fcn_00508e40(*(int*) i);
			if (p != 0) {
				fcn_0051af00(buf, 0x1747, *(unsigned short*) p);
			}
		}
	}
	if (p == 0) {
		return;
	}
	for (e = g_7f4ca4; (int) e < (int) (g_7f4ca4 + 0x65400); e += 0x21c) {
		if ((*(char*) (e - 2) == 6 || *(char*) (e - 2) == 7)
		    && *(int*) e != a2
		    && (*(int*) (e + 0x1e4) & a3) == 0) {
			for (i = 0; i < 0x800; i++) {
				if (*(int*) (0x99f800 + i * 8) == *(int*) e
				    && *(int*) (0x99f804 + i * 8) == a1) {
					fcn_00545d40(*(int*) e, -1, buf, 0, 0x5ec, g_6b5c60);
					*(int*) (0x7f4e88 + i * 540) &= a3;
					break;
				}
			}
		}
	}
}
