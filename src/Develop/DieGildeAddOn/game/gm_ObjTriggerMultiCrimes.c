


#include <stdlib.h>
#include <string.h>

typedef struct Cand {
	unsigned char id;
	unsigned char kind;
	char pad2[0x14 - 2];
	char active;
	char pad15[3];
	int ptr;
	char pad1c[0x24 - 0x1c];
} Cand;
// SIZE 0x24

extern __int64 gm_TargetPersonTypeMask;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern char gm_LawEntries[];

void __cdecl io_FormatTextBuffer(char*, int, ...);
char* __cdecl d2_OpenTargetPicker(int*, char*, int, int);
char* __cdecl gm_LookupEntityRecordById(int);
int __cdecl gm_HasActiveSpecialObject(char*, int);
void __cdecl gm_TryRecordCrime(int, int, int, int, int);
void __cdecl he_PostEntityMessage(int, int, char*, int, int, int);
char* __cdecl gm_LookupSpecialObjectRecord(int, int*);
void __cdecl d2_ShowUseObjDialog(char*);

/* ADDRESS: GOLDDE 0x005c07e0 */
int __cdecl gm_ObjTriggerMultiCrimes(char* ent, int* arg)
{
	int ok;
	int tmp;
	int desc[20];
	int list[29];
	char name[0x100];
	char text[0x400];
	char* obj;
	char* rec;
	int twice;
	int n;
	int r;
	int i;

	ok = 0;
	if (ent[2] == 6) {
		memset(desc, 0, sizeof(desc));
		memset(desc + 7, 0xff, 8 * sizeof(int));
		io_FormatTextBuffer(name, 0x9c);
		desc[2] = (*(int*)&gm_TargetPersonTypeMask);
		desc[0] = 1;
		desc[1] = 0x400;
		desc[4] = 6;
		desc[3] = g_66601c;
		obj = d2_OpenTargetPicker(desc, name, 0, 0);
		if (obj == 0) {
			goto end;
		}
		ok = 1;
	} else {
		obj = gm_LookupEntityRecordById(arg[1]);
		if (obj == 0) {
			goto end;
		}
		ok = 1;
	}
	twice = gm_HasActiveSpecialObject(ent, 0x2c5) != 0;
	n = 0;
	for (i = 0; i < 29; i++) {
		if (((Cand*)gm_LawEntries)[i].kind == 2 && ((Cand*)gm_LawEntries)[i].active && ((Cand*)gm_LawEntries)[i].ptr) {
			list[n++] = ((Cand*)gm_LawEntries)[i].id;
		}
	}
	if (n == 0) {
		io_FormatTextBuffer(text, 0xfff);
		he_PostEntityMessage(*(int*) (obj + 4), -1, text, 0, 0x5fa, 0);
		return 0;
	}
	r = rand() % n;
	gm_TryRecordCrime(list[r], 1, *(int*) (obj + 4), *(int*) (ent + 4),
	    *(char**) (ent + 0x170) ? *(int*) (*(char**) (ent + 0x170) + 1) : -1);
	r = rand() % n;
	gm_TryRecordCrime(list[r], 1, *(int*) (obj + 4), *(int*) (ent + 4),
	    *(char**) (ent + 0x170) ? *(int*) (*(char**) (ent + 0x170) + 1) : -1);
	if (twice) {
		r = rand() % n;
		gm_TryRecordCrime(list[r], 1, *(int*) (obj + 4), *(int*) (ent + 4),
		    *(char**) (ent + 0x170) ? *(int*) (*(char**) (ent + 0x170) + 1) : -1);
		r = rand() % n;
		gm_TryRecordCrime(list[r], 1, *(int*) (obj + 4), *(int*) (ent + 4),
		    *(char**) (ent + 0x170) ? *(int*) (*(char**) (ent + 0x170) + 1) : -1);
	}
	if (obj[2] == 6 || obj[2] == 7) {
		io_FormatTextBuffer(text, 0xfff);
		he_PostEntityMessage(*(int*) (obj + 4), -1, text, 0, 0x5fb, 0);
	}
	if (ent[2] == 6) {
		rec = gm_LookupSpecialObjectRecord(**(unsigned short**) arg, &tmp);
		arg[4] = 1;
		io_FormatTextBuffer(text, 0xfe8, *(unsigned short*) (rec + 0x18) + 1, *(unsigned short*) obj);
		d2_ShowUseObjDialog(text);
	}
end:
	return ok;
}
