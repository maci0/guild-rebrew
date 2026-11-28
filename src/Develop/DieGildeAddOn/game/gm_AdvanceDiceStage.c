


// SIZE 0x8
typedef struct {
	int a;
	int b;
} DiceStageEdge;

extern DiceStageEdge g_6641a0[];

/* ADDRESS: GOLDDE 0x00481840 */
int __cdecl gm_AdvanceDiceStage(char* p, int entity, int stage)
{
	int* slot;
	int i;
	DiceStageEdge* t;

	if (entity == *(int*) (p + 0xc)) {
		slot = (int*) (p + 0x28);
	} else if (entity == *(int*) (p + 0x30)) {
		slot = (int*) (p + 0x4c);
	} else {
		return 0;
	}
	t = g_6641a0;
	for (i = 0; i < 9; i++) {
		if (t[i].a == *slot && t[i].b == stage) {
			*slot = t[i].b;
			return 1;
		}
	}
	return 0;
}
