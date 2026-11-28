int __cdecl gm_IsDiceStageValid(char*, char*, int);
void __cdecl cm_RequestTransferCurrencyNoKill(int, int, char, int);
void __cdecl ai_RollWirtshausDice(void*, void*, int);
void __cdecl gm_AdvanceDiceStage(char*, char*, int);

/* ADDRESS: GOLDTL 0x00492d60 */
/* ADDRESS: GOLDDE 0x00481c10 */
int __cdecl gm_ExecuteDiceStage(int* p, char* q, int kind)
{
	if (!gm_IsDiceStageValid((char*) p, q, kind)) {
		return 0;
	}
	switch (kind) {
	case 1:
		if (q[2] == 6) {
			cm_RequestTransferCurrencyNoKill(-1, *(int*) (q + 4), 0, *p);
		}
		p[0x15] += *p;
		ai_RollWirtshausDice(p, q, 1);
		gm_AdvanceDiceStage((char*) p, q, kind);
		return 1;
	case 2:
		if (q[2] == 6) {
			cm_RequestTransferCurrencyNoKill(-1, *(int*) (q + 4), 0, p[1]);
		}
		p[0x15] += p[1];
		ai_RollWirtshausDice(p, q, 0);
		gm_AdvanceDiceStage((char*) p, q, kind);
		return 1;
	case 3:
		if (q[2] == 6) {
			cm_RequestTransferCurrencyNoKill(-1, *(int*) (q + 4), 0, p[1]);
		}
		p[0x15] += p[1];
		gm_AdvanceDiceStage((char*) p, q, kind);
		return 1;
	case 4:
		gm_AdvanceDiceStage((char*) p, q, kind);
		return 1;
	default:
		return 0;
	}
}
