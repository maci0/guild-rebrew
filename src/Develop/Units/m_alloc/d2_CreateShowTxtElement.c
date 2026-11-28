typedef struct
{
	int i[0x2f4 / 4];
} D2_SHOWTXT_ENT;
// SIZE 0x2f4

#include "Develop/Units/d2.v1/d2_gui.h"
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int d2_ScreenHeight;
extern int g_1040494;
extern char g_67d5bc[];

int __cdecl d2_AllocateElement(void);
int __cdecl m_alloc(int, char*);
int __cdecl d2_MeasureTextWidth(char*, int);

/* ADDRESS: GOLDTL 0x0046fcd0 */
int __cdecl d2_CreateShowTxtElement(int xpos, int ypos, char* name)
{
	int idx;
	char c;
	char* s;
	char* d;

	idx = d2_AllocateElement();
	(*(int*)&((D2_CONTROL_TL*)d2_Controls)[idx].value_088) = m_alloc(0x101, g_67d5bc);
	if ((*(int*)&((D2_CONTROL_TL*)d2_Controls)[idx].value_088) == 0) {
		return -1;
	}
	s = name;
	d = (char*) (*(int*)&((D2_CONTROL_TL*)d2_Controls)[idx].value_088);
	do {
		c = *s;
		s++;
		*d = c;
		d++;
	} while (c != 0);
	(*(int*)&((D2_CONTROL_TL*)d2_Controls)[idx].font) = d2_DefaultFont;
	(*(int*)&((D2_CONTROL_TL*)d2_Controls)[idx].kind) = 0x43;
	(*(int*)&((D2_CONTROL_TL*)d2_Controls)[idx].x) = xpos;
	(*(int*)&((D2_CONTROL_TL*)d2_Controls)[idx].y) = ypos;
	(*(int*)&((D2_CONTROL_TL*)d2_Controls)[idx].width) = d2_MeasureTextWidth(name, (*(int*)&((D2_CONTROL_TL*)d2_Controls)[idx].font)) + 0x60;
	(*(int*)&((D2_CONTROL_TL*)d2_Controls)[idx].height) = d2_FontHeight;
	(*(int*)&((D2_CONTROL_TL*)d2_Controls)[idx].mode) = 2;
	(*(int*)&((D2_CONTROL_TL*)d2_Controls)[idx].clip_top) = 0;
	(*(int*)&((D2_CONTROL_TL*)d2_Controls)[idx].clip_bottom) = d2_ScreenHeight;
	(*(int*)&((D2_CONTROL_TL*)d2_Controls)[idx].clip_left) = 0;
	(*(int*)&((D2_CONTROL_TL*)d2_Controls)[idx].clip_right) = g_1040494;
	return idx;
}
