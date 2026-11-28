#include <string.h>

extern int d3_CurrentContextIndex;
extern char g_1043695[];

int __cdecl fcn_0064d41a(char*, char*, ...);
char* __cdecl ch_FindCharacterByName(char*);
char* __cdecl gm_FindRecordById(int);
char* __cdecl gm_SearchTable67(int);
int __cdecl init_EnsureObjektSceneContext(char*);
int __cdecl init_AllocateGebaeudeSceneSlot(char*);
void __cdecl d3_SelectSceneContext(int, int);
char* __cdecl d3_FindSceneObject(int, int, int, char*);
void __cdecl ch_QueueStandUpAnimation(char*, char*);
char* __cdecl ch_QueueWalkToDummy(char*, char*);
char* __cdecl ch_CreateAction(char*, int, int);


/* ADDRESS: GOLDTL 0x004ca3d0 */
/* ADDRESS: GOLDDE 0x004b7bb0 */
int __cdecl cm_ExChrWalkToDummy(char* a1, char* a2)
{
	int saved;
	char buf[0x80];
	char* character;
	char* s;
	char* r;
	char* dummy;
	char* queuedWalk;
	int k;

	s = 0;
	r = 0;
	fcn_0064d41a(buf, "sp_%i", *(int*) (a1 + 0x10));
	character = ch_FindCharacterByName(buf);
	if (character == 0)
		return 1;
	if (*(int*) (a1 + 0x18) != -1)
		s = gm_FindRecordById(*(int*) (a1 + 0x18));
	else
		r = gm_SearchTable67(*(int*) (a1 + 0x14));
	saved = d3_CurrentContextIndex;
	if (*(int*) (a1 + 0x18) != -1)
		k = init_EnsureObjektSceneContext(s);
	else if (*(int*) (a1 + 0x14) != -1)
		k = init_AllocateGebaeudeSceneSlot(r);
	else
		k = 0;
	if (k == -1)
		return 2;
	if (g_1043695[k * 988] != 0)
		return 3;
	if (a1[0x1c] != 0) {
		d3_SelectSceneContext(k, 1);
		dummy = d3_FindSceneObject(0, 0x160, 0, a1 + 0x1c);
		d3_SelectSceneContext(saved, 1);
		if (dummy == 0)
			return 4;
		ch_QueueStandUpAnimation(character, "sitzend/aufstehen");
		queuedWalk = ch_QueueWalkToDummy(character, dummy);
		if (queuedWalk != 0)
			strcpy(queuedWalk + 0x70, "cm_ExChrWalkToDummy");
	} else {
		ch_QueueStandUpAnimation(character, "sitzend/aufstehen");
		ch_CreateAction(character, 0x39, k);
	}
	if (a2 != 0) {
		a2[0] = 1;
		a2[1] = 0;
		*(int*) (a2 + 6) = 0;
	}
	return 0;
}
