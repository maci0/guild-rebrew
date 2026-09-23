/* fcn_004e73c0 — format the status message into a local buffer. */

int __cdecl fcn_0064d41a(char*, char*, ...);

// FUNCTION: GOLDTL 0x4e73c0
// SIZE: 34
void __cdecl fcn_004e73c0(void)
{
	char buf[0x400];

	fcn_0064d41a(buf, (char*) 0x68d870, *(int*) 0x7f4c00);
}
