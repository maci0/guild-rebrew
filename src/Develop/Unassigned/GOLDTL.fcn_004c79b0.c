#include "Develop/DieGildeAddOn/game/entity_record.h"


// SIZE 0x21c
typedef struct {
	char data[0x21c];
} Rec21c;

extern char g_7f4ca0[];

int __cdecl gm_TransferDynastyEstate(int a, int b);
int __cdecl gm_LookupEntityRecordById(int h);
int __cdecl fcn_004f4650(int h, char** obj, int** val);
unsigned char __cdecl fcn_004f1790(int a, int* b);
void __cdecl fcn_004f22e0(int h, char* obj, int v, int flag);

int __cdecl cm_ExChangePlayerIdentity(char* cmd, char* result)
{
	int idx;
	int h;

	idx = gm_TransferDynastyEstate(*(int*) (cmd + 0x10), *(int*) (cmd + 0x14));
	if (result != 0) {
		result[0] = 1;
		if (idx >= 0) {
			char* obj;
			int* val;

			h = gm_LookupEntityRecordById(*(int*) (cmd + 0x14));
			if (fcn_004f4650(h, &obj, &val) != 0) {
				fcn_004f22e0(h, obj, *val, fcn_004f1790(*(int*) (obj + 0x65), val));
			}
			result[1] = 1;
			*(Rec21c**) (result + 6) = ((Rec21c *)&((ENTITY_RECORD_VIEW *)g_7f4ca0)[idx]);
		} else {
			result[1] = 0;
			*(int*) (result + 6) = 0;
		}
	}
	return 0;
}
