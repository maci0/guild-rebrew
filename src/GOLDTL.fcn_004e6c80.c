/* ADDRESS: GOLDTL 0x0068d6bc */
extern char g_68d6bc[];
/* ADDRESS: GOLD 0x0060ea00 */
extern char g_68d6bc[];
/* ADDRESS: GOLDTL 0x009b0820 */
extern unsigned int g_9b0820;
/* ADDRESS: GOLD 0x0092c4e0 */
extern unsigned int g_9b0820;
/* fcn_004e6c80 — format a message with the current global string. */

int __cdecl fcn_0064d41a(char*, char*, ...);

/* ADDRESS: GOLD 0x004e52c0 */
/* ADDRESS: GOLDTL 0x004e6c80 */
char* __cdecl fcn_004e6c80(void)
{
	char buf[0x40];

	fcn_0064d41a(buf, g_68d6bc, g_9b0820);
	return (char*) g_9b0820;
}
