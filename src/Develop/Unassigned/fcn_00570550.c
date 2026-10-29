
/* ADDRESS: GOLDTL 0x00570550 */
void __cdecl fcn_00570550(char* p)
{
	char* q;

	*(int*) (p + 0x52) = *(int*) 0x7f4c00;
	q = p + 0x52;
	*(int*) (q + 4) = *(int*) 0x7f4c04;
	*(int*) (q + 8) = *(int*) 0x7f4c08;
	*(short*) (q + 0xc) = *(short*) 0x7f4c0c;
	*(int*) (p + 0x84) = -1;
	*(short*) (p + 0x56) = 6;
	*(int*) (p + 0x58) = 0;
}
