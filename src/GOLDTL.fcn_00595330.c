extern char* g_99ec10;
extern char* g_1015ea0;

int __cdecl gm_GetBuildingTypeCategory(int);
void __cdecl fcn_004727a0(int, int);
int __cdecl fcn_0050cce0(char*, void*, int);
char* __cdecl fcn_005463a0(int, int, int, int, int);
char* __cdecl fcn_005462a0(void);
int __cdecl fcn_0046f100(int, int, int, int, int, int);
int __cdecl fcn_0046f740(int, int, int, int);
int __cdecl fcn_0046f7e0(int, int, int, int, int);
void __cdecl fcn_0046f9b0(int, int);
void __cdecl fcn_00472900(int, int);
void __cdecl fcn_0046b2b0(int);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_00500e20(int*);
int __cdecl fcn_0051e070(void);
char* __cdecl itoa(char*, int, int);

/* One stock row as produced by fcn_0050cce0. */
typedef struct Stock {
	int max;		/* 0x00 */
	int n;			/* 0x04 */
	int caps[16];		/* 0x08 */
	unsigned short ids[16];	/* 0x48 */
	int vals[16];		/* 0x68 */
	char pada8[0xc];	/* 0xa8 */
	char* store;		/* 0xb4 */
} Stock;

/* 16 building rows at 0x779160, stride 0x58. */
#define g_row(i) ((char*) (0x779160 + (i) * 0x58))
#define g_row_type(r) (*(int*) ((r) + 0x00))
#define g_row_cat(r, k) (*(int*) ((r) + 0x04 + (k) * 4))
#define g_row_val(r, k) (*(int*) ((r) + 0x14 + (k) * 4))
#define g_row_arg0(r) (*(int*) ((r) + 0x24))
#define g_row_arg1(r) (*(int*) ((r) + 0x28))
#define g_row_sel(r) (*(int*) ((r) + 0x2c))
#define g_row_handle(r) (*(int*) ((r) + 0x30))
#define g_row_sub(r) (*(int*) ((r) + 0x34))
#define g_row_extra(r) (*(int*) ((r) + 0x38))
#define g_row_item(r, k) (*(int*) ((r) + 0x3c + (k) * 4))
#define g_row_last(r) (*(int*) ((r) + 0x4c))

#define g_object(idx) (g_1015ea0 + (idx) * 0x2f4)
#define g_id_field(row, ofs) (*(unsigned short*) (g_99ec10 + g_row_type(row) * 0x41 + (ofs)))

