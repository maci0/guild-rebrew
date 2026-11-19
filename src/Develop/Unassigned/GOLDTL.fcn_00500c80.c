
/* ADDRESS: GOLDTL 0x00500c80 */
void __cdecl gm_CopyGameTime(char* p)
{
	char* q;

	q = p;
	*(int*) q = *(int*) 0x7f4c00;
	*(int*) (q + 4) = *(int*) 0x7f4c04;
	*(int*) (q + 8) = *(int*) 0x7f4c08;
	*(unsigned short*) (q + 0xc) = *(unsigned short*) 0x7f4c0c;
}
