

extern char g_6a4120[];
extern unsigned char g_77670a;
extern int g_7747b4;
extern int g_14ce8e0;
extern char g_14cf950;
#include "client_dialog_state.h"
extern int g_100f1dc;
extern int d2_CurrentElementId;

int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
int __cdecl fcn_00472250(int, int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl fcn_005373e0(int (__cdecl*)(void), int);
int __cdecl d2_CreateRadioGroup(int, ...);
void __cdecl d2_SelectRadioGroup(int, int);
void __cdecl d2_UpdateRadioGroup(int);
void __cdecl d2_ClearRadioGroup(int);
void __cdecl fcn_00471e30(int);

int __cdecl fcn_0053e9a0(void)
{
	int option1;
	int option2;
	int option3;
	int option4;
	int result;
	int h;
	int s;
	int option0;
	int list;

	result = 0;
	h = fcn_00470820(0, 0, g_6a4120);
	d2_CenterDialogWindows(h);
	g_7747b4 = g_77670a;
	s = io_AppendText(0x1abf);
	option0 = fcn_00472250(h, 0, s);
	option1 = fcn_00472250(h, 0, s + 1);
	option2 = fcn_00472250(h, 0, s + 2);
	option3 = fcn_00472250(h, 0, s + 3);
	option4 = fcn_00472250(h, 0, s + 4);
	list = d2_CreateRadioGroup(6, option0, option1, option2, option3, option4, fcn_00472250(h, 0, s + 5));
	d2_SelectRadioGroup(list, g_7747b4);
	while (fcn_005373e0(fcn_0053e9a0, 0xc6) != 0) {
		d2_UpdateRadioGroup(list);
		if (g_14ce8e0 != 0 || g_14cf950 == 1) {
			result = 0;
			g_774654 = 1;
		}
		if (g_100f1dc == 2 || g_14cf950 == 0x1c) {
			if (d2_CurrentElementId == option0) {
				g_7747b4 = 0;
			} else if (d2_CurrentElementId == option1) {
				g_7747b4 = 1;
			} else if (d2_CurrentElementId == option2) {
				g_7747b4 = 2;
			} else if (d2_CurrentElementId == option3) {
				g_7747b4 = 3;
			} else if (d2_CurrentElementId == option4) {
				g_7747b4 = 4;
			}
			result = 1;
			g_774654 = 1;
		} else if (g_100f1dc == 1) {
			g_774654 = 1;
		}
	}
	g_77670a = (unsigned char) g_7747b4;
	d2_ClearRadioGroup(list);
	fcn_00471e30(h);
	return result;
}
