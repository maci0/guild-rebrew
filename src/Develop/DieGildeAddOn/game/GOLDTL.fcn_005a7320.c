


extern char* g_7746c4;
extern int g_774650;
extern int g_774658;
extern int g_774654;
#include "Develop/Units/d3/d3_camera.h"
extern int g_774688;
extern int g_77468c;
extern int g_7747c8;
extern float g_7e3a40[3];
extern float g_7e3a50[3];
extern char g_6a30d4[];

short* __cdecl fcn_00502cd0(int, int, int, int);
short* __cdecl gm_NextEntityQueryMatch(void);
void __cdecl fcn_00438b40(char*, char*);
void __cdecl fcn_00438cb0(char*, char*);
void __cdecl fcn_004234e0(int, char*, int, int, int, int, int);

void __cdecl fcn_005a7320(int n, short v)
{
	short* r;
	int i;

	if (n != -1) {
		r = fcn_00502cd0(*(int*) (g_7746c4 + 0x5d), 1, 4, 2);
		if (r == 0) {
			return;
		}
		for (i = 1; i < n; i++) {
			r = gm_NextEntityQueryMatch();
			if (r == 0) {
				return;
			}
		}
		*(short*) (g_7746c4 + 0x29) = *r;
	}
	else {
		*(short*) (g_7746c4 + 0x29) = v;
	}
	g_774654 = g_774650 - g_774658 + 1;
	fcn_00438b40(g_6b8014, ((char*)g_7e3a40));
	fcn_00438cb0(g_6b8014, ((char*)g_7e3a50));
	g_774688 = 0;
	g_77468c = 0;
	fcn_004234e0(g_7747c8, g_6a30d4, 1, 0x3f, 0x7f, 0, 0);
}
