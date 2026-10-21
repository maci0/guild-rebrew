extern int g_68bfc0;
extern char* g_9afde4;
extern char* g_9afde0;
extern char g_772f5a;
extern char g_772f5b;
extern char g_772f5c;
extern char g_772f5d;
extern unsigned char g_772f58;
extern unsigned char g_772f59;
extern int g_772f44;
extern double g_664108;
extern double g_662a08;
extern double g_664180;
extern double g_6640e8;
extern float g_662a6c;

void __cdecl fcn_004727a0(int, int);
float __cdecl fcn_00507f10(char*, int);
int __cdecl fcn_005c6270(void*, int);
float __cdecl fcn_004e6d20(void);
int __cdecl fcn_004e6cb0(int);
void __cdecl fcn_004234e0(char*, char*, int, int, int, int, int);
int __cdecl fcn_004dfe40(char*, int);
void __cdecl fcn_00417b50(char*, int, float, float, float, float);
int __cdecl fcn_00406340(char*, char*, int);
int __cdecl fcn_004dff20(int);
char* __cdecl fcn_00519190(int, ...);
int __cdecl fcn_004c3030(int, int, char*, int);
float __cdecl fcn_004ff210(int, int);
void __cdecl fcn_004cfc40(char*, int, int);

/* ADDRESS: GOLDTL 0x004dff50 */
/* Resolves the shot of a duel action: the challenger's skill decides whether
 * the bullet hits, the victim takes damage and the matching gesture and log
 * message are played. */
void __cdecl fcn_004dff50(char* task)
{
	char* e;
	char* foe;
	float a;
	int n;
	int hit;

	fcn_004727a0(g_68bfc0, 0);
	e = *(char**) (task + 0x180);
	foe = *(char**) (task + 0x17c);
	a = fcn_00507f10(e, 3);
	fcn_00507f10(foe, 3);
	a = a * g_664108;
	if (fcn_005c6270(e, 0x16f) != 0) {
		a = a * g_662a08;
	}
	if ((e == g_9afde4 && g_772f5b) || (e == g_9afde0 && g_772f5a)) {
		a = a * g_664180;
	}
	if (fcn_004e6d20() < a) {
		hit = 1;
	} else {
		hit = 0;
		n = 0;
	}
	if (hit) {
		if ((e == g_9afde4 && g_772f5d) || (e == g_9afde0 && g_772f5c)) {
			n = fcn_004e6cb0(0xf) + 5;
		} else {
			n = fcn_004e6cb0(0x1e) + 0xf;
		}
		if (fcn_005c6270(foe, 0x2b5) != 0) {
			n = (int) ((float) n * g_662a6c);
		}
		if (foe == g_9afde4) {
			g_772f58 = g_772f58 + n;
		} else {
			g_772f59 = g_772f59 + n;
		}
		fcn_004cfc40(foe, (int) (*(float*) (foe + 0x1c) * g_6640e8 * n), 0);
	}
	fcn_004234e0(0, (char*) 0x68cbf4, 1, 0x3f, 0x7f, 0, 0);
	if (fcn_004dfe40(foe, n) != 0) {
		g_772f44 = 1;
		return;
	}
	if (hit) {
		fcn_00417b50(*(char**) (*(char**) (foe + 0x184) + 0x34), 0x40, 0.25f, 0.1f, 0.14f, 55.0f);
		if (*(int*) (*(char**) (foe + 0x184) + 0x128) == 0) {
			fcn_00406340(*(char**) (foe + 0x184), (char*) 0x68cbe4, 1);
		}
		fcn_004727a0(g_68bfc0, 0);
		task = (char*) fcn_004dff20(6);
		fcn_00519190((int) task + 0x1102, *(unsigned short*) foe);
		fcn_004c3030(*(unsigned short*) foe, 0, (char*) 0x68cbb8, (int) task);
		{
			float x;
			float y;

			y = *(float*) (foe + 0x1c) * g_6640e8 * n;
			x = (float) *(int*) (foe + 0x24) - y;
			*(int*) (foe + 0x24) = (int) x;
			fcn_004ff210(*(unsigned short*) foe, (int) -x);
		}
	} else {
		if (*(int*) (*(char**) (foe + 0x184) + 0x128) == 0) {
			fcn_00406340(*(char**) (foe + 0x184), (char*) 0x68cba0, 1);
		}
		task = (char*) fcn_004dff20(9);
		fcn_00519190((int) task + 0x1109, *(unsigned short*) foe);
		fcn_004c3030(*(unsigned short*) foe, 0, (char*) 0x68cb74, (int) task);
	}
}
