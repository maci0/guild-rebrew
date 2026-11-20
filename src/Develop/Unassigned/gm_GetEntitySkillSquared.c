float __cdecl gm_GetEntitySkill(char* entity, int index);

/* ADDRESS: GOLDTL 0x00507e50 */
float __cdecl gm_GetEntitySkillSquared(char* entity, int index)
{
	float t;

	t = gm_GetEntitySkill(entity, index);
	return t * t;
}
