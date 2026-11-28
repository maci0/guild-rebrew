unsigned char __cdecl gm_GetCitySkillAverage(int a);
int __cdecl gm_SumStraftatSeverity(int a);
int __cdecl gm_GetLawEntry(int idx, void* dst);
char* __cdecl amt_FindOfficeHolderByType(int a);
int __cdecl gm_MapEntityStatRange(int a);
float __cdecl gm_GetEntitySkill(char* entity, int index);
float __cdecl gm_CalcEntityFavor(unsigned int a0, unsigned int a1, unsigned int a2);

/* ADDRESS: GOLDTL 0x00490580 */
/* ADDRESS: GOLDDE 0x0047f430 */
int __cdecl ai_EvaluateLaw0x01(char* e, int unused, int* choice)
{
	float y;
	int n;
	float z;
	float w;
	int info[9];
	float m;
	int job;
	char* p;
	float r;

	job = gm_MapEntityStatRange(*(unsigned char*) (e + 0x164));
	m = (gm_GetEntitySkill(e, 4) - (gm_GetCitySkillAverage(4) + 1.0f) * 0.003968254f)
		* 0.023809524f;
	y = (float) ((*(float*) (e + 0xf4) - 2.0) * *(float*) (e + 0xfc));
	w = (float) ((*(float*) (e + 0x100) - 2.0) * *(float*) (e + 0x108));
	z = (float) ((*(float*) (e + 0x10c) - 2.0) * *(float*) (e + 0x114));
	n = gm_SumStraftatSeverity(*(int*) (e + 4));
	if (job == 0xb || job == 0xc)
		m = m + 7.0f;
	else if (job == 9 || job == 1 || job == 3 || job == 2)
		m = m + 3.0f;
	else
		m = m + 5.0f;
	m = (float) n / ((float) (0x28 - (int) *(unsigned short*) (e + 0xa)) * 0.1f + m);
	gm_GetLawEntry(1, info);
	if (m > 1.0f && info[6] == 0) {
		if (m > 1.4f || z > y) {
			*choice = 1;
			return 1;
		}
		return 0;
	}
	if (m < 0.5f && info[6] == 1
		&& (w > y || *(unsigned char*) (e + 0x166) == 0x11)) {
		*choice = 0;
		return 1;
	}
	p = amt_FindOfficeHolderByType(0x11);
	if (p != 0) {
		r = gm_CalcEntityFavor(*(unsigned short*) p, *(unsigned short*) e, 1);
		if (info[6] == 1) {
			if (r > 0.75f) {
				*choice = 0;
				return 1;
			}
		} else if (info[6] == 0 && r < 0.25f) {
			*choice = 1;
			return 1;
		}
	}
	return 0;
}
