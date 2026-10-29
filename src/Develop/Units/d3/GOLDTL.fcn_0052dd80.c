#include "Develop/Units/d3/d3_object.h"
extern int g_67a370;
extern int g_773dd8;

// SIZE 0x84
struct list_52dd80 {
	int n;
	char* a[32];
};



#include <string.h>

void __cdecl fcn_004379a0(int, char*, int, void*, struct list_52dd80*);
char __cdecl fcn_0052dd40(char*, struct list_52dd80*);
void __cdecl fcn_004550b0(char*, int);


#ifdef REBREW_GOLD
#define OBJ_SND_STATE_OFF 0x1f0
#define OBJ_SND_FLAG_OFF 0x210
#else
#define OBJ_SND_STATE_OFF 0x1f4
#define OBJ_SND_FLAG_OFF 0x214
#endif

/* ADDRESS: GOLD 0x005286e0 */
void __cdecl fcn_0052dd80(char* e)
{
	struct list_52dd80 l;
	char* o;
	int saved;
	int i;

	o = *(char**) (e + 0x61);
	if (o != 0) {
		memset(&l, 0, sizeof(l));
		if ((o[OBJ_SND_FLAG_OFF] & 1) == 0) {
			saved = *(int*) (o + OBJ_SND_STATE_OFF);
			*(int*) (o + OBJ_SND_STATE_OFF) = 0;
			fcn_004379a0(g_67a370, *(char**) (e + 0x61), 0x40, (void*) fcn_0052dd40, &l);
			*(int*) (*(char**) (e + 0x61) + OBJ_SND_STATE_OFF) = saved;
		} else {
			fcn_004379a0(g_67a370, o, 0x40, (void*) fcn_0052dd40, &l);
		}
		for (i = 0; i < l.n; i++) {
			if (g_773dd8 != 0) {
				fcn_004550b0(l.a[i], g_773dd8);
			}
			d3_DestroyObject((D3_OBJECT*) (l.a[i]));
		}
	}
}
