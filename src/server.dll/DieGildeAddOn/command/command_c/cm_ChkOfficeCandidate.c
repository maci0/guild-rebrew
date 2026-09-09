/* cm_ChkOfficeCandidate - proper C */

extern int __cdecl amt_ValidateOfficeCandidate(int*);

/* Validation handler: checks if the entity described by the command
 * payload at offset 0x10 is eligible for an office position. Returns
 * 1 when the candidate is valid, 0 otherwise. */

// FUNCTION: SERVER 0x1000d020
// SIZE: 22

int __cdecl cm_ChkOfficeCandidate(void* obj)
{
	return amt_ValidateOfficeCandidate((int*) obj + 4) == 0;
}
