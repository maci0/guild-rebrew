// GLOBAL: GOLDTL 0x68d6bc
extern char g_68d6bc[];
// GLOBAL: GOLD 0x60ea00
extern char g_68d6bc[];
// GLOBAL: GOLDTL 0x9b0820
extern unsigned int g_9b0820;
// GLOBAL: GOLD 0x92c4e0
extern unsigned int g_9b0820;
/* fcn_004e6c80 — format a message with the current global string. */

int __cdecl fcn_0064d41a(char*, char*, ...);

// FUNCTION: GOLD 0x004e52c0
// FUNCTION: GOLDTL 0x4e6c80
char* __cdecl fcn_004e6c80(void)
{
	char buf[0x40];

	fcn_0064d41a(buf, g_68d6bc, g_9b0820);
	return (char*) g_9b0820;
}
