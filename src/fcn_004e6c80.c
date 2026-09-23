/* fcn_004e6c80 — format a message with the current global string. */

int __cdecl fcn_0064d41a(char*, char*, ...);

// FUNCTION: GOLDTL 0x4e6c80
// SIZE: 33
char* __cdecl fcn_004e6c80(void)
{
	char buf[0x40];

	fcn_0064d41a(buf, (char*) 0x68d6bc, *(char**) 0x9b0820);
	return *(char**) 0x9b0820;
}
