int __cdecl ai_ComputeBaseActionScore(float* o1, float* o2, int a3, char* e, int a5, int a6, int a7);

/* ADDRESS: GOLDTL 0x00496dc0 */
int __cdecl ai_ScoreAmtsbewerbung(float* o1, float* o2, int actionIdx, char* entity, int skip, int extraA, int extraB)
{
	float scale;

	if (skip) {
		*o1 = -1.0e30f;
		*o2 = -1.0e30f;
		return 0;
	}
	*o1 = 0;
	*o2 = 0;
	if (entity[0x167] && !entity[0x166]) {
		scale = 10.0f;
	} else {
		scale = 1.0f;
	}
	ai_ComputeBaseActionScore(o1, o2, actionIdx, entity, 0, extraA, extraB);
	*o1 = scale * *o1;
	*o2 = scale * *o2;
	return 1;
}
