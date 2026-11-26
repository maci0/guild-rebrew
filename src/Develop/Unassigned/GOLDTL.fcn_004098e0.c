/* Plays the surface walking sound for the current path step: picks the
 * material name from the step type and remembers the step type on the object. */

#include <string.h>

extern int g_6b5c2c;
extern int g_67530c;
extern int g_6b5c30;

/* Surface name pools referenced by the reference body. */
extern char s_675ae8[]; /* "Pfuetze_s" */
extern char s_675af4[]; /* "Stein_s" */
extern char s_675afc[]; /* "Wiese_s" */
extern char s_675b04[]; /* "Erde_s" */
extern char s_675b0c[]; /* "Normal_s" */
extern char s_6752a8[]; /* "normal_s" */

int __cdecl d3_GetContextIndex(int);
char* __cdecl fcn_00422460(int, int);
void __cdecl d3snd_PlayObjectSound(char*, void*, unsigned char, float);

/* ADDRESS: GOLDTL 0x004098e0 */
void __cdecl ch_PlayFootstepSound(char* obj, int surface)
{
	char name[0x80];
	char* e;
	int stepType;
	char* r;

	e = *(char**) (obj + 0x14);
	if (*(int*) (e + 0x70) == 0) {
		return;
	}
	if (g_6b5c2c == 0) {
		return;
	}
	if (*(int*) 0x67a370 != *(int*) (e + 0x88)) {
		return;
	}
	if (g_67530c != *(int*) (e + 0x2c)) {
		return;
	}
	stepType = **(int**) (e + 0x70);
	if (stepType == *(unsigned char*) (obj + 0x100)) {
		return;
	}
	if (stepType != 4 && stepType != 0xc && stepType != 0x12 && stepType != 0x18) {
		return;
	}
	if ((*(unsigned char*) (e + 4) & 1) && g_6b5c30 < 3
	    && d3_GetContextIndex(*(int*) (e + 0x88)) != 0) {
		if (*(int*) (*(int*) (e + 0x88) + 0xac) != 0) {
			memcpy(name, s_675b0c, 9);
			if (surface == 6 || surface == 0xb) {
				memcpy(name, s_675af4, 8);
			} else if (surface == 3) {
				memcpy(name, s_675b04, 7);
			} else if (surface == 4) {
				memcpy(name, s_675afc, 8);
			} else if (surface == 8) {
				memcpy(name, s_675af4, 8);
			} else if (surface == 0xa) {
				memcpy(name, s_675ae8, 10);
			}
			r = fcn_00422460(g_6b5c2c, (int) name);
		} else {
			r = fcn_00422460(g_6b5c2c, (int) s_6752a8);
		}
		if (r != 0) {
			d3snd_PlayObjectSound(r, *(void**) (e + 0x34), 0x28, 500.0f);
			g_6b5c30++;
		}
	}
	*(unsigned char*) (obj + 0x100) = *(unsigned char*) *(int**) (e + 0x70);
}
