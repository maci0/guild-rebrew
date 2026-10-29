#include <string.h>

char* __cdecl fcn_00445600(char*, int, char*, char*);
void __cdecl fcn_00442d50(void*, int);
int __cdecl fcn_0051e070(void);
void __cdecl fcn_005338a0(void);
int __cdecl fcn_005373e0(int, int);
char* __cdecl fcn_005338d0(char*, int, int);
void __cdecl fcn_00597ec0(char*);
void __cdecl fcn_005ba8e0(char*);
void __cdecl fcn_005be140(char*, int);
void __cdecl fcn_005cf560(char*);
void __cdecl fcn_005a3680(void);

extern int g_7746d8;
extern char* g_7746a0;
extern int g_14ad100;
extern int g_14ad0f0;
extern int g_14a7d28;
extern int g_14abb60;

/* Object server loop: probes the two card-table object names, picks the
 * localized name, then pumps the frame delay and dispatches the active dialog. */

/* ADDRESS: GOLDTL 0x005a3820 */
void __cdecl fcn_005a3820(char* app)
{
	char name[0x18];
	char* obj;
	char* active;
	char* first;
	char* second;
	char* third;
	char* fourth;
	int idle;

	idle = 0;
	obj = fcn_00445600(0, 0xc0, 0, (char*) 0x6aaa48);
	if (obj != 0) {
		fcn_00442d50(obj, 0);
	}
	obj = fcn_00445600(0, 0xc0, 0, (char*) 0x6aaa38);
	if (obj != 0) {
		fcn_00442d50(obj, 0);
	}

	if (fcn_0051e070() == 0) {
		memcpy(name, (void*) 0x6aaa48, 0x14);
		obj = fcn_00445600(0, 0xc0, 0, (char*) 0x6aaa48);
		if (obj == 0) {
			obj = fcn_00445600(0, 0xc0, 0, (char*) 0x6aaa38);
			if (obj == 0) {
				goto ready;
			}
		}
		fcn_00442d50(obj, 1);
	} else {
		*(int*) (name + 0x00) = *(int*) 0x6aaa38;
		*(int*) (name + 0x04) = *(int*) 0x6aaa3c;
		*(int*) (name + 0x08) = *(int*) 0x6aaa40;
		*(unsigned short*) (name + 0x0c) = *(unsigned short*) 0x6aaa44;
		name[0x0e] = *(char*) 0x6aaa46;
		obj = fcn_00445600(0, 0xc0, 0, (char*) 0x6aaa38);
		if (obj != 0) {
			fcn_00442d50(obj, 1);
		}
	}

ready:
	fcn_005338a0();
	if (fcn_005373e0(0x5a3820, 0x67fff) == 0) {
		return;
	}
	first = 0;
	second = 0;
	third = 0;
	fourth = 0;
	for (;;) {
		fcn_00597ec0(app);
		if ((g_7746d8 & 0x200) != 0) {
			first = fcn_005338d0((char*) 0x6a956c, g_14ad100, 0x15);
			second = fcn_005338d0((char*) 0x6a9580, g_14ad0f0, 0xe);
			third = fcn_005338d0((char*) 0x6a9924, g_14a7d28, 0x16);
			fourth = fcn_005338d0(name, g_14abb60, 0x16);
		}
		active = g_7746a0;
		if (active != 0) {
			if (active == first) {
				fcn_005ba8e0(app);
				active = g_7746a0;
			}
			if (active == second) {
				fcn_005be140(app, *(int*) (app + 0x5d));
			} else if (active == third) {
				fcn_005cf560(app);
			} else if (active == fourth) {
				*(int*) (fourth + 0x224) = 0;
				fcn_005a3680();
				*(int*) (fourth + 0x224) = 1;
			}
		}
		if (fcn_005373e0(0x5a3820, 0x67fff) == 0) {
			break;
		}
	}
}
