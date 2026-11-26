extern int g_6b25b0;
extern int g_6b23a4;
#include <stdio.h>
#include <string.h>
#include "Develop/DieGildeAddOn/game/game_data.h"

void __cdecl d3_VisitSceneObjects(int, int, int, int, void*);
void __cdecl d3_SetSubtreeVisible(int, int);
void __cdecl d3_SelectSceneContext(int, int);
int __cdecl fcn_00445600(int, int, int, char*);
void __cdecl fcn_004550b0(int, int);
void __cdecl d3_DestroyObject(int);
int __cdecl gm_SearchTable67(int);
void __cdecl d3_CollectObjectCallback(void);
int __cdecl fcn_0064d41a(char*, const char*, ...);
char* __cdecl fcn_0064d1a0(char*, int);
char* __cdecl fcn_0064d530(char*, const char*, unsigned int);
int __cdecl atoi(char*);
int __cdecl _isctype(int, int);

typedef struct ObjList {
	int handle;
	void* items[64];
	int count;
} ObjList;

/* Collects the scene objects matching the "he_<id>" name, forces them into
 * state 5 and clears their pending flag, or selects the object whose
 * underscore-separated numeric range contains the requested value. */
/* ADDRESS: GOLDTL 0x00573e10 */
void __cdecl fcn_00573e10(int action)
{
	ObjList list;
	char name[256];
	char buf[128];
	int range[4];
	unsigned char digits[4];
	unsigned char leader;
	int saved;
	int obj;
	int cur;
	int idx;
	int num;
	int slot;
	int flag;
	char* p;

	saved = d3_CurrentContextIndex;
	d3_SelectSceneContext(0, 1);
	fcn_0064d41a(name, "he_%i", *(int*) (action + 4));
	obj = fcn_00445600(0, 0x1c0, 0, name);
	cur = *(int*) (action + 0xc8);
	if (cur == -1 && obj != 0) {
		list.handle = obj;
		list.count = 0;
		d3_VisitSceneObjects(g_67a370, obj, 0x2c0, (int) d3_CollectObjectCallback,
		             &list);
		idx = 0;
		while (idx < list.count) {
			slot = (int) list.items[idx];
			if (*(int*) (slot + 0x220) == 5
			    && !(*(unsigned char*) (slot + 0x217) & 1))
				goto next_mark;
			*(int*) (slot + 0x220) = 5;
			slot = (int) list.items[idx];
			if ((*(unsigned char*) (slot + 0x217) & 1)
			    && g_773dd8 != 0)
				fcn_004550b0(slot, g_773dd8);
			slot = (int) list.items[idx];
			*(unsigned char*) (slot + 0x217) &= 0xfe;
next_mark:
			idx++;
		}
		d3_SetSubtreeVisible(obj, 0);
		goto done;
	}
	if (cur >= *(int*) (action + 0xc4) || obj == 0) {
		if (cur > *(int*) (action + 0xc4))
			goto release;
		goto done;
	}
	list.handle = obj;
	list.count = 0;
	d3_VisitSceneObjects(g_67a370, obj, 0x2c0, (int) d3_CollectObjectCallback, &list);
	idx = 0;
	while (idx < list.count) {
		int item;

		item = (int) list.items[idx];
		if (*(int*) (item + 0x220) != 5
		    || (*(unsigned char*) (item + 0x217) & 1)) {
			if ((*(unsigned char*) (item + 0x217) & 1)
			    && g_773dd8 != 0)
				fcn_004550b0(item, g_773dd8);
			item = (int) list.items[idx];
			*(int*) (item + 0x220) = 5;
			item = (int) list.items[idx];
			*(unsigned char*) (item + 0x217) &= 0xfe;
		}
		item = (int) list.items[idx];
		num = 0;
		*(int*) (item + 0x224) = 0;
		item = (int) list.items[idx];
		{
			char* src;
			char* dst;

			src = (char*) item;
			dst = buf;
			while ((*dst++ = *src++) != 0)
				;
		}
		p = fcn_0064d1a0(buf, '_');
		if (p != 0) {

			do {
				if (num >= 2)
					break;
				fcn_0064d530((char*) digits, p + 1, 2);
				digits[2] = 0;
				leader = 0;
				if (g_6b25b0 > 1)
					flag = _isctype((signed char) digits[0], 4);
				else
					flag = *(unsigned char*)
					    ((unsigned char*) g_6b23a4
					     + (signed char) digits[0] * 2) & 4;
				if (flag)
					range[num++] = atoi((char*) digits);
				*p = 0;
				p = fcn_0064d1a0(buf, '_');
			} while (p != 0);
			if (num == 1) {
				if (*(int*) (action + 0xc8) >= range[0])
					d3_SetSubtreeVisible((int) list.items[idx], 1);
				else
					d3_SetSubtreeVisible((int) list.items[idx], 0);
			} else if (num == 2) {
				if (*(int*) (action + 0xc8) <= range[0] && *(int*) (action + 0xc8) >= range[1])
					d3_SetSubtreeVisible((int) list.items[idx], 1);
				else
					d3_SetSubtreeVisible((int) list.items[idx], 0);
			}
		}
		idx++;
	}
	goto done;
release:
	slot = gm_SearchTable67(*(int*) (action + 0xb8));
	if (slot != 0 && *(int*) (slot + 0x61) != 0)
		d3_SetSubtreeVisible(*(int*) (slot + 0x61), 1);
	if (obj != 0) {
		if (g_773dd8 != 0)
			fcn_004550b0(obj, g_773dd8);
		d3_DestroyObject(obj);
	}
done:
	d3_SelectSceneContext(saved, 1);
}