/* ADDRESS: GOLDTL 0x00595330 */
void __cdecl fcn_00595330(int a0, int a1, int a2, int a3, int a4)
{
	char numbuf[32];
	char* slot;
	char* row;
	char* ent;
	char* found;
	Stock stock;
	int state;
	int status;
	int delta;
	int pick;
	int cnt;
	int idx;
	int key;
	int j;
	int i;

	ent = (char*) *(int*) 0x7746c4;
	if (ent == 0) {
		ent = (char*) *(int*) 0x7746c8;
	}
	gm_GetBuildingTypeCategory((unsigned char) *ent);
	fcn_004727a0(a0, 0);
	fcn_004727a0(a0, a1);
	fcn_0050cce0(ent, &stock, 1);

	if (a2 >= 1) {
		row = g_row(0);
		for (i = a2; i != 0; i--) {
			g_row_sel(row) = -1;
			if (*(int*) 0x7798a0) {
				for (j = 0; j < 4; j++) {
					if (g_row_cat(row, j) == *(int*) 0x7798a0) {
						g_row_sel(row) = j;
					}
				}
			}
			row += 0x58;
		}
	}

	for (i = 0; i < a2; i++) {
		row = g_row(i);
		status = 0;
		if (g_row_handle(row) <= -1) {
			idx = fcn_0046f100(g_row_arg0(row), g_row_arg1(row), 0xcd, 0x57, 0x10,
			                   *(int*) 0x772514);
			g_row_handle(row) = idx;
			*(int*) (idx * 0x3cc + 0x10161cc) = 0x54;
			fcn_0046f740(0, 0, 0x74c, idx);
			g_row_sub(row) = fcn_0046f740(0xd, 5, g_row_type(row) + 0xdf,
			                              g_row_handle(row));
			key = 0x26;
			delta = 0x11;
			slot = row + 0x3c;
			*(int*) (g_object(g_row_sub(row)) + 0x5c) = 1;
			*(int*) (g_object(g_row_sub(row)) + 0x1e8) = -1;
			*(int*) (g_object(g_row_sub(row)) + 0x1ec) = -1;
			do {
				if (*(int*) (slot - 0x38)) {
					idx = fcn_0046f7e0(delta, 0x3a, *(int*) (slot - 0x38) + 0xdf,
					                  g_row_handle(row), -2);
					*(int*) slot = idx;
					*(int*) (g_object(idx) + 0x5c) = 1;
					fcn_00472900(*(int*) slot, 0x54);
					itoa(numbuf, g_id_field(row, key), 10);
					fcn_0046f9b0(*(int*) slot, (int) numbuf);
					*(int*) (g_object(*(int*) slot) + 0x1dc) = -8;
					*(int*) (g_object(*(int*) slot) + 0x1e0) = 6;
					*(int*) (g_object(*(int*) slot) + 0x1e8) = -1;
					*(int*) (g_object(*(int*) slot) + 0x1ec) = -1;
				}
				key += 2;
				slot += 4;
				delta += 0x31;
			} while (key < 0x2e);
			idx = fcn_0046f100(0x43, 4, 0x88, 0x32, 0x10, g_row_handle(row));
			g_row_last(row) = idx;
			*(int*) (idx * 0x3cc + 0x10161cc) = 0x54;
		}

		delta = 0;
		pick = 0;
		key = 0x26;
		status = 0;
		cnt = 0;
		slot = row + 0x3c;
		do {
			if (*(int*) (slot - 0x38)) {
				j = -1;
				if (stock.n >= 1) {
					for (idx = 0; idx < stock.n; idx++) {
						if ((unsigned int) stock.ids[idx] == (unsigned int) *(int*) (slot - 0x38)) {
							j = idx;
							break;
						}
					}
				}
				if (j >= 0 && j < stock.n) {
					if ((int) g_id_field(row, key) <= stock.vals[j]) {
						*(int*) (g_object(*(int*) slot) + 0x1e4) = 0x74d;
						pick = delta;
					} else {
						*(int*) (g_object(*(int*) slot) + 0x1e4) = 0x74e;
						if (status <= 1) {
							status = 1;
						}
						delta = (unsigned int) g_id_field(row, key) - stock.vals[j];
						pick = delta;
					}
				} else {
					status = 2;
					*(int*) (g_object(*(int*) slot) + 0x1e4) = 0x74f;
					if (g_row_sel(row) == cnt) {
						delta = (unsigned int) g_id_field(row, key);
						pick = delta;
					}
				}
			}
			key += 2;
			cnt++;
			slot += 4;
		} while (key < 0x2e);
		*(int*) (g_object(g_row_sub(row)) + 0x1e4) = status + 0x750;

		found = fcn_005463a0(2, 0, 4, 3, *(unsigned int*) (ent + 1));
		while (found != 0) {
			if ((unsigned int) *(unsigned short*) (found + 0xac) == (unsigned int) g_row_type(row)) {
				break;
			}
			found = fcn_005462a0();
		}
		if (found == 0) {
			found = fcn_005463a0(2, 0, 3, 3, *(unsigned int*) (ent + 1));
			while (found != 0) {
				if ((unsigned int) *(unsigned short*) (found + 0xac) == (unsigned int) g_row_type(row)) {
					break;
				}
				found = fcn_005462a0();
			}
		}

		if (found != 0 && (*(int*) (found + 0x14) || *(int*) (found + 0x18))) {
			state = 0;
			idx = fcn_00500e20((int*) 0x7f4c00);
			key = *(int*) 0x7f4c04 & 0xffff;
			if (!((float) key < *(float*) (idx * 4 + 0x696540)
			      || *(float*) (idx * 4 + 0x696550) <= (float) key)) {
				if (*found == 4) {
					if (*(int*) (found + 0xc8) == 0) {
						state = 0x4fc;
					} else {
						state = 0x50b;
					}
				} else if (*found == 3) {
					state = 0x50c;
				}
			} else {
				if (*found == 4) {
					state = 0x50b;
				} else if (*found == 3) {
					state = 0x50c;
				}
			}
			if (g_row_extra(row) >= 0
			    && *(int*) (g_object(g_row_extra(row)) + 8) != state) {
				fcn_0046b2b0(g_row_extra(row));
				g_row_extra(row) = -1;
			}
			if (g_row_extra(row) <= -1) {
				g_row_extra(row) = fcn_0046f740(0xd, 5, state, g_row_handle(row));
			}
			delta = *(int*) (found + 0x18) + *(int*) (found + 0x14);
			if (*found != 4) {
				if (*found == 3) {
					*(float*) (g_object(g_row_sub(row)) + 0x1f4) =
						-(float) *(int*) (found + 0xb0) / *(float*) (found + 0xb4);
				}
			} else {
				*(float*) (g_object(g_row_sub(row)) + 0x1f4) =
					-*(float*) (found + 0xb4) / *(float*) (found + 0xb8);
			}
		} else {
			if (g_row_extra(row) != -1) {
				fcn_0046b2b0(g_row_extra(row));
				g_row_extra(row) = -1;
			}
			if (g_row_sub(row) != -1) {
				*(float*) (g_object(g_row_sub(row)) + 0x1f4) = 0.0f;
			}
			idx = 0;
		}

		slot = row + 0x3c;
		for (j = 4; j != 0; j--) {
			if (*(int*) (slot - 0x38)) {
				*(int*) (g_object(*(int*) slot) + 0x3c) = 0;
			}
			slot += 4;
		}

		key = g_row_sel(row);
		if (key <= -1) {
			*(int*) 0x772514 = g_row_last(row);
			if (a4 != 0) {
				if (a4 != 1) {
					fcn_00519190(0x6aa164, delta, 0x51e, 0xbb, g_row_type(row) * 2 + 0x9a8);
				} else {
					fcn_00519190(0x6aa17c, delta, 0x51e, 0xba, g_row_type(row) * 2 + 0x9a8);
				}
			} else {
				fcn_00519190(0x6aa194, delta, 0x51e, 0xb8, g_row_type(row) * 2 + 0x9a8);
			}
		} else if (pick != 0) {
			*(int*) (g_object(g_row_item(row, key)) + 0x3c) = 1;
			*(int*) 0x772514 = g_row_last(row);
			if (g_id_field(row, 0x36) == 1) {
				j = fcn_0051e070();
				if (j == 0) {
					fcn_00519190(0xc1, (unsigned int) g_id_field(row, 0x36),
					             g_row_type(row) * 2 + 0x9a8);
				} else if (j == 1) {
					fcn_00519190(0xc1, g_row_type(row) * 2 + 0x9a8,
					             (unsigned int) g_id_field(row, 0x36));
				}
			} else {
				j = fcn_0051e070();
				if (j == 0) {
					fcn_00519190(0xc2, g_row_type(row) * 2 + 0x9a8,
					             (unsigned int) g_id_field(row, 0x36));
				} else if (j == 1) {
					fcn_00519190(0xc2, (unsigned int) g_id_field(row, 0x36),
					             g_row_type(row) * 2 + 0x9a8);
				}
			}
			state = g_row_val(row, key);
			if (state == 1) {
				fcn_00519190(0xc3, pick, g_row_cat(row, key) * 2 + 0x9a8);
			} else {
				fcn_00519190(0xc4, state, g_row_cat(row, key) * 2 + 0x9a8);
			}
			if (pick == 1) {
				fcn_00519190(0xc5);
			} else {
				fcn_00519190(0xc6, pick);
			}
		} else {
			pick = 1;
			*(int*) (g_object(g_row_item(row, key)) + 0x3c) = 1;
			*(int*) 0x772514 = g_row_last(row);
			if (g_id_field(row, 0x36) == 1) {
				j = fcn_0051e070();
				if (j == 0) {
					fcn_00519190(0xc1, (unsigned int) g_id_field(row, 0x36),
					             g_row_type(row) * 2 + 0x9a8);
				} else if (j == 1) {
					fcn_00519190(0xc1, g_row_type(row) * 2 + 0x9a8,
					             (unsigned int) g_id_field(row, 0x36));
				}
			} else {
				j = fcn_0051e070();
				if (j == 0) {
					fcn_00519190(0xc2, g_row_type(row) * 2 + 0x9a8,
					             (unsigned int) g_id_field(row, 0x36));
				} else if (j == 1) {
					fcn_00519190(0xc2, (unsigned int) g_id_field(row, 0x36),
					             g_row_type(row) * 2 + 0x9a8);
				}
			}
			state = g_row_val(row, key);
			if (state == 1) {
				fcn_00519190(0xc3, pick, g_row_cat(row, key) * 2 + 0x9a8);
			} else {
				fcn_00519190(0xc4, state, g_row_cat(row, key) * 2 + 0x9a8);
			}
			if (pick == 1) {
				fcn_00519190(0xc5);
			} else {
				fcn_00519190(0xc6, pick);
			}
		}

		fcn_004727a0(a0, a1);
	}

	if (i >= 0x10) {
		return;
	}
	for (; i < 0x10; i++) {
		row = g_row(i);
		if (g_row_handle(row) >= 0) {
			g_row_sel(row) = -1;
			fcn_0046b2b0(g_row_handle(row));
			g_row_handle(row) = -1;
			g_row_sub(row) = -1;
			g_row_extra(row) = -1;
			g_row_item(row, 0) = -1;
			g_row_item(row, 1) = -1;
			g_row_item(row, 2) = -1;
			g_row_item(row, 3) = -1;
			g_row_last(row) = -1;
		}
	}
}
