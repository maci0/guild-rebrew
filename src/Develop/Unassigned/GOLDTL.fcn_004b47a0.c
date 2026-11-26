extern unsigned char g_773d75;

int __cdecl fcn_0050d320(int, char);
int __cdecl fcn_0050b710(int, char);


/* ADDRESS: GOLDTL 0x004b47a0 */
int __cdecl gm_HasMinEntityGold(int entity, char* spec)
{
	return fcn_0050b710(fcn_0050d320(entity, (*(char*)&g_773d75)), (*(char*)&g_773d75)) >= *(int*) (spec + 0x14);
}
