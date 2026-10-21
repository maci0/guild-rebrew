#include <stdio.h>
#include <string.h>

void __cdecl fcn_004379a0(int, int, int, int, void*);
void __cdecl fcn_00442d50(int, int);
void __cdecl fcn_004432d0(int, int);
int __cdecl fcn_00445600(int, int, int, char*);
void __cdecl fcn_004550b0(int, int);
void __cdecl d3_DestroyObject(int);
int __cdecl fcn_00504e70(int);
void __cdecl fcn_00573de0(void);
int __cdecl fcn_0064d41a(char*, const char*, ...);
char* __cdecl fcn_0064d1a0(char*, int);
char* __cdecl fcn_0064d530(char*, const char*, unsigned int);
int __cdecl fcn_0064eeec(char*);
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
void __cdecl fcn_00573e10(int a0)
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

	saved = *(int*) 0x6b8010;
	fcn_004432d0(0, 1);
	fcn_0064d41a(name, "he_%i", *(int*) (a0 + 4));
	obj = fcn_00445600(0, 0x1c0, 0, name);
	cur = *(int*) (a0 + 0xc8);
	if (cur == -1 && obj != 0) {
		list.handle = obj;
		list.count = 0;
		fcn_004379a0(*(int*) 0x67a370, obj, 0x2c0, (int) fcn_00573de0,
		             &list);
		idx = 0;
		while (idx < list.count) {
			slot = (int) list.items[idx];
			if (*(int*) (slot + 0x220) == 5
			    && !(*(unsigned char*) (slot + 0x217) & 1))
				goto next_mark;
			if ((*(unsigned char*) (slot + 0x217) & 1)
			    && *(int*) 0x773dd8 != 0)
				fcn_004550b0(slot, *(int*) 0x773dd8);
			*(int*) (slot + 0x220) = 5;
			*(unsigned char*) (slot + 0x217) &= 0xfe;
next_mark:
			idx++;
		}
		fcn_00442d50(obj, 0);
		goto done;
	}
	if (*(int*) (a0 + 0xc4) <= cur || obj == 0) {
		if (*(int*) (a0 + 0xc4) < cur)
			goto release;
		goto done;
	}
	list.handle = obj;
	list.count = 0;
	fcn_004379a0(*(int*) 0x67a370, obj, 0x2c0, (int) fcn_00573de0, &list);
	idx = 0;
	while (idx < list.count) {
		int item;

		item = (int) list.items[idx];
		if (*(int*) (item + 0x220) != 5
		    || (*(unsigned char*) (item + 0x217) & 1)) {
			if ((*(unsigned char*) (item + 0x217) & 1)
			    && *(int*) 0x773dd8 != 0)
				fcn_004550b0(item, *(int*) 0x773dd8);
			*(int*) (item + 0x220) = 5;
			*(unsigned char*) (item + 0x217) &= 0xfe;
		}
		item = (int) list.items[idx];
		*(int*) (item + 0x224) = 0;
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
			num = 0;
			do {
				if (num >= 2)
					break;
				fcn_0064d530((char*) digits, p + 1, 2);
				leader = 0;
				if (*(int*) 0x6b25b0 > 1)
					flag = _isctype((signed char) digits[0], 4);
				else
					flag = *(unsigned char*)
					    (*(unsigned char**) 0x6b23a4
					     + digits[0] * 2) & 4;
				if (flag)
					range[num++] = fcn_0064eeec((char*) digits);
				*p = 0;
				p = fcn_0064d1a0(buf, '_');
			} while (p != 0);
			flag = -1;
			if (num == 1) {
				flag = *(int*) (a0 + 0xc8) >= range[0];
			} else if (num == 2) {
				flag = *(int*) (a0 + 0xc8) <= range[0]
				    && *(int*) (a0 + 0xc8) >= range[1];
			}
			if (flag >= 0)
				fcn_00442d50((int) list.items[idx], flag);
		}
		idx++;
	}
	goto done;
release:
	slot = fcn_00504e70(*(int*) (a0 + 0xb8));
	if (slot != 0 && *(int*) (slot + 0x61) != 0)
		fcn_00442d50(*(int*) (slot + 0x61), 1);
	if (obj != 0) {
		if (*(int*) 0x773dd8 != 0)
			fcn_004550b0(obj, *(int*) 0x773dd8);
		d3_DestroyObject(obj);
	}
done:
	fcn_004432d0(saved, 1);
}
