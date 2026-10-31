struct job_4e8810 {
	unsigned char key;
	char pad1[3];
	int id;
	unsigned char slot;
	char pad9[15];
};
// SIZE 0x18

#include "client_types.h"
extern Rec18_68da68 g_9a9220[42];

char* __cdecl gm_LookupEntityRecordById(int);
void __cdecl fcn_005b2900(char*, char*, char*);


/* ADDRESS: GOLDTL 0x004e8810 */
int __cdecl fcn_004e8810(unsigned char* a1)
{
	char* e;
	char* w1;
	char* w2;
	struct job_4e8810* p1;
	struct job_4e8810* p2;
	int i;
	int t;

	e = gm_LookupEntityRecordById(*(int*) a1);
	if (e == 0)
		return 0;
	if (*(int*) (e + 0x194) < *(int*) (a1 + 6))
		return 0;
	p1 = 0;
	for (i = 0; i < 30; i++) {
		if (((struct job_4e8810*)g_9a9220)[i].key == a1[4]) {
			p1 = &((struct job_4e8810*)g_9a9220)[i];
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
		if (((struct job_4e8810*)g_9a9220)[i].key == a1[5]) {
			p2 = &((struct job_4e8810*)g_9a9220)[i];
			break;
		}
	}
	if (p2 == 0)
		return 0;
	w2 = gm_LookupEntityRecordById(p2->id);
	if (w2 == 0)
		return 0;
	fcn_005b2900(e, w1, w2);
	w1[0x166] = p2->slot;
	w2[0x166] = p1->slot;
	t = p1->id;
	p1->id = p2->id;
	p2->id = t;
	*(int*) (e + 0x194) -= *(int*) (a1 + 6);
	return 1;
}
