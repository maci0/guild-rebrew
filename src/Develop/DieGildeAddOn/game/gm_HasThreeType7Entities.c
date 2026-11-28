int __cdecl ai_FilterRankCandidateLimit(unsigned short*, int, int);
char* __cdecl gm_StartFilteredEntitySearch(int arg_count, ...);
char* __cdecl gm_AddObjekt(void);
char* __cdecl gm_FindNextFilteredEntity(void);


/* ADDRESS: GOLDTL 0x004b4c10 */
/* ADDRESS: GOLDDE 0x004a2f00 */
int __cdecl gm_HasThreeType7Entities(unsigned short* owner_id, int arg_b, int arg_c)
{
	int count;
	char* entity;

	if (ai_FilterRankCandidateLimit(owner_id, arg_b, arg_c) == 0)
		return 0;
	count = 0;
	for (entity = gm_StartFilteredEntitySearch(2, 4, *owner_id, count, 7); entity != 0; entity = gm_FindNextFilteredEntity())
		count++;
	return count >= 3;
}
