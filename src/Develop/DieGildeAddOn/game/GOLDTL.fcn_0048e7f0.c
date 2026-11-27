unsigned short* __cdecl gm_StartFilteredEntitySearch(int arg_count, ...);


/* ADDRESS: GOLDTL 0x0048e7f0 */
int __cdecl ai_CheckSculptureEligibility(char* entity, unsigned short** out)
{
	unsigned short* building;

	if (entity[2] == 3)
		return 0;
	building = gm_StartFilteredEntitySearch(2, 5, 0x21, 4, *(unsigned short*) entity);
	if (out != 0)
		*out = building;
	if (building != 0)
		return 2;
	if (entity[2] == 5)
		return 1;
	if ((entity[2] == 2 || entity[2] == 4) && (unsigned char) entity[0xd] > 6)
		return 1;
	return 0;
}
