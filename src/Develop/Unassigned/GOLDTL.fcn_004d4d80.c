extern int g_772ec4;
extern unsigned short* g_772f24;
extern int g_68b79c;
extern int g_aed32c;

char* __cdecl fcn_004ce610(char*);
void __cdecl fcn_004cf110(char*);
void __cdecl fcn_004234e0(int, char*, int, int, int, int, int);
unsigned short* __cdecl fcn_004ce680(char*);
void __cdecl fcn_004c4510(char*, int);
void __cdecl fcn_004c4670(int, int, int, int*);
void __cdecl fcn_004c5360(void);

/* ADDRESS: GOLDTL 0x004d4d80 */
void __cdecl fcn_004d4d80(char* a0)
{
	char* obj;
	char* rec;
	char* e;
	int v;

	obj = *(char**) (a0 + 0x180);
	rec = fcn_004ce610(obj);
	fcn_004cf110((char*) (*(int*) (*(int*) (obj + 0x184) + 0x34) + 0x4c));
	fcn_004234e0(g_772ec4, (char*) 0x68be64, 3, 0x3f, 0x7f, 0, 0);
	if (*(int*) ((char*) g_772f24 + 4) == g_68b79c) {
		if (*(int*) (rec + 0x58) == 1 || *(int*) (rec + 0x58) == 2) {
			e = (char*) fcn_004ce680(obj);
			if (e != 0) {
				v = -1;
				fcn_004c4510(e, *(int*) (e + 2));
				fcn_004c4670(4, 1, (int) e - g_aed32c + 0x20, &v);
				fcn_004c5360();
			}
		}
	}
}
