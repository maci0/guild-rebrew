
/* ADDRESS: GOLDTL 0x0054b420 */
void __cdecl he_StartSkillDuelEvent(char* entry)
{
	entry += 0x52;
	*(int*) entry = *(int*) 0x7f4c00;
	*(int*) (entry + 4) = *(int*) 0x7f4c04;
	*(int*) (entry + 8) = *(int*) 0x7f4c08;
	*(unsigned short*) (entry + 0xc) = *(unsigned short*) 0x7f4c0c;
}
