#include <string.h>

#include "client_types.h"

extern char g_7f4ca0[];
extern pos14_7f4c00 g_7f4c00;
extern unsigned short g_7f4c04;
extern char* g_entity_type_table;
extern float g_696540[];
extern float g_696550[];
extern char s_6a2e68[];
extern char s_6a2e70[];
extern char s_6a2e78[];

extern void __cdecl fcn_00529000(int, char*);
extern void __cdecl fcn_00529060(int, char*);
extern void __cdecl fcn_005290d0(char*);
extern int __cdecl fcn_005241f0(char*);
extern void __cdecl fcn_00546190(char*);
extern int __cdecl fcn_004c5620(char, char*);
extern void __cdecl fcn_004c4510(char*, int);
extern int __cdecl fcn_004c4700(unsigned char, unsigned char, short, void*);
extern void __cdecl fcn_004c53a0(void);
extern char* __cdecl fcn_0040c120(char*, int, ...);
extern int __cdecl fcn_00500e20(int*);
extern int __cdecl fcn_00515540(char*);
extern int __cdecl fcn_005155e0(unsigned char*);
extern void* __cdecl fcn_00426cc0(int);
extern void __cdecl fcn_00428720(char*);
extern int __cdecl fcn_005373e0(void);

/* SIZE 0x188 */
typedef struct {
	unsigned short id;	/* +0x00 */
	char pad02[2];
	int handle;		/* +0x04 */
	char pad08[0x164];
	char* active;		/* +0x16c */
	char pad170[0xc];
	char* shown;		/* +0x17c */
	char* owner;		/* +0x184 */
} Slot_529160;

/* SIZE 0x24d */
typedef struct {
	unsigned char type;	/* +0x00 */
	char pad1[0x27];
	int object;		/* +0x28 */
	char pad2c[0x5c];
	int field88;		/* +0x88 */
} Rec_529160;

/* ADDRESS: GOLDTL 0x00529160 */

/* Shows one entity of the scene slot and queues the matching action; the
 * object type selects one of two scene-hook paths, then the shown object is
 * replaced by a4. */
void __cdecl fcn_00529160(unsigned char* a1, char* a2, unsigned int index, unsigned char* a4)
{
	Slot_529160* slot;
	Rec_529160* rec;
	char* old;
	char* owner;
	char* r;
	void* o;
	int v7;
	int cls;
	int obj;
	unsigned int tick;
	unsigned char type;

	if ((int) index >= 0x300) {
		return;
	}
	slot = (Slot_529160*) (g_7f4ca0 + index * 0x21c);
	old = slot->shown;
	if (old == (char*) a4) {
		return;
	}
	if (a1 == 0) {
		a1 = (unsigned char*) slot->active;
	}
	owner = slot->owner;
	if (a2 != 0) {
		rec = (Rec_529160*) ((unsigned char*) g_entity_type_table + (unsigned int) *a1 * 0x24d);
		if (*(short*) a2 != 0xfd) {
			v7 = fcn_00515540(a2);
		} else {
			v7 = fcn_005155e0(a1);
		}
		cls = fcn_00500e20((int*) &g_7f4c00);
		tick = g_7f4c04 & 0xffff;
		if ((((float) (int) tick < g_696550[cls] && g_696540[cls] <= (float) (int) tick)
		     || rec->type == 4 || rec->type == 0x13 || rec->type == 0x1d)
		    && v7 >= 0 && owner != 0
		    && v7 * 0x3dc + 0x10432c0 != ((Rec_529160*) owner)->field88) {
			r = fcn_0040c120(owner, 0x33, v7, *(int*) (a1 + 1), *(int*) (a2 + 2));
			*(int*) (r + 0x70) = *(int*) (s_6a2e78 + 0);
			*(int*) (r + 0x74) = *(int*) (s_6a2e78 + 4);
			*(int*) (r + 0x78) = *(int*) (s_6a2e78 + 8);
			*(int*) (r + 0x7c) = *(int*) (s_6a2e78 + 0xc);
			*(short*) (r + 0x80) = *(short*) (s_6a2e78 + 0x10);
			r = fcn_0040c120(owner, 0x39, v7);
			*(int*) (r + 0x70) = *(int*) (s_6a2e78 + 0);
			*(int*) (r + 0x74) = *(int*) (s_6a2e78 + 4);
			*(int*) (r + 0x78) = *(int*) (s_6a2e78 + 8);
			*(int*) (r + 0x7c) = *(int*) (s_6a2e78 + 0xc);
			*(short*) (r + 0x80) = *(short*) (s_6a2e78 + 0x10);
			obj = ((Rec_529160*) owner)->object;
			if (obj != -1) {
				o = fcn_00426cc0(obj);
				if (o != 0) {
					fcn_00428720((char*) o);
				}
			}
		}
	}
	if (old != 0) {
		fcn_00529060(slot->id, old);
		switch (*old) {
		case 3:
		case 4:
		case 8:
		case 9:
			fcn_005290d0(old);
			break;
		case 20:
		case 21:
		case 140:
			if (owner != 0) {
				obj = ((Rec_529160*) owner)->object;
				if (obj != -1) {
					fcn_00428720((char*) fcn_00426cc0(obj));
				}
			}
			if (*(int*) (old + 0x70) < 3) {
				*(pos14_7f4c00*) (old + 0x52) = g_7f4c00;
				*(int*) (old + 0x70) = -1;
			}
			break;
		case 22:
		case 136:
		case 137:
		case 141:
		case 143:
			fcn_005290d0(old);
			if (fcn_005241f0(old) <= 0) {
				*(pos14_7f4c00*) (old + 0x52) = g_7f4c00;
				fcn_004c5620(-1, old);
			}
			break;
		case 40:
			if (fcn_005241f0(old) <= 0) {
				fcn_004c5620(-1, old);
			}
			break;
		case 72:
		case 73:
		case 117:
		case 161:
			fcn_00546190(old);
			break;
		}
	} else if (owner != 0 && ((Rec_529160*) owner)->object != -1) {
		obj = ((Rec_529160*) owner)->object;
		o = fcn_00426cc0(obj);
		if (o != 0 && (strstr((char*) o, s_6a2e70) != 0 || strstr((char*) o, s_6a2e68) != 0)) {
			fcn_00428720((char*) o);
		}
	}
	if (a4 != 0) {
		fcn_00529000(slot->id, (char*) a4);
		switch (*a4) {
		case 3:
		case 4:
		case 8:
		case 9:
		case 20:
		case 21:
		case 140:
			fcn_005290d0((char*) a4);
			break;
		}
		type = *a4;
	} else {
		type = 0;
	}
	if ((slot->shown != 0 || a4 != 0) && type == 0) {
		return;
	}
	fcn_004c4510((char*) slot, slot->handle);
	fcn_004c4700(1, 1, 0x180, &type);
	fcn_004c53a0();
	slot->shown = (char*) a4;
}
