#include <string.h>
#include "client_placement.h"

extern int g_67a370;
extern int g_776664;

#ifdef REBREW_GOLD
char __cdecl d3_VisitSceneObjectsUntilStopped(char*, char*, unsigned int, char (__cdecl*)(char*, void*), void*);
#define lc_Collect fcn_0058fa00
#define lc_WalkScene d3_VisitSceneObjectsUntilStopped
#else
char __cdecl d3_VisitSceneObjects(char*, char*, unsigned int, char (__cdecl*)(char*, void*), void*);
#define lc_Collect fcn_005982d0
#define lc_WalkScene d3_VisitSceneObjects
#endif
/* 0x442d50 / Gold 0x447300 keeps a numeric object context. */
char __cdecl d3_SetSubtreeVisible(int, unsigned char);

void __cdecl fcn_00598330(char* node, int flag)
{
	LC_OBJECT_LIST list;
	int i;
	char* object;

	memset(&list, 0, sizeof(list));
	lc_WalkScene((char*) g_67a370, node, 0x2c0, lc_Collect, &list);
	for (i = 0; i < list.count; i++) {
		object = list.objects[i];
		if (flag != 0 && (i < (g_776664 & 0xff) || (char) g_776664 == 2)) {
			d3_SetSubtreeVisible((int) object, 1);
		}
		else {
			d3_SetSubtreeVisible((int) object, 0);
		}
	}
}
