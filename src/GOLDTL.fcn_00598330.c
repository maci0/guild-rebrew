#include <string.h>

/* 32 object pointers plus a count. Native clear is 132 bytes. */
typedef struct LC_OBJECT_LIST {
	char* objects[32];
	int count;
} LC_OBJECT_LIST;

extern int g_67a370;
extern int g_776664;

#ifdef REBREW_GOLD
char __cdecl fcn_0058fa00(char*, void*);
char __cdecl fcn_00438d40(char*, char*, unsigned int, char (__cdecl*)(char*, void*), void*);
#define lc_Collect fcn_0058fa00
#define lc_WalkScene fcn_00438d40
#else
char __cdecl fcn_005982d0(char*, void*);
char __cdecl fcn_004379a0(char*, char*, unsigned int, char (__cdecl*)(char*, void*), void*);
#define lc_Collect fcn_005982d0
#define lc_WalkScene fcn_004379a0
#endif
/* 0x442d50 / Gold 0x447300 keeps a numeric object context. */
char __cdecl fcn_00442d50(int, unsigned char);

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
			fcn_00442d50((int) object, 1);
		}
		else {
			fcn_00442d50((int) object, 0);
		}
	}
}
