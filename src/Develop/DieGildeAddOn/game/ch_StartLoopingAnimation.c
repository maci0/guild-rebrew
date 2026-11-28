


char* __cdecl ch_AttachAni(char* e, char* name, int flag);
void __cdecl d3_SetAnimFrame(int h, char* s, int n);

/* ADDRESS: GOLDDE 0x0040b260 */
void __cdecl ch_StartLoopingAnimation(char* e, char* name)
{
	char* s;

	s = ch_AttachAni(e, name, 1);
	*(char**) (e + 0x74) = s;
	*(int*) (e + 0x70) = 0;
	if (s != 0) {
		d3_SetAnimFrame(*(int*) (e + 0x34), s, -1);
		*(unsigned char*) (*(char**) (e + 0x74) + 0x6c) = 1;
		*(int*) (*(char**) (e + 0x74) + 0x70) &= ~3;
		*(unsigned char*) (*(char**) (e + 0x74) + 0x6d) |= 0x10;
	}
}
