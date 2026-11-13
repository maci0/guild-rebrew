/* Master-dialog message loop: reads the 0x11 request packet, resolves the
   object, shows the 0x6ab180 dialog and forwards the 0x39 reply while
   fcn_005373e0 keeps the loop alive. */
int __cdecl fcn_004e8a80(int, void*);
char* __cdecl gm_LookupEntityRecordById(int);
int __cdecl fcn_00526120(int, int);
int __cdecl fcn_005463a0(int, int, int, int, int);
int __cdecl io_FormatTextBuffer(char*, int, ...);
void* __cdecl fcn_00470820(int, int, void*);
void __cdecl fcn_00471b60(void*);
void __cdecl fcn_00471e30(void*);
void __cdecl d2_SetForm(void*, int);
int __cdecl fcn_00472250(void*, int, int);
void __cdecl fcn_00472380(int, int, int, int);
void __cdecl d2_SetOverlayAnimation(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl gm_SumSlotTreasury(int);
int __cdecl fcn_0050b710(int, char);
int __cdecl fcn_0050b750(int, char);
int __cdecl fcn_00471f80(int, char);
void __cdecl fcn_004c4eb0(void*);
void __cdecl fcn_004c4ef0(void*);
void __cdecl fcn_004c5150(int, int, char, int);
void __cdecl fcn_004c5530(void*);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00532ef0(void);

typedef struct Dlg005ad000 {
	int ctl;
	char pkt[0x910];
} Dlg005ad000;
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "client_dialog_state.h"
extern int g_14ce8e0;
extern int g_67d370;
/* ADDRESS: GOLDTL 0x005ad000 */
void __cdecl fcn_005ad000(void)
{
	Dlg005ad000 msg;
	char* obj;
	void* dlg;
	int ctl1;
	int ctl2;
	int h;
	int id;

	if (fcn_004e8a80(0x11, msg.pkt) == 0) {
		return;
	}
	obj = gm_LookupEntityRecordById(*(int*) (msg.pkt + 4));
	if (obj == 0) {
		fcn_00526120(*(int*) 0x14ab9f4, 0);
		fcn_00532ef0();
		return;
	}
	if (fcn_005463a0(2, 0, 0x39, 2, *(unsigned short*) &g_774970) != 0) {
		io_FormatTextBuffer(msg.pkt + 0x110, 0x19b6, *(unsigned short*) obj);
		fcn_00526120((int) (msg.pkt + 0x110), 0);
		fcn_00532ef0();
		return;
	}
	dlg = fcn_00470820(0, 0, (void*) 0x6ab180);
	fcn_00471b60(dlg);
	d2_SetForm(dlg, 1);
	h = *(unsigned char*) &g_773d75;
	id = io_AppendText(0x19b1, h, h, *(unsigned short*) obj);
	ctl1 = fcn_00472250(dlg, 1, id);
	ctl2 = fcn_00472250(dlg, 1, id + 1);
	id = *(unsigned short*) &g_774970;
	msg.ctl = ctl2;
	h = gm_SumSlotTreasury(id);
	fcn_00472380(ctl1, 0x96,
	             fcn_0050b710(h, *(unsigned char*) &g_773d75), 0xfa);
	d2_SetOverlayAnimation(0, 0);
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (*(int*) &g_100f1dc != -1 && g_67d370 == msg.ctl) {
			*(int*) (msg.pkt + 0x20) = *(int*) (obj + 4);
			*(char*) (msg.pkt + 0x1c) = 0x39;
			*(int*) (msg.pkt + 0x24) = -1;
			*(char*) (msg.pkt + 0x4e) = 9;
			*(int*) (msg.pkt + 0x74) = *(int*) (obj + 4);
			*(int*) (msg.pkt + 0x70) = *(int*) ((unsigned long)&g_7f4ca4 +
			                                    *(unsigned short*) &g_774970 * 0x21c);
			h = *(unsigned char*) &g_773d75;
			*(int*) (msg.pkt + 0x78) = fcn_0050b750(
			    fcn_00471f80(ctl1, h), h);
			fcn_004c4eb0((void*) 0x6ab168);
			fcn_004c5150(*(int*) (obj + 4),
			             *(int*) ((unsigned long)&g_7f4ca4 + *(unsigned short*) &g_774970 * 0x21c),
			             *(char*) &g_773d75, *(int*) (msg.pkt + 0x78));
			fcn_004c5530(msg.pkt + 0x14);
			fcn_004c4ef0((void*) 0x6ab168);
			g_774654 = 1;
		}
	} while (fcn_005373e0((void*) 0x5ad000, 0x677c7) != 0);
	fcn_00471e30(dlg);
	fcn_00532ef0();
}
