extern char g_6b89c0[];


void __cdecl d3_FreeSkyDome(void*);

/* ADDRESS: GOLDDE 0x0044f380 */
void __cdecl d3_DestroySkySystem(void)
{
	if (*(int*) &g_6b89c0 != 0) {
		d3_FreeSkyDome((void*) *(int*) &g_6b89c0);
		*(int*) &g_6b89c0 = 0;
	}
}
