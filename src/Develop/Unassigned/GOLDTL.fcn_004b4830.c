


void __cdecl ai_FilterCandidateLimit(int, int, int);

void __cdecl gm_HasMissionOfficeWithinLimit(char* entity, int holder, int* spec)
{
	ai_FilterCandidateLimit(holder, (unsigned char) entity[0x166] == spec[5], spec[6]);
}
