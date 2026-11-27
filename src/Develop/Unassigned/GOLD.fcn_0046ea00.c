#include <string.h>

int __cdecl d2_GetResourceData(int font);
int __cdecl d2_GetResourceBankEntry(int font_data, unsigned short character);

/* ADDRESS: GOLD 0x0046ea00 */
int __cdecl d2_CalcTextWidth(const char* text, int font)
{
    int length;
    int font_data;
    int width;
    int i;
    char* glyph;
    unsigned char character;

    width = 0;
    length = (int)strlen(text);
    font_data = d2_GetResourceData(font);
    for (i = 0; i < length; i++) {
        character = (unsigned char)text[i];
        if (character != '~') {
            glyph = (char*)d2_GetResourceBankEntry(font_data, character);
            if (i != 0 && text[i - 1] != ' ') {
                width -= *(unsigned short*)(glyph + 0x16);
            }
            if (character != ' ') {
                width += *(unsigned short*)(glyph + 0x1a) + *(int*)0x5fe728;
            } else {
                width += *(unsigned short*)(glyph + 0x1a) + *(int*)0x5fe724 + *(int*)0x5fe728;
            }
        }
    }
    return width + *(int*)0x5fe728;
}
