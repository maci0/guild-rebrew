char* __cdecl fcn_00503fe0(int a, int b, int c);
char* __cdecl gm_LookupEntityRecordById(int id);
void __cdecl fcn_004c5c80(int id);
void __cdecl fcn_004c5da0(int a, int b, int c, int d, int e, char* label);
int __cdecl fcn_00529160(int a, int b, int c, int d);
int __cdecl fcn_00500bb0(char* sel, int a, int b, int c);
int __cdecl fcn_0050c710(char* e, int a, int b);
char* __cdecl fcn_00502cd0(int a, int b, int c, int d);
char* __cdecl fcn_00502850(void);
int __cdecl fcn_0042e410(int code);
int __cdecl io_FormatTextBuffer(char* buf, int fmt, ...);
int __cdecl fcn_00545e80(int a, int b, char* s, int c, int d, int e, int f,
    int g, int h);
int __cdecl fcn_004c5980(void* p);
void __cdecl fcn_004c5a60(int a, int b, int c);
int __cdecl fcn_004c4450(int h);
int* __cdecl fcn_004c4480(int h);
int __cdecl fcn_004e6a30(int h);
char* __cdecl fcn_00504b30(char* p);
void __cdecl fcn_00546190(char* e);
int __cdecl fcn_004d5450(char* e);
int __cdecl fcn_004d5110(char* a, char* b, char* c, char* d);
int __cdecl memset(void* dst, int c, unsigned int n);

