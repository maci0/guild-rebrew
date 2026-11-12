#include <string.h>

extern char* g_772524;
extern char* g_77253c;
extern int g_772544;
extern int g_772548;
extern int g_77254c;
extern int g_772550;
extern int g_7725fc;
extern int g_772608;
extern int g_1015ea4;
extern int g_1040490;
extern int g_1040494;
extern int g_67d378;
extern int g_67d380;
extern int g_67d384;
extern int g_67d968;

int __cdecl fcn_00465950(char* name);
void* __cdecl d2_GetResourceData(int handle);
int __cdecl fcn_0046b520(char* text, int font);
char* __cdecl fcn_0047b620(char* font, int c);
int __cdecl fcn_0047cba0(int x, int y, int surface, void* font, int c);
int __cdecl fcn_0047cbf0(int x, int y, int surface, void* font, int c);
int __cdecl fcn_0047ccd0(int x, int y, int surface, void* font, int c);
int __cdecl fcn_0047cd20(int x, int y, int surface, void* font, int c);
void __cdecl fcn_0047c9c0(int width, int y, int x, int height, int color, float alpha);

/* ADDRESS: GOLDTL 0x0046bd20 */
int __cdecl fcn_0046bd20(int x, int y, int width, int height, int surface,
                         int text_address, int flags)
{
    char words[16][0x60];
    char* text;
    char* word;
    char* end;
    char* last;
    char* glyph;
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
    if (!g_772524)
        g_772524 = (char*)d2_GetResourceData(fcn_00465950("_FONT"));
    g_1015ea4 = *(unsigned short*)(g_772524 + 8);
    memset(words, 0, sizeof(words));
    if (surface && (flags & 0xa0)) {
        visible = 1;
        fcn_0046bd20(x, y, width, height, 0, text_address, flags);
        bg_x = g_772544 - g_77254c + x;
        bg_width = g_77254c;
        bg_height = g_772548;
        bg_y = g_772550;
        if ((char)flags < 0) {
            if (bg_width + bg_x > g_1040494) {
                bg_width = g_1040494 - bg_x;
                x = g_1040494 - g_772544;
                origin_x = x;
                g_77254c = x;
            }
            if (bg_y + bg_height > g_1040490) {
                bg_y = g_1040490 - bg_height;
                y = bg_y;
                origin_y = bg_y;
                g_772550 = bg_y;
            }
        }
        if (bg_y + bg_height < g_7725fc)
            visible = 0;
        if (bg_y > g_67d968)
            visible = 0;
        if (bg_y < g_7725fc) {
            bg_height = g_7725fc - bg_y;
            bg_y = g_7725fc;
        }
        if (bg_y + bg_height > g_67d968)
            bg_height = g_67d968 - bg_y;
        if (visible)
            fcn_0047c9c0(bg_width, bg_y, bg_x, bg_height,
                         *(int*)(g_77253c + 0x50), 0.7f);
        g_772544 = bg_x;
        g_772548 = bg_height;
    }
    offset = 0;
    word_count = 0;
    draw = fcn_0047cd20;
    if (!(flags & 0x40))
        draw = fcn_0047cba0;
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
            last_width = fcn_0046b520(word, g_67d378);
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
                            if (fcn_0046b520(last, g_67d378) + used_width <= width)
                                break;
                        }
                        split--;
                    }
                    if (split >= 0) {
                        offset += split - last_length;
                        used_width = 0;
                        word = words[0];
                        for (i = next_count; i > 0; i--) {
                            used_width += fcn_0046b520(word, g_67d378) + g_67d380;
                            word += 0x60;
                        }
                        used_width -= g_67d380;
                    } else if (next_count >= 2) {
                        offset += -1 - last_length;
                        next_count = word_count;
                        used_width = 0;
                        word = words[0];
                        for (i = next_count; i > 0; i--) {
                            used_width += fcn_0046b520(word, g_67d378) + g_67d380;
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
                    for (j = 0; j < (int)strlen(word); j++) {
                        c = (unsigned char)word[j];
                        if (c != '~') {
                            glyph = fcn_0047b620(g_772524, c);
                            if (j)
                                draw_x -= *(unsigned short*)(glyph + 0x11);
                            if (c != ' ') {
                                if (surface) {
                                    if (flags & 2)
                                        fcn_0047ccd0(draw_x, draw_y, surface, g_772524, c);
                                    else if (flags & 1)
                                        fcn_0047cbf0(draw_x, draw_y, surface, g_772524, c);
                                    else if (draw(draw_x, draw_y, surface, g_772524, c))
                                        g_772608--;
                                }
                                draw_x += *(unsigned short*)(glyph + 0x15) + g_67d384;
                            }
                        }
                        if (draw_x > right + g_67d384) {
                            draw_y += g_1015ea4;
                            draw_x = origin_x;
                        }
                    }
                    if (g_772544 < draw_x - origin_x)
                        g_772544 = draw_x - origin_x;
                    draw_x += g_67d380;
                    word += 0x60;
                }
                x = origin_x;
                y += g_1015ea4;
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
