#include <string.h>

int __cdecl fcn_004690a0(int font);
int __cdecl fcn_0047cb60(int font_data, unsigned int character);

/* ADDRESS: GOLD 0x0046ea00 */
int __cdecl fcn_0046ea00(const char* text, int font)
{
    int length;
    int font_data;
    int width;
    int i;
    char* glyph;
    unsigned char character;

    width = 0;
    length = (int)strlen(text);
    font_data = fcn_004690a0(font);
    for (i = 0; i < length; i++) {
        character = (unsigned char)text[i];
        if (character != '~') {
            glyph = (char*)fcn_0047cb60(font_data, character);
            if (i != 0 && text[i - 1] != ' ') {
                width -= *(unsigned short*)(glyph + 0x16);
            }
            if (character == ' ') {
                width += *(unsigned short*)(glyph + 0x1a) + *(int*)0x5fe724 + *(int*)0x5fe728;
            } else {
                width += *(unsigned short*)(glyph + 0x1a) + *(int*)0x5fe728;
            }
        }
    }
    return width + *(int*)0x5fe728;
}
