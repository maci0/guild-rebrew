extern char* g_1015ea0;
extern int g_14ce8e0;
extern char g_14cf950;
extern float g_14ce880;
extern int g_67d370;
extern int g_6b5cbc;
extern int g_6b5cc0;
extern char* g_6b8014;
extern float g_7e3a40[3];
extern float g_7e3a50[3];
extern int* g_7e2a9c;
extern char* g_7e2aa0;
extern int g_7ea360;
extern unsigned char g_7f4e51[];
extern char* g_item_def_table;
extern unsigned short g_774970;
extern int g_774650;
extern int g_774654;
extern int g_774658;
extern int g_77465c;
extern int g_774688;
extern int g_77468c;
extern char* g_7746a8;
extern int g_7746b8;
extern char* g_7746c4;
extern unsigned char* g_7746c8;
extern char* g_7746cc;
extern int g_7746d4;
extern int g_7746d8;
extern int g_7746dc;
extern int g_7746f0;
extern char g_7746f4;
extern char* g_7747a0;
extern char* g_7747a4;
extern char* g_7747b8;
extern int g_7747c8;
extern unsigned char** g_7749e4;
extern char g_7749e8;

void __cdecl fcn_004116d0(void);
void __cdecl fcn_00411740(void);
void __cdecl fcn_00412830(unsigned char mask);
void __cdecl fcn_004234e0(char*, char*, int, int, int, int, int);
void __cdecl fcn_00433780(void*);
void __cdecl fcn_00438b40(char*, float*);
void __cdecl fcn_00438cb0(char*, float*);
int __cdecl fcn_00451840(float*, float*, float);
void __cdecl fcn_004bbd70(void);
int* __cdecl gm_SetupEntityQuery(char*);
int __cdecl fcn_00506380(int, void*, void*, int);
void __cdecl fcn_0052ae80(void);
void __cdecl fcn_0052d820(void);
void __cdecl fcn_0052f7b0(void);
void __cdecl fcn_00530510(void);
void __cdecl fcn_005338a0(void);
void __cdecl fcn_00545c50(int);
void __cdecl fcn_0057e0a0(void);
int __cdecl fcn_0057eba0(int, int, int, int);
void __cdecl fcn_00599f90(void);
void __cdecl fcn_005a7320(int, int);

