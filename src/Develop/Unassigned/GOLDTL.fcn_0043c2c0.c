/* Mip-map preparation for one texture image: marks the edge/alpha bits of
 * the reduced levels and then lets the caller's texture code rebuild them.
 *
 * kuna loses the reaching definitions of the final inverse-index pass
 * (its v6/v11/v12 operands are live across the reduced-level loops), so only
 * the two passes whose operands are fully defined are reconstructed here. */

char __cdecl fcn_0043c140(int*, int, int, int);
void __cdecl fcn_0043db70(int*);

/* ADDRESS: GOLDTL 0x0043c2c0 */
void __cdecl fcn_0043c2c0(int* a0)
{
	unsigned char div[4];
	int* v12;
	unsigned int v16;
	unsigned int v20;
	unsigned int v18;
	unsigned int v19;
	unsigned int v9;
	unsigned int v21;
	unsigned int v22;
	unsigned int v24;
	unsigned int v25;
	unsigned int v3;
	unsigned int v4;
	unsigned int v13;
	unsigned int v15;
	unsigned int v17;
	unsigned int v5;
	int v6;
	int v7;
	int esi;
	int v8;
	char v2;
	int* v11;
	int* v23;
	unsigned char* p;

	v12 = a0;
	v16 = a0[3];
	div[0] = 1;
	div[1] = 2;
	div[2] = 4;
	v20 = *a0;
	v15 = 0;
	if ((int) v20 >= 1) {
		v9 = 0;
		v19 = 0;
		v18 = 0;
		do {
			v18 += 1;
			v13 = 0;
			v23 = (int*) ((v18 & v16) * v20);
			while (1) {
				v5 = v12[4];
				v21 = v13 + 1;
				v22 = v21 & v16;
				v3 = *(unsigned char*) (v9 + v5 + v13)
				    - *(unsigned char*) (v22 + v5 + (int) v23);
				v7 = (int) v3 >> 0x1f;
				v4 = *(unsigned char*) (v19 + v5 + v22)
				    - *(unsigned char*) (v5 + (int) v23 + v13);
				v8 = (int) v4 >> 0x1f;
				v2 = fcn_0043c140(v12, v13, v15, 1);
				*(unsigned char*) (v19 + v13 + v12[9]) =
				    (unsigned char) (((((int) ((v3 ^ v7) - v7)
					<= (int) ((v4 ^ v8) - v8)) * 2) | v2) << 6);
				if ((int) v20 <= (int) v21) {
					break;
				}
				v9 = v19;
				v13 = v21;
			}
			v15 = v18;
			v9 = v19 + v20;
			v19 = v9;
		} while ((int) v18 < (int) v20);
	}
	div[3] = 4;
	v17 = 1;
	v23 = &a0[10];
	do {
		v13 = div[v17];
		v20 = (unsigned int) *a0 / v13;
		v15 = 0;
		if ((int) v20 >= 1) {
			v3 = 0;
			v22 = 0;
			v21 = 0;
			do {
				v4 = 0;
				v24 = (v3 + v13) & v16;
				v18 = 0;
				v19 = 0;
				v11 = v12;
				v3 = v24;
				while (1) {
					v12 = a0;
					v5 = v11[0];
					v25 = (v19 + v13) & v16;
					v9 = v11[4];
					v4 = *(unsigned char*) ((v5 * v15 + v4) * v13 + v9)
					    - *(unsigned char*) (v25 + v3 * v5 + v9);
					v7 = (int) v4 >> 0x1f;
					v3 = *(unsigned char*) (v5 * v13 * v15 + v25 + v9)
					    - *(unsigned char*) (v3 * v5 + v19 + v9);
					v8 = (int) v3 >> 0x1f;
					v2 = fcn_0043c140(a0, v19, v21, v13);
					p = (unsigned char*) *v23;
					p[v22 + v18] = (unsigned char) (((((int) ((v4 ^ v7) - v7)
					<= (int) ((v3 ^ v8) - v8)) * 2) | v2) << 6);
					v4 = v18 + 1;
					v19 += v13;
					v18 = v4;
					if ((int) v20 <= (int) v4) {
						break;
					}
					v11 = v12;
					v3 = v24;
				}
				v15 += 1;
				v22 += v20;
				v21 += v13;
			} while ((int) v15 < (int) v20);
		}
		v17++;
		v23++;
	} while ((int) v17 < 3);
	fcn_0043db70(a0);
	/* Trailing pass: min/max alpha per progressive level and tile. */
	v17 = 0;
	p = (unsigned char*) (a0 + 0xa3);
	v18 = 0;
	do {
		esi = 0;
		do {
			v20 = (unsigned int) a0[1];
			v15 = 0xff;
			v9 = 0;
			v6 = v20 * v18;
			v13 = v20 * (unsigned int) esi;
			v3 = 0;
			do {
				v4 = ((v6 + v3) & v16) * (unsigned int) a0[0];
				v5 = v20 + 1;
				do {
					v21 = (v13 & v16) + v4;
					v7 = *(unsigned char*) (a0[4] + v21);
					if (v15 >= (unsigned int) v7) {
						v15 = (unsigned int) v7;
					}
					if (v9 <= (unsigned int) v7) {
						v9 = (unsigned int) v7;
					}
					if (a0[6] != 0) {
						v8 = *(unsigned char*) (a0[6] + v21);
						if (v8 > 0) {
							if (v15 >= (unsigned int) v8) {
								v15 = (unsigned int) v8;
							}
							if (v9 <= (unsigned int) v8) {
								v9 = (unsigned int) v8;
							}
						}
					}
					v13 += 1;
				} while (--v5 != 0);
				v3 += 1;
			} while (!((int) v20 < (int) v3));
			p[1] = (unsigned char) v9;
			p[0] = (unsigned char) v15;
			p[3] = 0xff;
			p += 0x1f4;
			esi += 1;
		} while ((int) esi < 8);
		v18 += 1;
	} while ((int) v18 < 8);
}
