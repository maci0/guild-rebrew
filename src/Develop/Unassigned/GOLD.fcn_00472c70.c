int __cdecl fcn_004690a0(int font);
int __cdecl fcn_0047cb60(int font_data, unsigned short character);

/* ADDRESS: GOLD 0x00472c70 */
void __cdecl fcn_00472c70(void* a0, int* a1, int* a2)
{
	int font;

	if (*((unsigned char*) a0 + 0xc) & 4) {
		font = fcn_004690a0(*(int*) ((char*) a0 + 0x278));
		*a2 = *(unsigned short*) (fcn_0047cb60(font, 4) + 0xa);
		*a1 = *(unsigned short*) (fcn_0047cb60(font, 6) + 6);
		return;
	}
	*a2 = 0;
	*a1 = 0;
}
