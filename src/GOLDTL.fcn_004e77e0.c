/* fcn_004e77e0 — format the second status message into a local buffer. */

int __cdecl fcn_0064d41a(char*, char*, ...);

// FUNCTION: GOLDTL 0x4e77e0
void __cdecl fcn_004e77e0(void)
{
	char buf[0x400];

	fcn_0064d41a(buf, (char*) 0x68d968, *(int*) 0x7f4c00);
}
