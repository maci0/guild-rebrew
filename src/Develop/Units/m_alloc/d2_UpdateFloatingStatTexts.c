#include <stdio.h>

typedef struct
{
	float speed;
	int ticks;
	int handle;
	char* owner;
	int arg;
} Timer14;
// SIZE 0x14

extern Timer14 g_9b4900[16];

char __cdecl d3_GetObjectScreenRect(void*, int*);
int __cdecl d2_CreateShowTxtElement(int x, int y, char* name);
void __cdecl d2_PositionControl(int x, int y, int slot);
void __cdecl d2_DestroyElement(int slot);
void __cdecl d2_SetSlotVisibility(int slot, int flag);

/* ADDRESS: GOLDTL 0x004cfca0 */
/* ADDRESS: GOLDDE 0x004bd180 */
void __cdecl d2_UpdateFloatingStatTexts(void)
{
	int r[4];
	char buf[64];
	int i;
	int px;
	int py;
	char* owner;

	for (i = 0; i < 16; i++) {
		if (g_9b4900[i].ticks == 0) {
			continue;
		}
		owner = g_9b4900[i].owner;
		if (!d3_GetObjectScreenRect((void*) *(int*) (*(char**) ((char*) owner + 0x184) + 0x34), r)) {
			if (g_9b4900[i].handle != -1) {
				d2_SetSlotVisibility(g_9b4900[i].handle, 0);
			}
			return;
		}
		px = r[0] + 0x10;
		py = r[1] - 0x30;
		if (g_9b4900[i].handle == -1) {
			if (g_9b4900[i].arg == 1) {
				sprintf(buf, "%c-%i%c", 0x5c, g_9b4900[i].ticks, 0x5d);
			} else if (g_9b4900[i].arg == 2) {
				sprintf(buf, "%c-%i%c", 0x5e, g_9b4900[i].ticks, 0x5f);
			} else {
				sprintf(buf, "%i", g_9b4900[i].ticks);
			}
			g_9b4900[i].handle = d2_CreateShowTxtElement(px, (int) ((float) py + g_9b4900[i].speed), buf);
		} else {
			d2_PositionControl(px, (int) ((float) py + g_9b4900[i].speed), g_9b4900[i].handle);
		}
		if (g_9b4900[i].handle != -1) {
			d2_SetSlotVisibility(g_9b4900[i].handle, 1);
		}
		g_9b4900[i].speed = g_9b4900[i].speed - 0.5;
		if (g_9b4900[i].speed <= 0.0f) {
			d2_DestroyElement(g_9b4900[i].handle);
			g_9b4900[i].ticks = 0;
			g_9b4900[i].handle = -1;
			g_9b4900[i].owner = 0;
		}
	}
}
