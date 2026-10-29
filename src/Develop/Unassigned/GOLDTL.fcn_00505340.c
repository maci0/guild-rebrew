extern unsigned char* lpGebaeudePROT;

/* ADDRESS: GOLDTL 0x00505340 */
int __cdecl fcn_00505340(unsigned char* e)
{
	return ((char*)lpGebaeudePROT)[*e * 0x24d] == 10;
}
