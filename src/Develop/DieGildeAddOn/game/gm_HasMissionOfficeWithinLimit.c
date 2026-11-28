


void __cdecl ai_FilterCandidateLimit(int, int, int);

/* ADDRESS: GOLDDE 0x004a2b20 */
void __cdecl gm_HasMissionOfficeWithinLimit(char* entity, int holder, int* spec)
{
	ai_FilterCandidateLimit(holder, (unsigned char) entity[0x166] == spec[5], spec[6]);
}
