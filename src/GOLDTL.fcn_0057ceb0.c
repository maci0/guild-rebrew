#include <string.h>

typedef struct {
	int id;
	int a;
	int b;
	char* item;
} Slot57ceb0;

typedef struct {
	int total;
	int blocked;
	int free;
} Counts57ceb0;

extern unsigned char g_773d75;

char* __cdecl fcn_00508e40(int a1);
int __cdecl gm_ResolveEntityById(void** out, void** a2, void** a3, int a4);
void __cdecl fcn_004a51d0(char* e, int n, Slot57ceb0* slots, Counts57ceb0* cnt);
int __cdecl fcn_0051af00(char* dst, int id, ...);
int __cdecl fcn_004c51f0(int a1, int a2, short a3, int a4, char a5, int a6);
void __cdecl fcn_004c51a0(int a1, int a2, char a3, int a4);
float __cdecl fcn_0050bb50(int id, unsigned char a);
int __cdecl fcn_00545d40(int id, int arg, char* text1, unsigned char flags, int value, char* text2);

/* ADDRESS: GOLDTL 0x0057ceb0 */
void __cdecl fcn_0057ceb0(char* entity)
{
	char buf[0x200];
	char msg[0x100];
	Slot57ceb0 slots[4];
	Counts57ceb0 counts;
	int handles[4];
	short* p;
	char* v3;
	char* item;
	int id;
	int n;
	int queued;
	int i;
	void* v15;

	v3 = fcn_00508e40(*(int*) (entity + 0xc));
	if (v3 == 0) {
		return;
	}
	gm_ResolveEntityById(&v15, 0, 0, *(int*) (entity + 0x10));
	if (v15 == 0) {
		return;
	}
	memset(slots, 0, sizeof(slots));
	n = 0;
	p = (short*) (entity + 0xc8);
	for (i = 0; i < 4; i++) {
		if (*p != 0) {
			slots[n].id = *p;
			n++;
		}
		p++;
	}
	if (n == 0) {
		fcn_0051af00(msg, 0x41f1, *(unsigned int*) (entity + 0xac));
	}
	else {
		fcn_004a51d0(v3, n, slots, &counts);
		queued = 0;
		p = (short*) (entity + 0xc8);
		for (i = 0; i < n; i++) {
			if (*p != 0) {
				id = *p;
				item = slots[i].item;
				if (item != 0) {
					if (*(int*) (item + 0xe) < 3) {
						handles[queued] = id;
						fcn_004c51f0(*(int*) (v3 + 4), -1, (short) id, 1, g_773d75, 0);
						queued++;
						goto next;
					}
					*(int*) (entity + 0xac) += (int) fcn_0050bb50(id, g_773d75);
					goto next;
				}
				if (counts.total < 6) {
					counts.total++;
					handles[queued] = id;
					fcn_004c51f0(*(int*) (v3 + 4), -1, (short) id, 1, g_773d75, 0);
					queued++;
					goto next;
				}
				*(int*) (entity + 0xac) += (int) fcn_0050bb50(id, g_773d75);
			}
next:
			p++;
		}
		if (queued != 0) {
			fcn_0051af00(msg, 0x41f2, *(unsigned int*) (entity + 0xac));
		}
		else {
			fcn_0051af00(msg, 0x41f1, *(unsigned int*) (entity + 0xac));
		}
	}
	fcn_004c51a0(*(int*) (v3 + 4), -1, g_773d75, *(unsigned int*) (entity + 0xac));
	fcn_0051af00(buf, 0x41f0, v15, msg);
	fcn_00545d40(*(int*) (v3 + 4), -1, buf, 0, 0x5ff, 0);
}
