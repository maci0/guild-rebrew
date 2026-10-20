extern char* g_1007cd4;

/* The 0x180-byte native table is addressed literally; no data row owns it. */
/* ADDRESS: GOLDTL 0x004a7be0 */
void __cdecl fcn_004a7be0(void)
{
	int counts[6];
	int off;
	int v13;
	int v11;
	int v14;
	int i;
	int g;
	int j;
	int c;
	int best;

	v14 = 0;
	i = 1;
	off = 0x34;
	do {
		v13 = 0;
		v11 = 0;
		best = 0;
		for (g = 0; g < 6; g++) {
			c = 0;
			for (j = 0; j < 4; j++) {
				if (((int*) 0x01007ce8)[(g * 4 + j) * 4] == i) {
					c++;
				}
			}
			if (c > 1) {
				v13++;
			}
			if (c > v11) {
				v11 = c;
			}
			counts[g] = c;
		}
		for (g = 0; g < 4; g++) {
			c = 0;
			for (j = 0; j < 6; j++) {
				if (((int*) 0x01007ce8)[g * 4 + j * 16] == i) {
					c++;
				}
			}
			if (c > best) {
				best = c;
				v14 = g;
			}
			counts[g] = c;
		}
		if ((unsigned char) g_1007cd4[0xb5] < 5 && v13 <= 1 && v11 < 2) {
			*(int*) (g_1007cd4 + 0x30 + off) = 3;
		} else if ((unsigned char) g_1007cd4[0xb5] == best) {
			*(int*) (g_1007cd4 + 0x30 + off) = 2;
		} else if (*(int*) g_1007cd4 < 6 && (unsigned char) g_1007cd4[0xb5] - best <= 1) {
			for (c = 0; c < 6; c++) {
				if (((int*) 0x01007cec)[v14 * 4 + c * 16 - 1] != i &&
				    ((int*) 0x01007cec)[v14 * 4 + c * 16] == 0) {
					break;
				}
			}
			if (c == 6) {
				*(int*) (g_1007cd4 + 0x30 + off) = 2;
			} else if ((unsigned char) g_1007cd4[0xb5] == 5 && v11 < 2) {
				*(int*) (g_1007cd4 + 0x30 + off) = 0;
			} else {
				*(int*) (g_1007cd4 + 0x30 + off) = 1;
			}
		} else if ((unsigned char) g_1007cd4[0xb5] == 5 && v11 < 2) {
			*(int*) (g_1007cd4 + 0x30 + off) = 0;
		} else {
			*(int*) (g_1007cd4 + 0x30 + off) = 1;
		}
		off += 0x34;
		i++;
	} while (off < 0x9c);
}
