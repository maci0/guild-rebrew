

int __cdecl amt_ValidateOfficeCandidate(char*);

int __cdecl fcn_004c7310(char* p)
{
	return amt_ValidateOfficeCandidate(p + 0x10) == 0;
}
