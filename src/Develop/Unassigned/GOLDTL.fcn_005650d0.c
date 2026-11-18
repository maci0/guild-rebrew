
/* ADDRESS: GOLDTL 0x005650d0 */
void __cdecl fcn_005650d0(char* action)
{
	action += 0x52;
	*(int*) action = *(int*) 0x7f4c00;
	*(int*) (action + 4) = *(int*) 0x7f4c04;
	*(int*) (action + 8) = *(int*) 0x7f4c08;
	*(unsigned short*) (action + 0xc) = *(unsigned short*) 0x7f4c0c;
}
