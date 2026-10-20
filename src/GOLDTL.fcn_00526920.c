#include <string.h>

extern int g_7e2700;
extern int g_7e46ac;
extern char* g_7e2704;
extern char* g_7e2708;
extern char g_7e2714[];
extern char* g_868050;
extern unsigned short g_774970;
extern char* g_7746c4;
extern char* g_7746c8;
extern char* g_7746cc;
extern int g_774650;
extern int g_774654;
extern int g_774658;
extern int g_774670;
extern char g_7f4e51[];
extern char g_7f4ca4[];
extern char g_1043690[];

char* __cdecl fcn_00502cd0(int a0, int a1, int a2, int a3);
int __cdecl gm_CheckEntityType(void* p);
int __cdecl fcn_00505340(void* p);
int __cdecl fcn_00515540(void* p);
void __cdecl init_LoadObjektScene(unsigned short id);
void __cdecl fcn_005356b0(void* p);

/* ADDRESS: GOLDTL 0x00526920 */
void __cdecl fcn_00526920(char* a0, int a1, char* a2)
{
	char* cur;
	char* hit;
	char* old;
	char* saved_ptr;
	int saved;
	int id;
	int type;
	int n;

	if (g_7e2700 != 0) {
		return;
	}
	if ((g_7e46ac & 0x10000) != 0) {
		return;
	}
	hit = 0;
	id = (int) g_774970;
	if (g_774970 != 0xffff && g_7f4e51[id * 540] != 0) {
		type = (int) *(g_868050 + ((unsigned char) *a0) * 589);
		if (type == 6) {
			goto ready;
		}
		if (type != 4) {
			return;
		}
		if (*(int*) (a0 + 0x65) != *(int*) (g_7f4ca4 + id * 540)) {
			return;
		}
	}
ready:
	if (g_7746c4 != 0) {
		hit = g_7746c4;
	} else if (g_7746c8 != 0) {
		hit = g_7746c8;
	}
	g_7e2704 = a0;
	g_7e2708 = fcn_00502cd0(*(int*) (a0 + 0x5d), 1, 1, a1);
	if (*a0 == 0x47) {
		g_7e2708 = fcn_00502cd0(*(int*) (a0 + 0x5d), 1, 0, 0xfd);
	}
	strcpy(g_7e2714, a2);
	g_7e2700 = 1;
	cur = g_7e2708;
	if (cur == 0 || *(unsigned short*) cur == 0) {
		if (a0 == hit && g_7746c8 == 0) {
			g_7e2700 = 0;
			return;
		}
		fcn_005356b0((void*) 0x59a340);
		return;
	}
	if (cur == g_7746cc) {
		if (g_774650 > g_774658) {
			g_774654 = g_774650 - g_774658;
			return;
		}
		g_7e2700 = 0;
		return;
	}
	if (a0 == hit) {
		if (gm_CheckEntityType(hit) != 0) {
			*(unsigned short*) (a0 + 0x29) = *(unsigned short*) g_7e2708;
			if (g_7746cc != 0) {
				g_774654 = g_774650 + 1 - g_774658;
				return;
			}
			g_774654 = g_774650 - g_774658;
			return;
		}
	}
	*(unsigned short*) (a0 + 0x29) = *(unsigned short*) g_7e2708;
	old = g_7746cc;
	saved = g_774670;
	if (gm_CheckEntityType(a0) == 0 && fcn_00505340(a0) == 0) {
		cur = g_7e2708;
		g_7746cc = cur;
		g_7e2700 = 0;
		g_774670 = 0;
		n = fcn_00515540(cur);
		if (g_1043690[n * 988 + 5] != 0) {
			init_LoadObjektScene(*(unsigned short*) g_7e2708);
		}
		g_7746cc = old;
		g_7e2700 = 1;
		g_774670 = saved;
	}
	fcn_005356b0((void*) 0x59a340);
}
