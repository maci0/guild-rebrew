

int __cdecl amt_ValidateOfficeCandidate(char*);

int __cdecl cm_ValidateOfficeCandidateCmd(char* p)
{
	return amt_ValidateOfficeCandidate(p + 0x10) == 0;
}
