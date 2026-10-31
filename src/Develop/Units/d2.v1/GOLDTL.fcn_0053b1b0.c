#include <string.h>

extern int g_772514;
extern char* g_77255c;
extern char* g_1015ea0;
extern int g_100f1dc;
extern int g_774654;
extern int g_14ce8e0;
extern char g_14cf950;
extern int g_67d370;

extern char s_6a3bd4[];
extern char s_6a3bcc[];
extern char s_6a3bc4[];

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_00471e30(int);
int __cdecl fcn_00472250(int, int, int);
void __cdecl fcn_00472640(int, int);
int __cdecl d2_SetForm(int, int);
int __cdecl fcn_0046f740(int, int, int, int);
int __cdecl io_AppendText(int, ...);
void __cdecl fcn_005340f0(int);
void __cdecl fcn_00534160(int, int, int, int);
int __cdecl fcn_005373e0(void*, int);

/* ADDRESS: GOLDTL 0x0053b1b0 */
int __cdecl fcn_0053b1b0(void)
{
	int v_len;
	int v_id;
	int v_first;
	int dlg;
	int v_ret;
	int id;
	int st[11];
	int ids[14];
	int i;
	int j;
	int y;

	v_ret = 0;
	memset((void*) 0x7e1fd8, 0, 24);
	v_first = 1;
	memcpy(st, (void*) 0x7e1fc0, 44);
	v_len = 0x7e;
	v_id = -1;
	for (i = 4; i < 6; i++) {
		if (i < 4)
			st[6 + st[i]] = (int) (st[6 + st[i]] + 21.0f);
		else
			st[6 + st[i]] = (int) (st[6 + st[i]] + 63.0);
	}
	memcpy((void*) 0x7e1fc0, st, 44);
	dlg = fcn_00470820(0, 0, s_6a3bd4);
	fcn_00471b60(dlg);
	d2_SetForm(dlg, 0);
	fcn_005340f0(g_772514);
	d2_SetForm(dlg, 2);
	io_AppendText(0x1ae2);
	if (fcn_005373e0((void*) fcn_0053b1b0, 0x12d6) != 0) {
		do {
			if (g_14ce8e0 != 0)
				g_774654 = 1;
			if (v_first != 0) {
				d2_SetForm(dlg, 1);
				io_AppendText((int) s_6a3bcc);
				y = 0x1c;
				for (i = 0; y < 0xd5; i++, y += 0x25) {
					io_AppendText((int) s_6a3bc4, i + 0x16b7);
					fcn_00534160(0xd2, y, st[6 + i], 0x4d9);
					id = fcn_0046f740(*(int*) (g_77255c + 0xc) - 0x2c, y, 0x519, g_772514);
					ids[2 * i] = id;
					*(int*) (g_1015ea0 + id * 0x2f4 + 0x5c) = 1;
					*(int*) (g_1015ea0 + id * 0x2f4 + 0x1d0) = 3;
					id = fcn_0046f740(*(int*) (g_77255c + 0xc) - 0x18, y, 0x51a, g_772514);
					ids[2 * i + 1] = id;
					*(int*) (g_1015ea0 + id * 0x2f4 + 0x5c) = 1;
					*(int*) (g_1015ea0 + id * 0x2f4 + 0x1d0) = 3;
				}
				io_AppendText(0x1ae3);
				fcn_00534160(0xd2, 0xec, v_len, 0x4d9);
				v_id = fcn_00472250(dlg, 1, io_AppendText(0x1ae4));
				j = 0;
				for (i = 0; i < 0x14; i += 4) {
					if (*(int*) ((char*) st + 0x18 + i) > *(int*) ((char*) 0x7e1fd8 + i))
						j = 0;
					else
						j = 1;
					id = *(int*) ((char*) ids + i);
					*(int*) (g_1015ea0 + id * 0x2f4 + 0x4c) = j;
					*(int*) (g_1015ea0 + id * 0x2f4 + 0x60) = j;
					if (v_len > 0 && *(int*) ((char*) st + 0x18 + i) < 126.0f)
						j = 0;
					else
						j = 1;
					id = *(int*) ((char*) ids + i + 4);
					*(int*) (g_1015ea0 + id * 0x2f4 + 0x4c) = j;
					*(int*) (g_1015ea0 + id * 0x2f4 + 0x60) = j;
				}
				v_first = 0;
			}
			if (v_len != 0)
				fcn_00472640(v_id, 0);
			else
				fcn_00472640(v_id, 1);
			if (g_100f1dc != -1) {
				if (g_100f1dc == 2 || g_14cf950 == 0x1c) {
					v_ret = 1;
					for (i = 0; i < 5; i++)
						((char*) 0x7e2430)[i] = (char) st[6 + i];
					switch (st[4]) {
					case 0:
						*(char*) 0x7e23e0 = 0x1c;
						break;
					case 1:
						*(char*) 0x7e23e0 = 0x31;
						break;
					case 2:
						*(char*) 0x7e23e0 = 4;
						break;
					case 3:
						*(char*) 0x7e23e0 = 0x37;
						break;
					case 4:
						*(char*) 0x7e23e0 = 0x10;
						break;
					}
					switch (st[5]) {
					case 0:
						*(char*) 0x7e23e1 = 0x1c;
						break;
					case 1:
						*(char*) 0x7e23e1 = 0x25;
						break;
					case 2:
						*(char*) 0x7e23e1 = 4;
						break;
					case 3:
						*(char*) 0x7e23e1 = 0;
						break;
					case 4:
						*(char*) 0x7e23e1 = 0x49;
						break;
					}
					memcpy((void*) 0x7e1fc0, st, 44);
					g_774654 = 1;
				} else if (g_100f1dc == 1) {
					g_774654 = 1;
					continue;
				}
				if (g_100f1dc == 0x519 || g_100f1dc == 0x51a) {
					v_first = 1;
					for (j = 0; j < 0xc; j++) {
						if (g_67d370 != ids[j])
							continue;
						if (j % 2 != 0) {
							if (v_len > 0) {
								st[6 + j / 2] = (int) (st[6 + j / 2] + 21.0f);
								v_len = (int) (v_len - 21.0f);
							}
						} else if (st[6 + j / 2] > ((int*) 0x7e1fd8)[j / 2]) {
							st[6 + j / 2] = (int) (st[6 + j / 2] - 21.0f);
							v_len = (int) (v_len + 21.0f);
						}
					}
				}
			}
		} while (fcn_005373e0((void*) fcn_0053b1b0, 0x12d6) != 0);
	}
	fcn_00471e30(dlg);
	return v_ret;
}
