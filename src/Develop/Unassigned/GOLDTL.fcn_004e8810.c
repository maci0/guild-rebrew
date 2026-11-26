struct job_4e8810 {
	unsigned char key;
	char pad1[3];
	int id;
	unsigned char slot;
	char pad9[15];
};
// SIZE 0x18

#include "client_types.h"
extern Rec18_68da68 amt_OfficeSlots[42];

char* __cdecl gm_LookupEntityRecordById(int);
void __cdecl amt_NotifyOfficeSwap(char*, char*, char*);


/* ADDRESS: GOLDTL 0x004e8810 */
int __cdecl amt_SwapOfficeOccupants(unsigned char* request)
{
	char* e;
	char* w1;
	char* w2;
	struct job_4e8810* p1;
	struct job_4e8810* p2;
	int i;
	int savedId;

	e = gm_LookupEntityRecordById(*(int*) request);
	if (e == 0)
		return 0;
	if (*(int*) (e + 0x194) < *(int*) (request + 6))
		return 0;
	p1 = 0;
	for (i = 0; i < 30; i++) {
		if (((struct job_4e8810*)amt_OfficeSlots)[i].key == request[4]) {
			p1 = &((struct job_4e8810*)amt_OfficeSlots)[i];
			break;
		}
	}
	if (p1 == 0)
		return 0;
	w1 = gm_LookupEntityRecordById(p1->id);
	if (w1 == 0)
		return 0;
	p2 = 0;
	for (i = 0; i < 30; i++) {
		if (((struct job_4e8810*)amt_OfficeSlots)[i].key == request[5]) {
			p2 = &((struct job_4e8810*)amt_OfficeSlots)[i];
			break;
		}
	}
	if (p2 == 0)
		return 0;
	w2 = gm_LookupEntityRecordById(p2->id);
	if (w2 == 0)
		return 0;
	amt_NotifyOfficeSwap(e, w1, w2);
	w1[0x166] = p2->slot;
	w2[0x166] = p1->slot;
	savedId = p1->id;
	p1->id = p2->id;
	p2->id = savedId;
	*(int*) (e + 0x194) -= *(int*) (request + 6);
	return 1;
}
