/* Draws one minimap/office slot: resolves the slot record from the global
 * table, picks the frame colour, draws the glyph runs and finally the label. */

extern char* g_1015ea0;
extern int d2_FontHeight;
extern int d2_CurrentElementId;
extern int tp_d2_SelectedControl;
extern int g_7725fc;
extern int d2_ClipBottom;
extern double g_662908;

typedef struct Glyph {
	unsigned short id;
	unsigned short w;
	unsigned short pad4;
	unsigned short h;
} Glyph;

void __cdecl fcn_00472880(int font);
Glyph* __cdecl fcn_0047b620(char* font, int c);
void __cdecl fcn_0047cba0(int x, int y, int surf, char* font, int c);
void __cdecl fcn_0047a040(int a, int b, int c, int d);
void __cdecl fcn_0046bd20(int x, int y, int w, int h, int surf, char* text, int flags);

/* ADDRESS: GOLDTL 0x00468e40 */
void __cdecl fcn_00468e40(int slotIndex, int surface)
{
	char* slot;
	char* font;
	Glyph* leftGlyph;
	Glyph* rightGlyph;
	Glyph* middleGlyph;
	int innerWidth;
	int flags;
	int glyphBase;
	unsigned char color;
	int i;

	glyphBase = 0; color = 8; slot = g_1015ea0 + slotIndex * 0x2f4;
	flags = *(int*) (slot + 0x1d0);
	if ((flags & 2) && tp_d2_SelectedControl == 0) {
		if (!((g_1015ea0 + d2_CurrentElementId * 0x2f4 != slot) && *(int*) (slot + 0x38) == 0)
		    && *(int*) (slot + 0x4c) == 0) {
			if (flags & 1) {
				*(int*) (slot + 0x3c) = 1;
			}
		} else if (flags & 1) {
			*(int*) (slot + 0x3c) = 0;
		}
	}
	if (!(flags & 2) && *(int*) (slot + 0x58) != 0 && *(int*) (slot + 0x4c) == 0) {
		*(int*) (slot + 0x3c) = *(int*) (slot + 0x38);
	}
	if (*(int*) (slot + 0x3c) != 0) {
		color = 10;
	} else if (*(int*) (slot + 0x60) != 0) {
		color = 9;
	}
	fcn_00472880(*(int*) (slot + 0x84));
	font = *(char**) (slot + 0xc);
	leftGlyph = fcn_0047b620(font, 0);
	rightGlyph = fcn_0047b620(font, 1);
	middleGlyph = fcn_0047b620(font, 2);
	innerWidth = (*(int*) (slot + 0x18) - rightGlyph->w) - leftGlyph->w;
	if (*(int*) (slot + 0x3c) != 0) {
		glyphBase = 3;
	}
	fcn_0047cba0(*(int*) (slot + 0x10), *(int*) (slot + 0x14), surface, font, glyphBase);
	fcn_0047cba0((*(int*) (slot + 0x18) - rightGlyph->w) + *(int*) (slot + 0x10),
	    *(int*) (slot + 0x14), surface, font, glyphBase + 1);

	fcn_0047a040(*(int*) (slot + 0x10) + leftGlyph->w - 1, g_7725fc, *(int*) (slot + 0x10) + leftGlyph->w + innerWidth, d2_ClipBottom);
	i = 0;
	if (0.0 < (double) (innerWidth / middleGlyph->w) + 0.5) {
		do {
			fcn_0047cba0(middleGlyph->w * i + leftGlyph->w + *(int*) (slot + 0x10),
			    *(int*) (slot + 0x14), surface, font, glyphBase + 2);
			i++;
		} while ((double) i < (double) (innerWidth / middleGlyph->w) + 0.5);
	}
	fcn_0046bd20(*(int*) (slot + 0x10),
	    ((leftGlyph->h >> 1) - d2_FontHeight / 2) + 1 + *(int*) (slot + 0x14),
	    *(int*) (slot + 0x18), *(int*) (slot + 0x1c), surface, slot + 0x8c, color);
}
