#include "Develop/Units/d2.v1/d2_training_rows.h"
#include "Develop/DieGildeAddOn/game/object_prototype.h"










#include "Develop/Units/d2.v1/d2_gui.h"
extern char* lpObjektePROT;
extern unsigned char g_10161bc[];
extern int d2_CurrentWindowId;
extern int g_775334;

void __cdecl d2_SetForm(int, int);
void __cdecl d2_DestroyElement(int);
unsigned short* __cdecl fcn_00502cd0(int, int, ...);
int __cdecl io_AppendText(int, ...);
void __cdecl fcn_00534160(int, int, int, int);
int __cdecl d2_AddWindowField(int, int, int, int, int);
int __cdecl d2_GetControlValue(int);
void __cdecl fcn_00472380(int, int, int, int);
unsigned short* __cdecl gm_NextEntityQueryMatch(void);
int __cdecl d2_AddElementToWindow(int, int, int, int);
int __cdecl d2_CreateChildWindow(int, int, int, int, int, int);
void __cdecl d2_SetElementFont(int, int);
int __cdecl fcn_00507c30(int);
void __cdecl d2_AddDisplayCounter(int, int);
float __cdecl gm_GetEntityHealthRatio(int);

/* ADDRESS: GOLDTL 0x005c6a10 */
unsigned int __cdecl d2_UpdateTrainingRows(unsigned int dialog, unsigned int form)
{
	unsigned short* item;
	int* list;
	int i;
	int j;
	int k;
	int h;
	int v;
	int built;

	built = 0;
	d2_SetForm(dialog, form);
	g_775334 = 0;
	for (i = 0; i < 32; i++) {
		if (!g_7774a0[i].entity)
			continue;
		g_775334++;
		for (list = (int*) 0x7e4260; (int) list < 0x7e42e0; list++) {
			if (*list == g_7774a0[i].entity)
				break;
		}
		if ((int) list >= 0x7e42e0) {
			g_7774a0[i].entity = 0;
			if (g_7774a0[i].portrait_element != -1) {
				d2_DestroyElement(g_7774a0[i].portrait_element);
				g_7774a0[i].portrait_element = -1;
			}
			if (g_7774a0[i].row_element != -1) {
				d2_DestroyElement(g_7774a0[i].row_element);
				g_7774a0[i].row_element = -1;
			}
			if (g_7774a0[i].window != -1) {
				d2_DestroyElement(g_7774a0[i].window);
				g_7774a0[i].window = -1;
			}
			continue;
		}
		d2_CurrentWindowId = g_7774a0[i].window;
		for (j = 0; j < 6; j++) {
			if (g_7774a0[i].item[j].objekt_id != 0
			    && !fcn_00502cd0(*(int*) (g_7774a0[i].entity + 0x178), 1, 0, g_7774a0[i].item[j].objekt_id)) {
				d2_DestroyElement(g_7774a0[i].item[j].button);
				g_7774a0[i].item[j].button = -1;
				g_7774a0[i].item[j].objekt_id = 0;
			}
		}
		d2_CurrentWindowId = g_7774a0[i].window;
		io_AppendText(0x6ac790, *(unsigned short*) g_7774a0[i].entity,
			(int) (gm_GetEntityHealthRatio(g_7774a0[i].entity) * 100.0));
		io_AppendText(0x16ac);
		fcn_00534160(0x50, 0x16, *(unsigned char*) (g_7774a0[i].entity + 0x83), 0x4f1);
		io_AppendText(0x16ad);
		fcn_00534160(0x50, 0x25, *(unsigned char*) (g_7774a0[i].entity + 0x82), 0x4f1);
		item = fcn_00502cd0(*(int*) (g_7774a0[i].entity + 0x178), 1, 5);
		while (item) {
			if ((char)((OBJECT_PROTOTYPE*)lpObjektePROT)[*item].kind != '\t') {
				for (j = 0; j < 6; j++) {
					if (g_7774a0[i].item[j].objekt_id == *item)
						goto present;
				}
				d2_SetForm(dialog, form);
				for (j = 0; j < 6; j++) {
					if (!g_7774a0[i].item[j].objekt_id)
						goto found_item_slot;
				}
				goto present;
			found_item_slot:
				g_7774a0[i].item[j].button = d2_AddWindowField(j * 0x36 + 0x50, i * 0x78 + 0x28,
					*item + 0xdf, 10, d2_CurrentWindowId);
				g_7774a0[i].item[j].objekt_id = *item;
			present:
				v = d2_GetControlValue(g_7774a0[i].item[j].button);
				fcn_00472380(g_7774a0[i].item[j].button, 0, *(int*) ((char*) item + 0xe), v);
			}
			item = gm_NextEntityQueryMatch();
		}
	}
	for (list = (int*) 0x7e4260; (int) list < 0x7e42e0; list++) {
		if (!*list)
			continue;
		k = fcn_00507c30(*(unsigned char*) (*list + 0x165));
		if (k < 10 || k > 12)
			continue;
		for (i = 0; i < 32; i++) {
			if (g_7774a0[i].entity == *list)
				goto next_list;
		}
		for (i = 0; i < 32; i++) {
			if (!g_7774a0[i].entity)
				goto found_row_slot;
		}
		continue;
	found_row_slot:
		d2_SetForm(dialog, form);
		g_7774a0[i].entity = *list;
		h = d2_AddElementToWindow(0, i * 0x78, 0x74c, d2_CurrentWindowId);
		g_7774a0[i].row_element = h;
		*(int*)&((D2_CONTROL_TL*)g_1015ea0)[h].value_05c = 1;
		g_7774a0[i].portrait_element = d2_AddElementToWindow(0x10, i * 0x78 + 5,
			*(int*) (g_7774a0[i].entity + 0x18c), d2_CurrentWindowId);
		h = d2_CreateChildWindow(0x40, i * 0x78, 0xb4, 0x50, 0x10, d2_CurrentWindowId);
		g_7774a0[i].window = h;
		d2_SetElementFont(*(int*) (g_10161bc + h * 0x3cc), 0x54);
		io_AppendText(0x16ab, *(unsigned short*) g_7774a0[i].entity,
			*(unsigned char*) (g_7774a0[i].entity + 0x83));
	next_list:
		;
	}
	for (i = 0; i < 32; i++) {
		if (!g_7774a0[i].entity)
			continue;
		for (j = 0; j < 6; j++) {
			if (g_7774a0[i].item[j].button != -1 && d2_GetControlValue(g_7774a0[i].item[j].button)) {
				d2_AddDisplayCounter(g_7774a0[i].item[j].objekt_id + 0xdf,
					d2_GetControlValue(g_7774a0[i].item[j].button));
				built = 1;
			}
		}
	}
	return built;
}
#if defined(REBREW_SERVER) || defined(REBREW_GOLD)
unsigned char _dpad_7766a0[3584];
unsigned char _dpad_7774a0[7360];
#else
/* Reference gaps only; the emitted objects inside the span keep their own rows. */
unsigned char _dpad_7766b4[6];
unsigned char _dpad_7766be[70];
unsigned char _dpad_776710[912];
unsigned char _dpad_776ae0[384];
unsigned char _dpad_776c78[24];
unsigned char _dpad_776c98[8];
unsigned char _dpad_7770a0[1024];
unsigned char _dpad_777520[1920];
unsigned char _dpad_777ca8[88];
unsigned char _dpad_777f00[3072];
unsigned char _dpad_778b04[28];
unsigned char _dpad_778b24[508];
unsigned char _dpad_778d28[32];
unsigned char _dpad_778d5c[68];
unsigned char _dpad_778de0[840];
unsigned char _dpad_779130[24];
unsigned char _dpad_779150[16];
#endif
