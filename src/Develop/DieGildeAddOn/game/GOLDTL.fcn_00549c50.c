char *__cdecl gm_LookupEntityRecordById(int);
void __cdecl io_FormatTextBuffer(char *, int, ...);
void __cdecl he_MessageBoxQuickjump(int, int, char *, int, int, int, int, int, char *);
float __cdecl fcn_0050bb50(int, unsigned char);
void __cdecl fcn_004c51a0(int, int, int, int);
void __cdecl fcn_004c54c0(int, int, int, int);

extern char g_6b5c60[];
extern unsigned char g_773d75;

/* ADDRESS: GOLDTL 0x00549c50 */
void __cdecl fcn_00549c50(int cmd, int obj, int arr, int id, int extra)
{
	char text1[0x400];
	char text2[0x100];
	char text3[0x100];
	char *found[4];
	int type_off;
	int n;
	int i;
	int j;
	int step;
	int total;
	float fh;
	float fy;

	n = 0;
	type_off = *(unsigned short *) (obj + 0x27) * 0x21c;
	for (i = 0; i < 4; i++) {
		char *e;

		e = gm_LookupEntityRecordById(*(int *) (arr + 0x1c + i * 4));
		if (e != 0) {
			found[n] = e;
			n++;
		}
	}
	if ((unsigned int) cmd < 0x6a6f696fu) {
		if (cmd == 0x6a6f696e) {
			char *e;

			e = gm_LookupEntityRecordById(id);
			if (e != 0) {
				io_FormatTextBuffer(text1, 0x189b, obj, *(unsigned short *) e);
				for (i = 0; i < n; i++) {
					if (found[i][2] == 6 || found[i][2] == 7) {
						he_MessageBoxQuickjump(*(int *) (found[i] + 4), -1, text1, 0, 0x5ec,
							*(int *) (obj + 1), -1, 0, g_6b5c60);
					}
				}
				if (*(char *) (type_off + 0x7f4ca2) == 6 || *(char *) (type_off + 0x7f4ca2) == 7) {
					if (n == 3) {
						io_FormatTextBuffer(text2, 0x1894, obj, *(unsigned short *) e);
						io_FormatTextBuffer(text3, 0x1896);
						io_FormatTextBuffer(text1, "%s%s", text2, text3);
					} else {
						io_FormatTextBuffer(text1, 0x1894, obj, *(unsigned short *) e);
					}
					he_MessageBoxQuickjump(*(int *) (type_off + 0x7f4ca4), -1, text1, 0, 0x5ec,
						*(int *) (obj + 1), -1, 0, g_6b5c60);
					return;
				}
			}
		} else if (cmd == 0x636c6572) {
			io_FormatTextBuffer(text1, 0x189d, obj);
			for (i = 0; i < n; i++) {
				if (found[i][2] == 6 || found[i][2] == 7) {
					he_MessageBoxQuickjump(*(int *) (found[i] + 4), -1, text1, 0, 0x5ec,
						*(int *) (obj + 1), -1, 0, g_6b5c60);
				}
			}
			return;
		} else if (cmd == 0x65786563) {
			char *e;

			fh = fcn_0050bb50(0x17a, g_773d75);
			fy = fcn_0050bb50(0x179, g_773d75);
			step = (int) (fh + fy);
			total = 0;
			io_FormatTextBuffer(text1, 0x189a, obj, step);
			if (n > 0) {
				total = step * n;
				for (i = 0; i < n; i++) {
					e = found[i];
					fcn_004c51a0(*(int *) (type_off + 0x7f4ca4), *(int *) (e + 4), g_773d75, step);
					if (e[2] == 6 || e[2] == 7) {
						he_MessageBoxQuickjump(*(int *) (e + 4), -1, text1, 0, 0x5ec,
							*(int *) (obj + 1), -1, 0, g_6b5c60);
					}
					fcn_004c54c0(*(int *) (type_off + 0x7f4ca4), *(int *) (e + 4), 3, 1);
					fcn_004c54c0(*(int *) (e + 4), *(int *) (type_off + 0x7f4ca4), 3, 1);
				}
			}
			if (*(char *) (type_off + 0x7f4ca2) == 6 || *(char *) (type_off + 0x7f4ca2) == 7) {
				io_FormatTextBuffer(text1, 0x1893, obj, total);
				he_MessageBoxQuickjump(*(int *) (type_off + 0x7f4ca4), -1, text1, 0, 0x5ec,
					*(int *) (obj + 1), -1, 0, g_6b5c60);
			}
			if (n > 0) {
				for (i = 0; i < n; i++) {
					for (j = 0; j < n; j++) {
						if (i != j) {
							fcn_004c54c0(*(int *) (found[i] + 4), *(int *) (found[j] + 4), 3, 1);
							fcn_004c54c0(*(int *) (found[j] + 4), *(int *) (found[i] + 4), 3, 1);
						}
					}
				}
				return;
			}
		}
	} else if (cmd == 0x6c656176) {
		char *e;

		e = gm_LookupEntityRecordById(id);
		if (e != 0) {
			io_FormatTextBuffer(text1, 0x189c, obj, *(unsigned short *) e);
			for (i = 0; i < n; i++) {
				if ((found[i][2] == 6 || found[i][2] == 7) &&
				    *(int *) (found[i] + 4) != *(int *) (e + 4)) {
					he_MessageBoxQuickjump(*(int *) (found[i] + 4), -1, text1, 0, 0x5ec,
						*(int *) (obj + 1), -1, 0, g_6b5c60);
				}
			}
			if (*(char *) (type_off + 0x7f4ca2) == 6 || *(char *) (type_off + 0x7f4ca2) == 7) {
				if (n == 1) {
					io_FormatTextBuffer(text3, 0x1895, obj, *(unsigned short *) e);
					io_FormatTextBuffer(text2, 0x1897);
					io_FormatTextBuffer(text1, "%s%s", text3, text2);
				} else {
					io_FormatTextBuffer(text1, 0x1895, obj, *(unsigned short *) e);
				}
				he_MessageBoxQuickjump(*(int *) (type_off + 0x7f4ca4), -1, text1, 0, 0x5ec,
					*(int *) (obj + 1), -1, 0, g_6b5c60);
			}
			if (n == 4) {
				int *p;

				io_FormatTextBuffer(text1, 0x1899, obj);
				p = (int *) 0x7f4ca4;
				do {
					if ((*(char *) ((int) p - 2) == 6 || *(char *) ((int) p - 2) == 7) &&
					    *p != *(int *) (type_off + 0x7f4ca4)) {
						for (i = 0; i < 4; i++) {
							if (*p == *(int *) (found[i] + 4)) {
								if (i < 4) {
									he_MessageBoxQuickjump(*p, -1, text1, 0, 0x5ec,
										*(int *) (obj + 1), -1, 0, g_6b5c60);
								}
								break;
							}
						}
					}
					p = (int *) ((int) p + 0x87 * 4);
				} while ((int) p < 0x85a0a4);
			}
		}
	} else if (cmd == 0x6e657720) {
		int *p;

		io_FormatTextBuffer(text1, 0x1898, obj);
		p = (int *) 0x7f4ca4;
		do {
			if ((*(char *) ((int) p - 2) == 6 || *(char *) ((int) p - 2) == 7) &&
			    *p != *(int *) (type_off + 0x7f4ca4)) {
				he_MessageBoxQuickjump(*p, -1, text1, 0, 0x5ec, *(int *) (obj + 1), -1, 0, g_6b5c60);
			}
			p = (int *) ((int) p + 0x87 * 4);
		} while ((int) p < 0x85a0a4);
		return;
	}
	return;
}
