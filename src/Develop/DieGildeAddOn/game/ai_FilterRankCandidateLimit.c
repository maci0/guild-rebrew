


void __cdecl ai_FilterCandidateLimit(int, int, int);

/* ADDRESS: GOLDDE 0x004a2a20 */
void __cdecl ai_FilterRankCandidateLimit(char* entity, int holder, int* spec)
{
	ai_FilterCandidateLimit(holder, (unsigned char) entity[0xd] >= spec[5], spec[6]);
}
