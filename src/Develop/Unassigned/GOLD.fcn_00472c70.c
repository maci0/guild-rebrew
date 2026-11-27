int __cdecl d2_GetResourceData(int font);
int __cdecl d2_GetResourceBankEntry(int font_data, unsigned short character);

/* ADDRESS: GOLD 0x00472c70 */
void __cdecl d2_GetWindowBorderSize(void* context, int* a1, int* a2)
{
	int font;

	if (*((unsigned char*) context + 0xc) & 4) {
		font = d2_GetResourceData(*(int*) ((char*) context + 0x278));
		*a2 = *(unsigned short*) (d2_GetResourceBankEntry(font, 4) + 0xa);
		*a1 = *(unsigned short*) (d2_GetResourceBankEntry(font, 6) + 6);
		return;
	}
	*a2 = 0;
	*a1 = 0;
}
