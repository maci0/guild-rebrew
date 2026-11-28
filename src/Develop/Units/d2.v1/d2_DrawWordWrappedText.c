#include <string.h>

extern char* d2_CurrentFontBank;
extern char* d2_BlackTexture;
extern int g_772544;
extern int g_772548;
extern int g_77254c;
extern int g_772550;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int d2_ScreenHeight;
extern int g_1040494;
extern int g_67d384;

int __cdecl d2_FindResourceByName(char* name);
void* __cdecl d2_GetResourceData(int handle);
int __cdecl d2_MeasureTextWidth(char* text, int font);
char* __cdecl d2_GetBankEntry(char* font, int c);
int __cdecl d2_DrawSpriteFromSet(int x, int y, int surface, void* font, int c);
int __cdecl d2_DrawDimmedSpriteFrame(int x, int y, int surface, void* font, int c);
int __cdecl d2_DrawHighlightSprite(int x, int y, int surface, void* font, int c);
int __cdecl d2_DrawBankSpriteColored(int x, int y, int surface, void* font, int c);
void __cdecl d2_DrawTexturedQuad(int width, int y, int x, int height, int color, float alpha);

/* ADDRESS: GOLDTL 0x0046bd20 */
/* ADDRESS: GOLDDE 0x0045f3a0 */
int __cdecl d2_DrawWordWrappedText(int x, int y, int width, int height, int surface,
                         int text_address, int flags)
{
    char words[16][0x60];
    char* text;
    char* word;
    char* end;
    char* last;
    char* glyph;
    char* p;
    int origin_x;
    int origin_y;
    int right;
    int used_width;
    int word_count;
    int next_count;
    int offset;
    int length;
    int last_width;
    int last_length;
    int split;
    int i;
    int j;
    int draw_x;
    int draw_y;
    int bg_x;
    int bg_y;
    int bg_width;
    int bg_height;
    int visible;
    unsigned char c;
    int (__cdecl *draw)(int, int, int, void*, int);

    origin_x = x;
    origin_y = y;
    used_width = 0;
    g_772544 = 0;
    g_772548 = 0;
    g_77254c = 9999;
    g_772550 = y;
    if (!d2_CurrentFontBank)
        d2_CurrentFontBank = (char*)d2_GetResourceData(d2_FindResourceByName("_FONT"));
    d2_FontHeight = *(unsigned short*)(d2_CurrentFontBank + 8);
    memset(words, 0, sizeof(words));
    if (surface && (flags & 0xa0)) {
        visible = 1;
        d2_DrawWordWrappedText(x, y, width, height, 0, text_address, flags);
        bg_x = g_772544 - g_77254c + x;
        bg_width = g_77254c;
        bg_height = g_772548;
        bg_y = g_772550;
        if (flags & 0x80) {
            if (bg_width + bg_x > g_1040494) {
                bg_width = g_1040494 - bg_x;
                x = g_1040494 - g_772544;
                origin_x = x;
                g_77254c = x;
            }
            if (bg_y + bg_height > d2_ScreenHeight) {
                bg_y = d2_ScreenHeight - bg_height;
                y = bg_y;
                origin_y = bg_y;
                g_772550 = bg_y;
            }
        }
        if (bg_y + bg_height < g_7725fc)
            visible = 0;
        if (bg_y > d2_ClipBottom)
            visible = 0;
        if (bg_y < g_7725fc) {
            bg_height = g_7725fc - bg_y;
            bg_y = g_7725fc;
        }
        if (bg_y + bg_height > d2_ClipBottom)
            bg_height = d2_ClipBottom - bg_y;
        if (visible)
            d2_DrawTexturedQuad(bg_width, bg_y, bg_x, bg_height,
                         *(int*)(d2_BlackTexture + 0x50), 0.7f);
        g_772544 = bg_x;
        g_772548 = bg_height;
    }
    offset = 0;
    word_count = 0;
    draw = d2_DrawBankSpriteColored;
    if (!(flags & 0x40))
        draw = d2_DrawSpriteFromSet;
    text = (char*)text_address;
    length = strlen(text);
    if (length > 0) {
        right = x + width;
        do {
            word = words[word_count];
            strcpy(word, text + offset);
            end = strchr(word, ' ');
            if (end)
                *end = 0;
            else
                end = strchr(word, 0);
            offset += end - word + 1;
            last_width = d2_MeasureTextWidth(word, d2_CurrentFont);
            x += last_width;
            used_width += last_width;
            if (offset <= length) {
                used_width += g_67d380;
                x += g_67d380;
            }
            next_count = word_count + 1;
            if (x >= right || offset >= length || end[-1] == '~') {
                if (used_width > width) {
                    last = words[next_count - 1];
                    last_length = strlen(last);
                    used_width -= last_width;
                    split = last_length;
                    while (split >= 0) {
                        if (last[split] == '~' || last[split] == '-') {
                            if (last[split] == '~')
                                last[split] = '-';
                            last[split + 1] = 0;
                            if (d2_MeasureTextWidth(last, d2_CurrentFont) + used_width <= width)
                                break;
                        }
                        split--;
                    }
                    if (split >= 0) {
                        offset += split - last_length;
                        used_width = 0;
                        word = words[0];
                        for (i = next_count; i > 0; i--) {
                            used_width += d2_MeasureTextWidth(word, d2_CurrentFont) + g_67d380;
                            word += 0x60;
                        }
                        used_width -= g_67d380;
                    } else if (next_count >= 2) {
                        offset += -1 - last_length;
                        next_count = word_count;
                        used_width = 0;
                        word = words[0];
                        for (i = next_count; i > 0; i--) {
                            used_width += d2_MeasureTextWidth(word, d2_CurrentFont) + g_67d380;
                            word += 0x60;
                        }
                        used_width -= g_67d380;
                    } else {
                        used_width += last_width;
                    }
                } else {
                    used_width -= g_67d380;
                }
                if ((flags & 8) && used_width <= width)
                    draw_x = (width - used_width) / 2 + origin_x;
                else {
                    draw_x = origin_x;
                    if (flags & 0x10)
                        draw_x = origin_x - used_width + width;
                }
                draw_y = y;
                if (draw_x <= g_77254c)
                    g_77254c = draw_x;
                word = words[0];
                for (i = next_count; i > 0; i--) {
                    p = word;
                    for (j = 0; j < (int)strlen(word); j++) {
                        c = (unsigned char)*p;
                        if (c != '~') {
                            glyph = d2_GetBankEntry(d2_CurrentFontBank, c);
                            if (right)
                                draw_x -= *(unsigned short*)(glyph + 0x11);
                            if (c != ' ') {
                                if (surface) {
                                    if (flags & 2)
                                        d2_DrawHighlightSprite(draw_x, draw_y, surface, d2_CurrentFontBank, c);
                                    else if (flags & 1)
                                        d2_DrawDimmedSpriteFrame(draw_x, draw_y, surface, d2_CurrentFontBank, c);
                                    else if (draw(draw_x, draw_y, surface, d2_CurrentFontBank, c))
                                        d2_DrawDepthIndex--;
                                }
                                draw_x += *(unsigned short*)(glyph + 0x15) + g_67d384;
                            }
                        }
                        if (draw_x > right + g_67d384) {
                            draw_y += d2_FontHeight;
                            draw_x = origin_x;
                        }
                        p++;
                    }
                    if (g_772544 < draw_x - origin_x)
                        g_772544 = draw_x - origin_x;
                    draw_x += g_67d380;
                    word += 0x60;
                }
                x = origin_x;
                y += d2_FontHeight;
                used_width = 0;
                word_count = 0;
                next_count = word_count;
            }
            word_count = next_count;
        } while (offset < length);
    }
    if (g_772548 <= y - origin_y)
        g_772548 = y - origin_y;
    return y - origin_y;
}
