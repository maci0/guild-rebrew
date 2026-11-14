#include <string.h>
#include <stdio.h>
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/DieGildeAddOn/game/entity.h"
extern int g_9b4a40[];

void* __cdecl gm_LookupEntityRecordById(int);
int __cdecl fcn_004fe2e0(char*, int, int*, int*, int, int*);
void __cdecl fcn_004ce9e0(char*);
char* __cdecl fcn_004ce610(char*);
char* __cdecl fcn_004ce680(char*);

/* ADDRESS: GOLDTL 0x004d1970 */
void* __cdecl fcn_004d1970(int a1, int a2)
{
	char* src;
	char* rec;
	char* obj;
	char* e;
	char* e2;
	int i;
	int f;
	EntityStruct* pool;
	EntityStruct* scan;

	src = (char*) gm_LookupEntityRecordById(a1);
	i = 0;
	pool = (EntityStruct*) g_9b4a40;
	scan = pool;
	do {
		if (scan->entity_index == 0xffff)
			goto found;
		i++; scan++;
	} while ((int) scan < (int) (pool + 32));
	return 0;
found:
	rec = (char*) &pool[i];
	pool[i] = *(EntityStruct*) src;
	*(int*) ((char*) g_9b4a40 + i * 0x21c + 0x1ac) = 0;
	*(int*) ((char*) g_9b4a40 + i * 0x21c + 0x184) = 0;
	fcn_004fe2e0(rec, g_6b8010, 0, 0, 0, (int*) a2);
	obj = *(char**) ((char*) g_9b4a40 + i * 0x21c + 0x184);
	*(unsigned char*) (obj + 0x240) = 4;
	obj = *(char**) ((char*) g_9b4a40 + i * 0x21c + 0x184);
	*(unsigned char*) (obj + 0x8d) |= 0x80;
	fcn_004ce9e0(rec);
	e = (char*) fcn_004ce610(src);
	obj = *(char**) ((char*) g_9b4a40 + i * 0x21c + 0x184);
	*(float*) (obj + 0x1a0) = (float) ((double) *(unsigned char*) (e + 9) * (2.0 / 7.0));
	obj = *(char**) ((char*) g_9b4a40 + i * 0x21c + 0x184);
	f = *(int*) (obj + 0x34);
	sprintf((char*) f, "cmb_%i", *(int*) ((char*) g_9b4a40 + i * 0x21c + 4));
	e2 = (char*) fcn_004ce680(src);
	if (e2 != 0) {
		if (*(int*) (e + 0x58) == 2) {
			*(int*) (e2 + 0x20) = 6;
		} else {
			*(int*) (e2 + 0x20) = 0x0f;
		}
	}
	return rec;
}
