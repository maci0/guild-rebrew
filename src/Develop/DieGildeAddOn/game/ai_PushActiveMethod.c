
/* ADDRESS: GOLDTL 0x00495120 */
/* ADDRESS: GOLDDE 0x00483be0 */
void __cdecl ai_PushActiveMethod(int methodType)
{
	int i;

	i = *(int*) 0x1008524;
	((int*) 0x100af80)[i] = methodType;
	*(int*) 0x1008524 = i + 1;
}
