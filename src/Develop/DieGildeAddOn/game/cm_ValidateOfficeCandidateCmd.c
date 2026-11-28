

int __cdecl amt_ValidateOfficeCandidate(char*);

/* ADDRESS: GOLDDE 0x004b4b00 */
int __cdecl cm_ValidateOfficeCandidateCmd(char* p)
{
	return amt_ValidateOfficeCandidate(p + 0x10) == 0;
}
