void __cdecl io_FormatTextBuffer(char*, int, ...);
int __cdecl main_RunFrameLoop(int, int);
void __cdecl d2_SetForm(int, int);
void __cdecl d2_RenderDialogIconsAndText(int);
void __cdecl d2_RenderDiceRollIcons(int, unsigned char*);
void __cdecl d2_RenderPlayerDiceIcons(int, unsigned char*);
extern volatile int gm_GameTicks; extern unsigned short gm_LocalPlayerSlot; extern char gm_EntityIdField[];
/* ADDRESS: GOLDTL 0x005a0cd0 */
void __cdecl d2_ShowWirtshausDiceStep(unsigned char* a0, unsigned char* a1, int mode, int windowId, int formId, int duration, int a6)
{
	unsigned int start;
	char buf[256];
	int step;
	unsigned int last;

	step = 2;
	if (a6 == 0) {
		switch (mode) {
		case 1:
			io_FormatTextBuffer(buf, 0x1883, *(int*) a1 + 0x30);
			start = gm_GameTicks;
			last = gm_GameTicks;
			while (start + duration > gm_GameTicks) {
				main_RunFrameLoop(0, 0x777c7);
				if (!*(char*) ((char*) &gm_EntityIdField + (*(unsigned short*) &gm_LocalPlayerSlot) * 0x21c + 4)) {
					break;
				}
				if (last + step < gm_GameTicks) {
					d2_SetForm(windowId, formId);
					d2_RenderDialogIconsAndText((int) buf);
					step += step / 2;
					last = gm_GameTicks;
				}
			}
			break;
		case 2:
			io_FormatTextBuffer(buf, 0x1884, *(int*) a1 + 0x30, *(int*) (a0 + 4));
			start = gm_GameTicks;
			last = gm_GameTicks;
			while (start + duration > gm_GameTicks) {
				main_RunFrameLoop(0, 0x777c7);
				if (!*(char*) ((char*) &gm_EntityIdField + (*(unsigned short*) &gm_LocalPlayerSlot) * 0x21c + 4)) {
					break;
				}
				if (last + step < gm_GameTicks) {
					d2_SetForm(windowId, formId);
					d2_RenderDiceRollIcons((int) buf, a1);
					step += step / 2;
					last = gm_GameTicks;
				}
			}
			break;
		case 3:
			io_FormatTextBuffer(buf, 0x1885, *(int*) a1 + 0x30, *(int*) (a0 + 4));
			start = gm_GameTicks;
			last = gm_GameTicks;
			d2_SetForm(windowId, formId);
			d2_RenderPlayerDiceIcons((int) buf, a1);
			while (start + duration > gm_GameTicks) {
				if (!*(char*) ((char*) &gm_EntityIdField + (*(unsigned short*) &gm_LocalPlayerSlot) * 0x21c + 4)) {
					break;
				}
				main_RunFrameLoop(0, 0x777c7);
			}
			break;
		case 4:
			io_FormatTextBuffer(buf, 0x1886, *(int*) a1 + 0x30, *(int*) (a0 + 4));
			start = gm_GameTicks;
			last = gm_GameTicks;
			d2_SetForm(windowId, formId);
			d2_RenderPlayerDiceIcons((int) buf, a1);
			while (start + duration > gm_GameTicks) {
				if (!*(char*) ((char*) &gm_EntityIdField + (*(unsigned short*) &gm_LocalPlayerSlot) * 0x21c + 4)) {
					break;
				}
				main_RunFrameLoop(0, 0x777c7);
			}
			break;
		}
	}
	else {
		switch (mode) {
		case 1:
			io_FormatTextBuffer(buf, 0x1883, *(int*) a1 + 0x30);
			break;
		case 2:
			io_FormatTextBuffer(buf, 0x1884, *(int*) a1 + 0x30, *(int*) (a0 + 4));
			break;
		case 3:
			io_FormatTextBuffer(buf, 0x1885, *(int*) a1 + 0x30, *(int*) (a0 + 4));
			break;
		case 4:
			io_FormatTextBuffer(buf, 0x1886, *(int*) a1 + 0x30, *(int*) (a0 + 4));
			break;
		}
		start = gm_GameTicks;
		last = gm_GameTicks;
		d2_SetForm(windowId, formId);
		d2_RenderPlayerDiceIcons((int) buf, a1);
		while (start + duration > gm_GameTicks) {
			if (!(*(char*) ((char*) &gm_EntityIdField + (*(unsigned short*) &gm_LocalPlayerSlot) * 0x21c + 4))) {
				break;
			}
			main_RunFrameLoop(0, 0x777c7);
		}
	}
}
