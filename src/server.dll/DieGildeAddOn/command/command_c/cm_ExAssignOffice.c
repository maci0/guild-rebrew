/* cm_ExAssignOffice - proper C */

extern unsigned int __cdecl ValidateAndAssignOffice(unsigned int*);

/* Execution handler: assigns the office described by the command
 * payload at offset 0x10 to the requesting player. Returns 1 on
 * success, 0 on failure. */

// CFLAGS: /O2 /Gd
// FUNCTION: SERVER 0x1000f940
// SYMBOL: _cm_ExAssignOffice
// SIZE: 22

int __cdecl cm_ExAssignOffice(void* obj)
{
	return ValidateAndAssignOffice((unsigned int*) obj + 4) == 0;
}