/* ADDRESS: GOLDTL 0x00533090 */
void __cdecl fcn_00533090(unsigned int a0)
{
	char* p;
	char* q;
	char* e;
	char* d;
	char* v4;
	char* v5;
	int* ip;
	int i;
	int v2;

	d = 0;
	if (g_14ce8e0 && (*(int*) (g_774650 * 8 + 0x7e35c0) != 0x59a340 || g_7746f0
	    || g_7e2a9c || g_7ea360 || g_7e2aa0)) {
		fcn_004234e0(g_7747b8, "MausclickRechts_s_01", 1, 0x3f, 0x7f, 0, 0);
	}
	if (g_7749e4) {
		if (g_14ce8e0 == 0 && g_14cf950 != 0x1c) {
			return;
		}
		if (*g_7749e4 != 0) {
			if (**g_7749e4 == 0x11 || **g_7749e4 == 0x26 || **g_7749e4 == 0x69) {
				g_7749e8 = 1;
			} else if (**g_7749e4 == 0x87) {
				fcn_0057e0a0();
			} else {
				fcn_00545c50(0);
			}
		} else {
			fcn_00545c50(0);
		}
		fcn_00412830(0x10);
		if (g_14cf950 != 0x1c) {
			return;
		}
		g_14cf950 = 0;
		return;
	}
	if (g_14ce8e0 != 0 && g_67d370 != -1) {
		i = 0;
		ip = (int*) 0x77e8c4;
		do {
			if (*ip != -1 && (ip - 1) != 0
			    && g_67d370 == *(int*) (g_1015ea0 + *ip * 0x2f4)) {
				*(int*) (*(int*) (i * 0xc + 0x77e8c0) + 0x70) = -1;
				g_7749e8 = 0;
				fcn_004116d0();
				break;
			}
			ip += 3;
			i += 1;
		} while (ip < (int*) 0x77e984);
	}
	if (a0 & 0x800) {
		fcn_00599f90();
		fcn_004bbd70();
		if (g_14ce8e0 && g_7e2aa0
		    && *(int*) (g_774650 * 8 + 0x7e35c0) == 0x59a340) {
			fcn_00530510();
			goto done;
		}
		if (g_7746c4 != 0) {
			if (g_7746b8 && g_7746f0 == 0 && g_7746f4 == 0) {
				fcn_004234e0((char*) g_7747c8, "RaumWechseln_s", 1, 0x3f, 0x7f, 0, 0);
				*(unsigned short*) (g_7746c4 + 0x29) = *(unsigned short*) g_7746b8;
				g_774654 = (g_774650 - g_774658) + 1;
				fcn_00438b40(g_6b8014, g_7e3a40);
				fcn_00438cb0(g_6b8014, g_7e3a50);
				g_774688 = 0;
				g_77468c = 0;
			}
		} else if (g_7746c8 != 0 && g_7746cc != 0 && g_7746b8 != 0
		    && g_7746f0 == 0 && g_7746f4 == 0) {
			g_774654 = (g_774650 - g_774658) + 1;
			fcn_00438b40(g_6b8014, g_7e3a40);
			fcn_00438cb0(g_6b8014, g_7e3a50);
			g_774688 = 0;
			g_77468c = 0;
		}
		if (g_14ce8e0 && (g_7746f4 != 0 || (g_7e2a9c != 0
		    && g_item_def_table[*(unsigned short*) g_7e2a9c * 0x41] == 0x1d))) {
			fcn_00530510();
			fcn_00412830(0x10);
		}
		if ((g_7746c4 != 0
		    && fcn_0057eba0(0x1a, (int) g_7746c4, 0, *(unsigned short*) g_7746cc) == 0)
		    || (g_7746c8 != 0 && fcn_0057eba0(0x1c, (int) g_7746c8, 0, 0) == 0)) {
			fcn_00411740();
		}
		if (g_7746f0 || g_7746f4 || g_14ce8e0 == 0) {
			goto done;
		}
		v2 = 0;
		if (g_6b5cc0) {
			if (g_7746c4 == 0 && g_7746c8 == 0) {
				goto done;
			}
			if (fcn_00451840(&g_14ce880, g_7e3a40, 0.1f)) {
				fcn_00433780(g_6b8014);
				g_6b5cc0 = 0;
				g_6b5cbc = 0;
				v2 = 1;
				fcn_00438b40(g_6b8014, g_7e3a40);
				fcn_00438cb0(g_6b8014, g_7e3a50);
			} else {
				fcn_00433780(g_6b8014);
				g_6b5cc0 = 0;
				g_6b5cbc = 0;
			}
		}
		if (g_774650 <= g_774658 || v2) {
			if (fcn_00451840((float*) (g_6b8014 + 0x84), g_7e3a50, 0.1f)
			    || fcn_00451840((float*) (g_6b8014 + 0x4c), g_7e3a40, 0.1f) || v2) {
				if (g_7746c4 == 0 && g_7746c8 == 0 && g_7746cc == 0) {
					if (g_774650 == g_774658 && g_7e2a9c) {
						fcn_00530510();
					}
					goto done;
				}
				v5 = 0;
				if (g_7746cc != 0) {
					if (g_7746c4 != 0) {
						i = fcn_0057eba0(0x1a, (int) g_7746c4, 0,
						    *(unsigned short*) g_7746cc);
						if (i == 1 && g_7f4e51[g_774970 * 0x21c] == 0
						    && *(unsigned short*) g_7746cc == 0xf2) {
							v5 = (char*) gm_SetupEntityQuery(g_7746c4);
						}
					} else if (g_7746c8 != 0) {
						i = fcn_0057eba0(0x1c, (int) g_7746c8, 0, 0);
						if (i == 1 && g_7f4e51[g_774970 * 0x21c] == 0
						    && *(unsigned short*) g_7746cc == 0xf2) {
							v5 = (char*) gm_SetupEntityQuery(g_7746c8);
						}
					}
					if (g_7746c4 != 0 && v5 != 0 && v5 != g_7746cc) {
						fcn_005a7320(-1, (int) *(unsigned short*) v5);
					} else {
						g_7746cc = 0;
					}
				} else if (g_7746c8 != 0 || g_7746c4 != 0) {
					g_7746c8 = 0;
					g_7746c4 = 0;
					g_7746cc = 0;
				} else {
					g_7746cc = 0;
				}
				g_774654 = 1;
				if (g_7746c4 != 0 && g_7746cc == 0) {
					g_7746c4 = 0;
				}
				fcn_00438b40(g_6b8014, g_7e3a40);
				fcn_00438cb0(g_6b8014, g_7e3a50);
				g_774688 = 0;
				g_77468c = 0;
				goto done;
			}
			if (g_7746c4 != 0 || g_7746c8 != 0) {
				fcn_0052d820();
			}
		} else {
			g_774654 = 1;
			if (g_77465c < g_774650 - 1) {
				goto done;
			}
			if (g_7746c4 != 0 || g_7746c8 != 0) {
				fcn_0052d820();
			}
			g_77465c = g_774650 - g_774654;
		}
		if (g_7746a8 != 0) {
			e = *(char**) (g_7746a8 + 0x1d4);
			if (e != 0 && *(int*) (e + 0x18c) != 0) {
				(*(void (__cdecl**) (char*, int, char*, int)) (e + 0x18c))
				    (g_7746a8, 3, e + 400, 0);
			}
			g_7746a8 = 0;
		}
		fcn_00530510();
	}
done:
	if (a0 & 0x100) {
		fcn_0052f7b0();
	}
	v4 = g_7746c4;
	if (v4 == 0) {
		v4 = g_7746c8;
		if (v4 == 0) {
			v4 = d;
		}
	}
	if ((a0 & 8) && v4 != 0) {
		if (g_7746cc != 0) {
			v5 = g_7746cc;
		} else {
			v5 = 0;
		}
		g_7746dc = fcn_00506380(g_774970, v4, v5, 0);
		if (*(unsigned short*) (v4 + 0x27) == g_774970 || (g_7746dc & 0x1000)) {
			fcn_0052ae80();
		}
	}
	if (g_7747a0 == v4 && g_7747a4 == g_7746cc && g_7746d4 == 0) {
		return;
	}
	g_7746d8 = fcn_00506380(g_774970, v4, g_7746cc, 0);
	fcn_005338a0();
	g_7746d4 = 0;
	g_7747a0 = v4;
	g_7747a4 = g_7746cc;
}
