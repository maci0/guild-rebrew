#include "Develop/Units/d2.v1/d2_training_rows.h"











extern char* g_1015ea0;
extern char* lpObjektePROT;
extern unsigned char g_10161bc[];
extern int d2_CurrentWindowId;
extern int g_775334;

void __cdecl d2_SetForm(int, int);
void __cdecl d2_DestroyElement(int);
unsigned short* __cdecl fcn_00502cd0(int, int, ...);
int __cdecl io_AppendText(int, ...);
void __cdecl fcn_00534160(int, int, int, int);
int __cdecl fcn_00466ee0(int, int, int, int, int);
int __cdecl fcn_00471f80(int);
void __cdecl fcn_00472380(int, int, int, int);
unsigned short* __cdecl gm_NextEntityQueryMatch(void);
int __cdecl fcn_0046f740(int, int, int, int);
int __cdecl fcn_0046f100(int, int, int, int, int, int);
void __cdecl d2_SetElementFont(int, int);
int __cdecl fcn_00507c30(int);
void __cdecl fcn_00473690(int, int);
float __cdecl fcn_004ff040(int);

/* ADDRESS: GOLDTL 0x005c6a10 */
unsigned int __cdecl d2_UpdateTrainingRows(unsigned int dialog, unsigned int form)
{
	D2_TRAINING_ROW* slot;
	unsigned short* item;
	int* list;
	int* p;
	int i;
	int j;
	int k;
	int h;
	int v;
	int built;
	int row_offset;
	int row_y;
	int button_base;

	built = 0;
	d2_SetForm(dialog, form);
	g_775334 = 0;
	p = (int*) ((char*) g_7774a0 + 0x10);
	for (button_base = 0, row_offset = 0, row_y = 0x28; row_y < 0xf28;
	     row_y += 0x78, row_offset += 0x40, button_base += 8) {
		slot = (D2_TRAINING_ROW*) ((char*) g_7774a0 + row_offset);
		if (!slot->entity)
			continue;
		g_775334++;
		for (list = (int*) 0x7e4260; (int) list < 0x7e42e0; list++) {
			if (*list == slot->entity)
				break;
		}
		if ((int) list >= 0x7e42e0) {
			slot->entity = 0;
			if (slot->portrait_element != -1) {
				d2_DestroyElement(slot->portrait_element);
				slot->portrait_element = -1;
			}
			if (slot->row_element != -1) {
				d2_DestroyElement(slot->row_element);
				slot->row_element = -1;
			}
			if (slot->window != -1) {
				d2_DestroyElement(slot->window);
				slot->window = -1;
			}
			continue;
		}
		d2_CurrentWindowId = slot->window;
		for (j = 0; j < 6; j++) {
			if (slot->item[j].objekt_id != 0
			    && !fcn_00502cd0(*(int*) (slot->entity + 0x178), 1, 0, slot->item[j].objekt_id)) {
				d2_DestroyElement(slot->item[j].button);
				slot->item[j].button = -1;
				slot->item[j].objekt_id = 0;
			}
		}
		d2_CurrentWindowId = slot->window;
		io_AppendText(0x6ac790, *(unsigned short*) slot->entity,
			(int) (fcn_004ff040(slot->entity) * 100.0));
		io_AppendText(0x16ac);
		fcn_00534160(0x50, 0x16, *(unsigned char*) (slot->entity + 0x83), 0x4f1);
		io_AppendText(0x16ad);
		fcn_00534160(0x50, 0x25, *(unsigned char*) (slot->entity + 0x82), 0x4f1);
		item = fcn_00502cd0(*(int*) (slot->entity + 0x178), 1, 5);
		while (item) {
			if (*(char*) (lpObjektePROT + *item * 0x41) != '\t') {
				for (j = 0; j < 6; j++) {
					if (slot->item[j].objekt_id == *item)
						break;
				}
				if (j < 6)
					goto present;
				d2_SetForm(dialog, form);
				for (j = 0; j < 6; j++) {
					if (!slot->item[j].objekt_id)
						break;
				}
				if (j < 6) {
					p[(button_base + j) * 2] = fcn_00466ee0(j * 0x36 + 0x50, row_y,
						*item + 0xdf, 10, d2_CurrentWindowId);
					p[(button_base + j) * 2 + 1] = *item;
				}
present:
				v = fcn_00471f80(p[(button_base + j) * 2]);
				fcn_00472380(p[(button_base + j) * 2], 0, *(int*) ((char*) item + 0xe), v);
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
				break;
		}
		if (i < 32)
			continue;
		for (i = 0; i < 32; i++) {
			if (!g_7774a0[i].entity)
				break;
		}
		if (i >= 32)
			continue;
		d2_SetForm(dialog, form);
		g_7774a0[i].entity = *list;
		h = fcn_0046f740(0, i * 0x78, 0x74c, d2_CurrentWindowId);
		g_7774a0[i].row_element = h;
		*(int*) (g_1015ea0 + h * 0x2f4 + 0x5c) = 1;
		g_7774a0[i].portrait_element = fcn_0046f740(0x10, i * 0x78 + 5,
			*(int*) (g_7774a0[i].entity + 0x18c), d2_CurrentWindowId);
		h = fcn_0046f100(0x40, i * 0x78, 0xb4, 0x50, 0x10, d2_CurrentWindowId);
		g_7774a0[i].window = h;
		d2_SetElementFont(*(int*) (g_10161bc + h * 0x3cc), 0x54);
		io_AppendText(0x16ab, *(unsigned short*) g_7774a0[i].entity,
			*(unsigned char*) (g_7774a0[i].entity + 0x83));
	}
	for (i = 0; i < 32; i++) {
		if (!g_7774a0[i].entity)
			continue;
		for (j = 0; j < 6; j++) {
			if (g_7774a0[i].item[j].button != -1 && fcn_00471f80(g_7774a0[i].item[j].button)) {
				fcn_00473690(g_7774a0[i].item[j].objekt_id + 0xdf,
					fcn_00471f80(g_7774a0[i].item[j].button));
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