/* ADDRESS: GOLDTL 0x0056bfd0 */
void __cdecl fcn_0056bfd0(char* ent)
{
	int count;
	float value;
	float prob;
	int slot;
	int rnd;
	char* e2;
	char* target;
	int i;
	int j;
	unsigned char msg[0x114];
	char text[0x400];
	char text2[0x3f0];

	count = 0;
	value = 1.0f;
	switch (*(int*) (ent + 0x70)) {
	case 0:
		e2 = fcn_00503fe0(*(int*) (ent + 0xb0), 1, 1);
		target = fcn_00503fe0(*(int*) (ent + 0xac), 1, 1);
		if (e2 != 0 && target != 0) {
			count = 8;
			do {
				j = *(int*) (ent + 0x8c + (8 - count) * 4);
				if (j != -1) {
					slot = (int) gm_LookupEntityRecordById(j);
					fcn_004c5c80(j);
					fcn_004c5da0(j, *(int*) (e2 + 1),
					    -1, 0, 0, (char*) 0x6a6aac);
					fcn_00529160((int) e2, 0,
					    *(unsigned short*) slot,
					    (int) ent);
				}
				count--;
			} while (count != 0);
			*(int*) (ent + 0x52) = *(int*) 0x7f4c00;
			*(int*) (ent + 0x56) = *(int*) 0x7f4c04;
			*(int*) (ent + 0x5a) = *(int*) 0x7f4c08;
			*(short*) (ent + 0x5e) = *(short*) 0x7f4c0c;
			fcn_00500bb0(ent + 0x52, 0, 10, 0);
			*(int*) (ent + 0x70) = 1;
			return;
		}
		break;
	case 1:
		for (i = 0; i < 8; i++) {
			j = *(int*) (ent + 0x8c + i * 4);
			if (j != -1) {
				target = gm_LookupEntityRecordById(j);
				if (*(int*) (target + 0x184) != 0
				    && *(int*) (*(int*) (target + 0x184) + 0x128)
				    != 0) {
					*(int*) (ent + 0x52) =
					    *(int*) 0x7f4c00;
					*(int*) (ent + 0x56) =
					    *(int*) 0x7f4c04;
					*(int*) (ent + 0x5a) =
					    *(int*) 0x7f4c08;
					*(short*) (ent + 0x5e) =
					    *(short*) 0x7f4c0c;
					fcn_00500bb0(ent + 0x52, 0, 10, 0);
					return;
				}
			}
		}
		*(int*) (ent + 0x52) = *(int*) 0x7f4c00;
		*(int*) (ent + 0x56) = *(int*) 0x7f4c04;
		*(int*) (ent + 0x5a) = *(int*) 0x7f4c08;
		*(short*) (ent + 0x5e) = *(short*) 0x7f4c0c;
		fcn_00500bb0(ent + 0x52, 0, 0, 1);
		*(int*) (ent + 0x70) = 2;
		return;
	case 2:
		e2 = fcn_00503fe0(*(int*) (ent + 0xb0), 1, 1);
		if (e2 == 0) {
			*(int*) (ent + 0x70) = -1;
			return;
		}
		j = (int) (0x7f4ca0
		    + *(unsigned short*) (e2 + 0x27) * 0x21c);
		i = (int) (0x7f4ca0
		    + *(unsigned short*) (ent + 8) * 0x21c);
		slot = fcn_0050c710(e2, 5, 1);
		prob = (float) ((double) slot * 0.01 + 1.0);
		e2 = fcn_00503fe0(*(int*) (ent + 0xb0), 1, 1);
		target = fcn_00502cd0(*(int*) (e2 + 0x5d), 1, 0, 0xca);
		count = (int) target;
		while (target != 0) {
			if (*(int*) (target + 0x2a) == *(int*) (e2 + 1)) {
				value = (float) ((double)
				    (unsigned char) target[0x37] + 100.0) * 0.01;
				break;
			}
			target = fcn_00502850();
			count = (int) target;
		}
		if (*(int*) 0x774800 != 0) {
			value = 10.0f;
		}
		rnd = fcn_0042e410(0x4b) & 0xffff;
		if ((float) rnd + value * 100.0f < prob * 125.0f) {
			memset(msg, 0, 0x114);
			msg[8] = 3;
			msg[0x26] = 0xa2;
			*(int*) (msg + 0x14) = *(int*) (e2 + 1);
			msg[0x30] = 2;
			msg[0x7c] = 2;
			*(int*) (msg + 0xc) = *(int*) (0x7f4ca4
			    + *(unsigned short*) 0x774970 * 0x21c);
			*(int*) (msg + 0x10) = *(int*) ((char*) i + 4);
			*(int*) (msg + 0x34) = *(int*) ((char*) j + 4);
			for (i = 0; i < 0x10; i++) {
				*(int*) (msg + 0x80 + i * 4) = -1;
				*(int*) (msg + 0xc0 + i * 4) = -1;
			}
			slot = 0;
			i = 0x7f4e0c;
			do {
				if (slot >= 6) {
					break;
				}
				if (*(char*) (i - 0x164) != 0
				    && *(int*) i == (int) e2) {
					*(int*) (msg + 0x80 + slot * 4) =
					    *(int*) (i - 0x168);
					slot++;
				}
				i += 0x21c;
			} while (i < 0x85a20c);
			*(int*) (msg + 0x100) = -1;
			*(int*) (msg + 0x104) = -1;
			*(int*) (msg + 0x108) = -1;
			e2 = fcn_00503fe0(*(int*) (ent + 0xb0), 1, 1);
			*(int*) (msg + 0x100) = *(int*) (e2 + 1);
			slot = 0;
			e2 = ent + 0x8c;
			i = 0;
			do {
				if (slot >= 6) {
					break;
				}
				if (*(int*) e2 != -1) {
					*(int*) (msg + 0xc0 + slot * 4) =
					    *(int*) e2;
					slot++;
				}
				i++;
				e2 += 4;
			} while (i < 8);
			if (slot != 0 && count != 0) {
				*(int*) (msg + 0x1c) = *(int*) 0x7f4c00;
				*(int*) (msg + 0x20) = *(int*) 0x7f4c04;
				*(int*) (msg + 0x24) = *(int*) 0x7f4c08;
				*(short*) (msg + 0x28) = *(short*) 0x7f4c0c;
				fcn_00500bb0((char*) msg + 0x1c, 0, 0x1e, 0);
				*(int*) (ent + 0xb4) = fcn_004c5980(msg);
				*(int*) (ent + 0x52) = *(int*) 0x7f4c00;
				*(int*) (ent + 0x56) = *(int*) 0x7f4c04;
				*(int*) (ent + 0x5a) = *(int*) 0x7f4c08;
				*(short*) (ent + 0x5e) = *(short*) 0x7f4c0c;
				fcn_00500bb0(ent + 0x52, 0, 0, 1);
				*(int*) (ent + 0x70) = 3;
				goto tail;
			}
			e2 = fcn_00503fe0(*(int*) (ent + 0xb0), 1, 1);
			target = fcn_00503fe0(*(int*) (ent + 0xac), 1, 1);
			j = fcn_004d5110(target, e2, (char*) i,
			    (char*) (0x7f4ca0
			    + *(unsigned short*) (e2 + 0x27) * 0x21c));
			if (e2 != 0) {
				*(int*) (e2 + 0x4d) += j;
			}
			io_FormatTextBuffer(text, 0x1c54, target, j);
			fcn_00545e80(*(int*) (0x7f4ca4
			    + *(unsigned short*) (e2 + 0x27) * 0x21c),
			    -1, text, 0, 0x5f0, *(int*) (e2 + 1), -1, 0, 0);
			io_FormatTextBuffer(text2, 0x1c55, target, j);
			fcn_00545e80(*(int*) (0x7f4ca4
			    + *(unsigned short*) (ent + 8) * 0x21c),
			    -1, text2, 0, 0x5f0, *(int*) (e2 + 1), -1, 0, 0);
			*(int*) (ent + 0x52) = *(int*) 0x7f4c00;
			*(int*) (ent + 0x56) = *(int*) 0x7f4c04;
			*(int*) (ent + 0x5a) = *(int*) 0x7f4c08;
			*(short*) (ent + 0x5e) = *(short*) 0x7f4c0c;
			fcn_00500bb0(ent + 0x52, 0, 0, 1);
			*(int*) (ent + 0x70) = 5;
tail:
			if (count != 0) {
				e2 = fcn_00503fe0(*(int*) (ent + 0xb0),
				    1, 1);
				if (e2 != 0) {
					fcn_004c5a60(*(int*) (e2 + 1), -1,
					    *(int*) ((char*) count + 2));
				}
			}
			return;
		}
		e2 = fcn_00503fe0(*(int*) (ent + 0xb0), 1, 1);
		target = fcn_00503fe0(*(int*) (ent + 0xac), 1, 1);
		j = fcn_004d5450(e2) + 0x1125;
		io_FormatTextBuffer(text, 0x114b, j,
		    (int) *(unsigned short*) (target + 0x27), target, j);
		fcn_00545e80(*(int*) (0x7f4ca4
		    + *(unsigned short*) (ent + 8) * 0x21c),
		    -1, text, 0, 0x5f0, *(int*) (target + 1), -1, 0, 0);
		if (*(unsigned char*) (0x7f4ca2
		    + *(unsigned short*) (target + 0x27) * 0x21c) == 6
		    || *(unsigned char*) (0x7f4ca2
		    + *(unsigned short*) (target + 0x27) * 0x21c) == 7) {
			io_FormatTextBuffer(text2, 0x1c56, target);
			fcn_00545e80(*(int*) (0x7f4ca4
			    + *(unsigned short*) (target + 0x27) * 0x21c),
			    -1, text2, 0, 0x5f0,
			    *(int*) (target + 1), -1, 0, 0);
		}
		*(int*) (ent + 0x70) = 5;
		return;
	case 3:
		if (fcn_004c4450(*(int*) (ent + 0xb4)) == 0) {
			return;
		}
		target = (char*) fcn_004c4480(*(int*) (ent + 0xb4));
		*(int*) (ent + 0xb8) = *(int*) target;
		*(int*) (ent + 0x52) = *(int*) 0x7f4c00;
		*(int*) (ent + 0x56) = *(int*) 0x7f4c04;
		*(int*) (ent + 0x5a) = *(int*) 0x7f4c08;
		*(short*) (ent + 0x5e) = *(short*) 0x7f4c0c;
		fcn_00500bb0(ent + 0x52, 0, 1, 0);
		*(int*) (ent + 0x70) = 4;
		return;
	case 4:
		if (fcn_004e6a30(*(int*) (ent + 0xb8)) != 0) {
			*(int*) (ent + 0x52) = *(int*) 0x7f4c00;
			*(int*) (ent + 0x56) = *(int*) 0x7f4c04;
			*(int*) (ent + 0x5a) = *(int*) 0x7f4c08;
			*(short*) (ent + 0x5e) = *(short*) 0x7f4c0c;
			fcn_00500bb0(ent + 0x52, 0, 5, 0);
			return;
		}
		*(int*) (ent + 0x52) = *(int*) 0x7f4c00;
		*(int*) (ent + 0x56) = *(int*) 0x7f4c04;
		*(int*) (ent + 0x5a) = *(int*) 0x7f4c08;
		*(short*) (ent + 0x5e) = *(short*) 0x7f4c0c;
		fcn_00500bb0(ent + 0x52, 0, 0, 1);
		*(int*) (ent + 0x70) = 5;
		return;
	case -2:
	case -1:
	case 5:
		e2 = fcn_00503fe0(*(int*) (ent + 0xb0), 1, 1);
		if (e2 != 0) {
			slot = (int) fcn_00504b30(e2);
		}
		count = 8;
		do {
			j = *(int*) (ent + 0x8c + (8 - count) * 4);
			if (j != -1) {
				target = gm_LookupEntityRecordById(j);
				if (target != 0) {
					fcn_004c5c80(*(int*) (target + 4));
					if (e2 != 0) {
						fcn_004c5da0(
						    *(int*) (target + 4),
						    *(int*) (e2 + 1),
						    *(int*) ((char*) slot + 2),
						    0, 0, (char*) 0x6a6aac);
					}
					fcn_00529160(0, 0,
					    *(unsigned short*) target, 0);
				}
			}
			count--;
		} while (count != 0);
		fcn_00546190(ent);
		return;
	}
	(void) prob;
	(void) rnd;
	(void) i;
}
