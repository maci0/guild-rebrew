extern int ai_ActiveMethodCount;

/* ADDRESS: GOLDTL 0x00495140 */
/* ADDRESS: GOLDDE 0x00483c00 */
void __cdecl ai_PopActiveMethod(void)
{
	ai_ActiveMethodCount--;
}
