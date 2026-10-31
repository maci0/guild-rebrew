extern char* lpGebaeudePROT;
extern int g_7746c4;
extern int g_7746c8;
extern int g_774970;
extern int g_100f1dc;
extern int g_14ce8e0;
extern int g_774654;
extern int g_67d370;
extern int g_14abaac;
extern char* g_6aa4d8;

int __cdecl fcn_0055c050(char* obj);
void* __cdecl fcn_00502cd0(int container_id, int arg_count, ...);
void* __cdecl gm_NextEntityQueryMatch(void);
void* __cdecl fcn_005463a0(int a, int b, int c, int d, int e);
void* __cdecl he_fn_Handlung(void);
void __cdecl io_FormatTextBuffer(char* buf, int id, ...);
void __cdecl fcn_00526120(char* buf, int flag);
int __cdecl fcn_00470820(int a, int b, char* name);
void __cdecl fcn_00471b60(int dlg);
void __cdecl d2_SetOverlayAnimation(int a, int b);
void __cdecl d2_SetForm(int dlg, int flag);
int __cdecl io_AppendText(int id, ...);
int __cdecl fcn_00472250(int dlg, int a, int b);
void __cdecl fcn_004c5530(int a1);
void __cdecl fcn_004c35f0(void);
void __cdecl fcn_0052ae70(void);
int __cdecl fcn_005373e0(int a, int b);
void __cdecl fcn_00471e30(int dlg);

/* ADDRESS: GOLDTL 0x0059d6b0 */
void __cdecl fcn_0059d6b0(unsigned int id, char* obj)
{
	char msg[0x400];
	char* list[16];
	char msg2[0x100];
	unsigned int slots[8];
	char packet[4];
	unsigned int count;
	int entity;
	int other;
	int index;
	int choice;
	int option;
	int i;

	count = 0;
	if (obj == 0) {
		return;
	}
	if (*(unsigned short*) (obj + 0x27) == 0xffff) {
		return;
	}
	if (fcn_0055c050(obj) == 0) {
		io_FormatTextBuffer(msg, 0x1a92, *(unsigned short*) (obj + 0x27), obj);
		fcn_00526120(msg, 0);
		return;
	}
	count = 0;
	entity = g_7746c4;
	if (g_7746c4 != 0 || (entity = g_7746c8) != 0) {
		other = (int) fcn_00502cd0(*(int*) (entity + 0x5d), 1, 0, 0xca);
		while (other != 0) {
			if (*(int*) (other + 0x2a) != *(int*) (obj + 1)) {
				list[count] = (char*) other;
				count++;
			}
			other = (int) gm_NextEntityQueryMatch();
		}
	}
	other = (int) fcn_005463a0(2, 2, g_774970, 0, 0x40);
	while (other != 0) {
		for (index = 0; index < count; index++) {
			if (*(int*) (other + 0xac) == *(int*) (list[index] + 0x2a)) {
				break;
			}
		}
		if (index == count) {
			count++;
		}
		other = (int) he_fn_Handlung();
	}
	if ((*(unsigned char*) (lpGebaeudePROT + id * 0x24d + 0x247) * 2) <= count) {
		io_FormatTextBuffer(msg2, 0x19fa, count, g_7746c8);
		fcn_00526120(msg2, 0);
		return;
	}
	choice = *(unsigned short*) (obj + 0x27);
	option = fcn_00470820(0, 0, g_6aa4d8);
	fcn_00471b60(option);
	d2_SetOverlayAnimation(0, 0);
	d2_SetForm(option, 1);
	index = io_AppendText(0x19f7, *(unsigned short*) (choice * 0x21c + 0x7f4ca0), obj);
	other = fcn_00472250(option, 1, index);
	index = fcn_00472250(option, 1, index + 1);
	g_100f1dc = -1;
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (g_100f1dc != -1) {
			if (g_67d370 != other) {
				if (g_67d370 == index) {
					g_774654 = 1;
				}
			}
			else {
				for (i = 0; i < 8; i++) {
					slots[i] = 0xffffffff;
				}
				packet[0] = 0x40;
				packet[2] = 1;
				i = 0;
				for (entity = 0x7f4ca4; entity < 0x85a0a4 && i < 8; entity += 0x21c) {
					if (*(char*) (entity + 0x184) != 0) {
						slots[i] = *(unsigned int*) entity;
						i++;
					}
				}
				if (i != 0) {
					fcn_004c5530(*(int*) packet);
					fcn_004c35f0();
					fcn_0052ae70();
					g_774654 = 1;
				}
				else {
					fcn_00526120((char*) g_14abaac, 0);
					g_774654 = 1;
				}
			}
		}
	} while (fcn_005373e0(0x59d6b0, 0x677c7));
	fcn_00471e30(option);
}
