#include "Develop/DieGildeAddOn/game/event_callbacks.h"

#include <string.h>

extern char* g_14a9a28;
extern char g_6b5c60[];

char* __cdecl gm_LookupEntityRecordById(int);
void __cdecl fcn_004c57e0(int, int);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl fcn_004e6240(char*, char*, char*, char*);

#include "Develop/DieGildeAddOn/game/game_data.h"
extern char g_14cf950;
extern int tp_d2_SelectedControl;
extern int g_7747f0;

char* __cdecl gm_LookupEntityRecordById(int);
#include "client_packet_builder.h"
void __cdecl cm_AppendPacketFieldDelta(int, int, int, void*);
void __cdecl fcn_004c5360(void);
int __cdecl fcn_004e4ae0(char*, int);
void __cdecl fcn_004e4e90(char*);
void __cdecl fcn_004e4730(char*);
int __cdecl fcn_004e4470(char*);
int __cdecl cut_WaitForTimeoutOrInput(int, int, int);
int __cdecl cut_RandMod(int);
void __cdecl fcn_004e4b40(int, int, char*, int, int);
unsigned short __cdecl gm_RandomMod(int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
char* __cdecl io_AppendText(int, ...);
int __cdecl fcn_00472250(int, int, char*);
void __cdecl d2_SetBildArgument(int, int);
void __cdecl d2_SelectControl(int);
char* __cdecl fcn_00471f80(int);
int __cdecl fcn_005373e0(int, int);
void __cdecl fcn_00471e30(int);
void __cdecl fcn_004e48b0(void);
void __cdecl fcn_004e4610(int);
void __cdecl fcn_004e44f0(int);
void __cdecl fcn_004c09b0(void);
void __cdecl fcn_004e4b00(int);
void __cdecl fcn_004e4910(void);
void __cdecl fcn_004e3640(void);

char* __cdecl gm_LookupEntityRecordById(int);
float __cdecl fcn_004fef80(char*);

/* ADDRESS: GOLD 0x004e0e90 */
/* ADDRESS: GOLDTL 0x004e27b0 */
int __cdecl fcn_004e27b0(char* x)
{
	char buf[0x200];
	char* a;
	char* b;
	char* c;

	a = gm_LookupEntityRecordById(*(int*) (x + 0x34));
	b = gm_LookupEntityRecordById(*(int*) (x + 0x38));
	if (a == 0 || b == 0)
		return 0;
	c = gm_LookupEntityRecordById(*(int*) (a + 0x5c));
	if (c == 0 || c[2] == 0xf) {
		fcn_004c57e0(*(int*) (b + 4), 1);
		return 0;
	}
	if (a[2] == 6 || a[2] == 7) {
		io_FormatTextBuffer(buf, 0x11c1);
		strcat(buf, g_14a9a28);
		fcn_004e6240(a, x, buf, g_6b5c60);
	}
	return 1;
}

/* ADDRESS: GOLDTL 0x004e2890 */
void __cdecl fcn_004e2890(char* m)
{
	char buf[0x10];
	char* a;
	char* b;
	int snd;
	int esc;
	int n;
	int sc;
	int w;

	a = gm_LookupEntityRecordById(*(int*) (m + 0x34));
	b = gm_LookupEntityRecordById(*(int*) (m + 0x38));
	if (a == 0 || b == 0)
		return;
	{
		int v;

		v = 8;
		fcn_004c4510(b, *(int*) (b + 4));
		cm_AppendPacketFieldDelta(1, 1, 2, &v);
		fcn_004c5360();
	}
	cut_EventLoopFlags = 0x702c6;
	d2_SuppressOverlay = 1;
	snd = fcn_004e4ae0("GEBURT.sbf", 0);
	fcn_004e4e90("cd2\\Geburt.mp3");
	fcn_004e4730("Geburt.ed3");
	esc = fcn_004e4470("cutscenes\\geburt\\enter_Geburt.esc");
	if (cut_WaitForTimeoutOrInput(0x1964, 0, 0) == 0) {
		if (a[9] == 0) {
			if (b[9] == 0)
				fcn_004e4b40(-8, snd, "_GEBURT", cut_RandMod(2), 0);
			else
				fcn_004e4b40(-8, snd, "_GEBURT", cut_RandMod(2) + 2, 0);
		} else if (b[9] == 0) {
			fcn_004e4b40(-8, snd, "_GEBURT", cut_RandMod(2) + 4, 0);
		} else {
			fcn_004e4b40(-8, snd, "_GEBURT", cut_RandMod(2) + 6, 0);
		}
		if (cut_WaitForTimeoutOrInput(1000, 0, 0) == 0) {
			for (n = cut_RandMod(4) + 2; n > 0; n--)
				fcn_004e4b40(-8, snd, "_GEBURT_GESCHREI", cut_RandMod(5), gm_RandomMod(0x800) + 1000);
			cut_WaitForTimeoutOrInput(7000, 0, 0);
		}
	}
	sc = fcn_00470820(0, 0, "cutscenes\\geburt");
	d2_CenterDialogWindows(sc);
	d2_SetForm(sc, 1);
	if (b[9] == 0)
		io_AppendText(0x1aae);
	else
		io_AppendText(0x1aaf);
	d2_SetForm(sc, 2);
	w = fcn_00472250(sc, 2, io_AppendText((int) "$L%t", b + 0x30));
	d2_SetBildArgument(w, 0xf);
	d2_SelectControl(w);
	for (;;) {
		if (g_14cf950 == 0x1c || tp_d2_SelectedControl == 0) {
			strcpy(buf, fcn_00471f80(w));
			if (buf[0] != 0)
				break;
			d2_SelectControl(w);
		}
		if (fcn_005373e0(0, cut_EventLoopFlags) == 0 || g_7747f0 != 0)
			break;
	}
	fcn_004c4510(b, *(int*) (b + 4));
	cm_AppendPacketFieldDelta(1, 0x10, 0x30, buf);
	fcn_004c5360();
	fcn_00471e30(sc);
	fcn_004e48b0();
	fcn_004e4610(esc);
	fcn_004e44f0(esc);
	fcn_004c09b0();
	fcn_004e4b00(snd);
	g_772f54 = 0;
	fcn_004e4910();
	fcn_004e3640();
	d2_SuppressOverlay = 0;
}

/* ADDRESS: GOLDTL 0x004e2b40 */
int __cdecl fcn_004e2b40(char* m)
{
	if (fcn_004fef80(gm_LookupEntityRecordById(*(int*) (m + 0x34))) > 0.0f)
		return 0;
	return 1;
}
