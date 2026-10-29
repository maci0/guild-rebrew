extern int __cdecl gm_RandomMod(int);
extern char* __cdecl fcn_005463a0(int, int, int, int, int);
extern char* __cdecl he_fn_Handlung(void);
extern int __cdecl fcn_0050d6d0(char*, short*, int, int*);
extern int __cdecl fcn_004f4830(int, char*);

/* Rates the records returned for an action and fills the action packets with
 * the best-scoring record; 0x33 on success. */
/* ADDRESS: GOLDTL 0x0049e900 */
int __cdecl fcn_0049e900(int code, short* target, char* ent, char* out1, char* out2)
{
	float score[4];
	int rec[9];
	int msg[9];
	int v[4];
	int step;
	int cnt;
	int i;
	int j;
	int type;
	int best;
	int found;
	int count;
	double d;
	double dd;

	step = *(int*) ((gm_RandomMod(0x10) & 0xffff) * 4 + 0x6643d8);
	if (*(char*) (ent + 2) == 3)
		return 0;
	if (code != 0x33 && code != 0x13 && code != 0x10 && code != 0x11)
		return 0;
	cnt = 0;
	if (fcn_005463a0(2, 0, 0x23, 2, *(unsigned short*) ent) != 0) {
		cnt = 1;
		while (he_fn_Handlung() != 0)
			cnt += 1;
	}
	if ((gm_RandomMod(10) & 0xffff) < cnt + 1)
		return 0;
	if (code != 0x33)
		goto branch2;
	if ((*(int*) 0x7f4c04 & 0xffff) - 8 >= 0xa)
		j = 0xa;
	else
		j = (*(int*) 0x7f4c04 & 0xffff) - 8;
	d = (double) (10 - j) * *(float*) 0x662a3c;
	dd = d * d;
	v[1] = (int) (*(float*) 0x664378 * dd);
	v[2] = (int) (*(float*) 0x664374 * dd);
	v[3] = (int) (*(float*) 0x664370 * dd);
	found = 0;
	for (i = 0; i < 0x100; i++) {
		j = gm_RandomMod(0x100) & 0xffff;
		found = *(int*) 0x90e094 + j + j * 0xa8;
		if (*(unsigned char*) found != 0 &&
		    *(unsigned short*) (found + 0x27) == *target) {
			type = *(unsigned char*) found;
			if (((1 << (type & 0x1f)) & 0x7d4390) != 0 &&
			    *(int*) (found + 0x39) < v[*(unsigned char*)
				(*(int*) 0x868050 + type * 0x24d + 0x247)])
				break;
		}
		j = (signed char) (j + v[0]);
	}
	if (found == 0)
		return 0;
	goto search2;
branch2:
	if (*(unsigned char*) out1 != 0x12)
		return 0;
	found = 0;
	for (i = 0; i < 0x100; i++) {
		j = gm_RandomMod(0x100) & 0xffff;
		found = *(int*) 0x90e094 + j + j * 0xa8;
		if (*(unsigned char*) found != 0 &&
		    *(unsigned short*) (found + 0x27) != *target &&
		    *(unsigned char*) (*(int*) 0x868050 + (*(unsigned char*) found) * 0x24d) == 5)
			break;
		j = (signed char) (j + v[0]);
	}
	if (found == 0)
		return 0;
search2:
	for (i = 0; i < 0x100; i++) {
		j = gm_RandomMod(0x100) & 0xffff;
		found = *(int*) 0x90e094 + j + j * 0xa8;
		if (*(unsigned char*) found != 0 &&
		    *(unsigned short*) (found + 0x27) != *target &&
		    *(unsigned char*) (*(int*) 0x868050 + (*(unsigned char*) found) * 0x24d) == 5)
			break;
		j = (signed char) (j + v[0]);
	}
	if (found == 0)
		return 0;
	count = fcn_0050d6d0((char*) found, target, 3, rec);
	if (count <= 0)
		return 0;
	fcn_004f4830(0xe, (char*) msg);
	if (code == 0x33) {
		for (i = 0; i < count; i++) {
			score[i + 1] = (float) rec[i * 3] *
				((float) rec[i * 3 + 1] * *(float*) 0x662dbc) *
				((float) (msg[6] - 2) / (float) rec[i * 3 + 2]);
		}
	} else {
		for (i = 0; i < count; i++) {
			if (rec[i * 3] <= *(int*) (out1 + 8))
				score[i + 1] = *(float*) 0x662a94;
			else
				score[i + 1] = (float) rec[i * 3] *
					((float) rec[i * 3 + 1] * *(float*) 0x662dbc) *
					((float) (msg[6] - 2) / (float) rec[i * 3 + 2]);
		}
	}
	best = -1;
	d = *(float*) 0x6628a8;
	for (i = 0; i < count; i++) {
		if (d < score[i + 1]) {
			d = score[i + 1];
			best = i;
		}
	}
	if (best < 0)
		return 0;
	if (best > 2)
		return 0;
	if (code == 0x33) {
		out1[0] = 4;
		*(int*) (out1 + 4) = *(int*) (found + 1);
		*(int*) (out1 + 8) = -1;
	} else {
		out1[0] = 4;
		*(int*) (out1 + 4) = *(int*) (found + 1);
		*(int*) (out1 + 8) = -1;
	}
	out2[0] = 0x14;
	*(int*) (out2 + 4) = rec[best * 3];
	*(int*) (out2 + 8) = rec[best * 3 + 1];
	*(int*) (out2 + 0x10) = rec[best * 3 + 2];
	return 0x33;
}
