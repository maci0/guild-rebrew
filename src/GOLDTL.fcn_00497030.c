extern char* g_99ec10;
extern char* g_entity_type_table;
extern unsigned char g_773d75;
extern float g_6628a8;

unsigned short* __cdecl fcn_00502cd0(int, int, ...);
char* __cdecl gm_FindRecordById(unsigned int);
char* __cdecl gm_SearchTable67(unsigned int);
char* __cdecl fcn_00508e40(int);
short* __cdecl fcn_0050d430(short*);
int __cdecl fcn_0050d320(char*, char);
float __cdecl fcn_0050bb50(int, unsigned char);

/* ADDRESS: GOLDTL 0x00497030 */
unsigned char __cdecl fcn_00497030(int a0, int a1, int a2, char* a3, char* a4)
{
	char* rec;
	unsigned char* ent;
	unsigned char* tbl;
	char* row;
	unsigned int id;
	unsigned char kind;
	int i;
	int cnt;
	int v28;

	if (a2 != 1) {
		goto fail;
	}
	if (*a3 != 2) {
		goto fail;
	}
	id = *(unsigned int*) (a3 + 4);
	if (*(g_99ec10 + id * 0x40 + id + 0x40) != 0) {
		goto fail;
	}
	if (*(g_99ec10 + id * 0x40 + id) == 2) {
		goto fail;
	}
	ent = 0;
	rec = 0;
	v28 = 0;
	if (*a4 == 1) {
		rec = (char*) gm_FindRecordById(*(unsigned int*) (a4 + 4));
		if (rec == 0) {
			goto fail;
		}
		kind = *(g_99ec10 + (unsigned int) *(unsigned short*) rec * 0x40 + *(unsigned short*) rec);
		if (kind != 2 && kind != 6) {
			goto done;
		}
		if (fcn_00502cd0(*(int*) (rec + 0x14), 1, 0, *(unsigned int*) (a3 + 4)) != 0) {
			goto fail;
		}
		ent = (unsigned char*) gm_SearchTable67(*(unsigned int*) (rec + 6));
		if (ent == 0) {
			goto fail;
		}
		tbl = (unsigned char*) g_entity_type_table + (unsigned int) *ent * 0x24d;
		cnt = *(unsigned char*) (tbl + 0x22);
		i = 0;
		if (cnt > 0) {
			do {
				if ((*(unsigned short*) (tbl + 0x23 + i * 2) & 0x7fff) == *(unsigned short*) rec) {
					break;
				}
				i++;
			} while (i < cnt);
		}
		if (cnt <= i) {
			goto fail;
		}
		i++;
		if (cnt <= i) {
			goto fail;
		}
		do {
			if ((*(unsigned short*) (tbl + 0x23 + i * 2) & 0x7fff) == *(unsigned int*) (a3 + 4)) {
				break;
			}
			i++;
		} while (i < cnt);
		if (cnt <= i) {
			goto fail;
		}
		if (*(unsigned short*) (tbl + i * 4 + 0xa3) != 0) {
			if (fcn_00502cd0(*(int*) (rec + 0x14), 1, 0, (unsigned int) *(unsigned short*) (tbl + i * 4 + 0xa3)) == 0) {
				goto fail;
			}
		}
		if (*(unsigned short*) (tbl + i * 4 + 0xa5) != 0) {
			if (fcn_00502cd0(*(int*) (rec + 0x14), 1, 0, (unsigned int) *(unsigned short*) (tbl + i * 4 + 0xa5)) == 0) {
				goto fail;
			}
		}
	} else if (*a4 == 4) {
		ent = (unsigned char*) gm_SearchTable67(*(unsigned int*) (a4 + 4));
		if (ent == 0) {
			goto fail;
		}
		if (fcn_00502cd0(*(int*) (ent + 0x5d), 1, 0, *(unsigned int*) (a3 + 4)) != 0) {
			goto fail;
		}
		tbl = (unsigned char*) g_entity_type_table + (unsigned int) *ent * 0x24d;
		cnt = *(unsigned char*) (tbl + 0x22);
		i = 0;
		if (cnt > 0) {
			do {
				if ((*(unsigned short*) (tbl + 0x23 + i * 2) & 0x7fff) == *(unsigned int*) (a3 + 4)) {
					break;
				}
				i++;
			} while (i < cnt);
		}
		if (cnt <= i) {
			goto fail;
		}
		if (*(unsigned short*) (tbl + i * 4 + 0xa3) != 0) {
			if (fcn_00502cd0(*(int*) (ent + 0x5d), 1, 0, (unsigned int) *(unsigned short*) (tbl + i * 4 + 0xa3)) == 0) {
				goto fail;
			}
		}
		if (*(unsigned short*) (tbl + i * 4 + 0xa5) != 0) {
			if (fcn_00502cd0(*(int*) (ent + 0x5d), 1, 0, (unsigned int) *(unsigned short*) (tbl + i * 4 + 0xa5)) == 0) {
				goto fail;
			}
		}
	} else if (*a4 == 7) {
		v28 = (int) fcn_00508e40(*(unsigned int*) (a4 + 4));
		if (v28 == 0) {
			goto fail;
		}
	} else {
		goto fail;
	}
done:
	if (a0 == 0x39) {
		i = *(int*) (a4 + 0x10);
		*(int*) (a3 + 0x10) = 0x39;
	} else {
		if (rec != 0) {
			v28 = (int) fcn_0050d430((short*) rec);
		} else if (ent != 0) {
			if (*(unsigned short*) (ent + 0x27) == 0xffff) {
				goto fail;
			}
			v28 = (unsigned int) *(unsigned short*) (ent + 0x27) * 0x21c + 0x7f4ca0;
		} else if (v28 == 0) {
			goto fail;
		}
		if (v28 == 0) {
			goto fail;
		}
		i = fcn_0050d320((char*) v28, g_773d75);
		*(int*) (a3 + 0x10) = 0;
	}
	if (g_6628a8 < *(float*) (a3 + 0x14) && *(float*) (a3 + 0x14) < 1.0f) {
		i = (int) ((float) i * *(float*) (a3 + 0x14));
	}
	row = a3 + 4;
	return (unsigned char) (((i < (int) fcn_0050bb50(*(int*) row, g_773d75)) - 1U) & 0xb);

fail:
	return 0;
}
