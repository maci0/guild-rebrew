#pragma pack(push, 2)
typedef struct {
	int a;
	int b;
	int c;
	short d;
} Cpy14;
#pragma pack(pop)
extern char* lpObjektePROT;
#include "Develop/DieGildeAddOn/game/object_prototype.h"
double __cdecl gm_CalcAvgEntityFavor(int, int, void*);
int __cdecl gm_SearchTable67(int);
void __cdecl he_AssignActionSlot(int, int, int, void*);
void __cdecl gm_AddTime(void*, int, int, int);

/* ADDRESS: GOLDTL 0x00571140 */
void __cdecl he_StartAbbau(char* obj)
{
	int value;
	int id;
	Cpy14* dst;
	char* p;
	double scaled;
	char* table;
	unsigned int index;

	table = lpObjektePROT; index = *(unsigned short*) (obj + 0xac);
	value = *(int *)&((OBJECT_PROTOTYPE *)table)[index].value_022;
	*(int*) (obj + 0xb0) = value;
	dst = (Cpy14*) (obj + 0x52);
	*dst = *(Cpy14*) (obj + 0x44);
	*(Cpy14*) (obj + 0x60) = *(Cpy14*) (obj + 0x44);
	*(float*) (obj + 0xb4) = (float) value;
	scaled = gm_CalcAvgEntityFavor(*(unsigned short*) (obj + 8), 8, obj + 0x8c) - *(double*) 0x662908;
	*(char*) (obj + 0xc8) = 0;
	*(float*) (obj + 0xc4) = (float) (scaled * *(double*) 0x662ad8);
	id = gm_SearchTable67(*(int*) (obj + 0xb8));
	for (p = (char*) 0x7f4ca0; (int) p < 0x85a0a0; p += 0x21c) {
		if (*(int*) (p + 0x17c) == (int) obj) {
			he_AssignActionSlot(id, 0, *(unsigned short*) p, obj);
		}
	}
	gm_AddTime(dst, 0, 0, 1);
}
