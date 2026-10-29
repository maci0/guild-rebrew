/* Recomputes the wage/price curve of one profession slot: selects the curve
 * segment from the global tables, interpolates it and stores the per-goods
 * factors used by the economy tick.
 *
 * The reference body keeps the interpolated values in the x87 stack across
 * calls; kuna leaves the st(1) intermediate undefined, so the exact double
 * locals are reconstructed from the instruction sequence (low confidence). */

extern char* g_8680c0;
extern char* g_85ab80;
extern char* lpObjektePROT;
extern unsigned char g_773d75;
extern int g_14cbca0;
extern double g_662908;

typedef struct Stamp {
	char b[14];
} Stamp;

void __cdecl fcn_00500d60(int*, void*);
int __cdecl fcn_005017a0(int);
int __cdecl fcn_00501fe0(int);
int __cdecl fcn_00502450(int, int);
int __cdecl fcn_005024e0(int, int);
float __cdecl fcn_005025a0(int, int);

/* ADDRESS: GOLDTL 0x005020e0 */
double __cdecl fcn_005020e0(int a0, int a1)
{
	Stamp stamp;
	char* base;
	char* tab;
	int v5;
	int v6;
	int v7;
	int v8;
	int v9;
	int v10;
	int v11;
	int v12;
	unsigned short id;
	double d;

	fcn_00500d60((int*) a1, &stamp);
	id = *(unsigned short*) (stamp.b + 0xa);
	v5 = 0;
	v11 = a0 * 0x2f4;
	base = g_8680c0 + v11;
	v7 = 0x4;
	v6 = v7;
	do {
		if (*(int*) (base + v6) <= *(int*) (base + v6 - 4)) {
			if (v5 <= 8) {
				break;
			}
			break;
		}
		v5++;
		v6 += 8;
	} while (v5 < 9);
	if (v5 == 9) {
		v5 = 9;
	}
	v8 = 0;
	if (v5 >= 1) {
		v7 = 0x4;
		do {
			if ((int) id <= *(int*) (base + v7 - 4)) {
				break;
			}
			v8++;
			v7 += 8;
		} while (v8 < v5);
	}
	if (v5 - 1 <= v8) {
		*(int*) (g_85ab80 + a0 * 0x2a90) = *(int*) (base + v5 * 8);
	} else {
		v9 = *(int*) (base + v8 * 8);
		if ((int) id != v9) {
			if (v8 >= 1) {
				int lo;
				int hi;

				lo = *(int*) (base + v8 * 8 - 4);
				hi = *(int*) (base + v8 * 8 + 4);
				*(int*) (g_85ab80 + a0 * 0x2a90) =
				    (int) (((*(int*) (stamp.b + 10) - lo) * 0xc)
					* (hi - *(int*) (base + v8 * 8 - 8)))
				    / ((v9 - lo) * 0xc)
				    + *(int*) (base + v8 * 8 - 8);
			} else {
				*(int*) (g_85ab80 + a0 * 0x2a90) = *(int*) (base + 4);
			}
		} else {
			int lo;

			lo = *(int*) (base + v8 * 8 + 4);
			*(int*) (g_85ab80 + a0 * 0x2a90) =
			    (int) (((*(int*) (stamp.b + 10) - v9) * 0xc)
				* (*(int*) (base + v8 * 8 + 12) - lo))
			    / ((*(int*) (base + v8 * 8 + 8) - v9) * 0xc)
			    + lo;
		}
	}
	v8 = a0 * 0x2a90;
	*(int*) (g_85ab80 + v8) = (*(int*) (g_85ab80 + v8 + 4)
	    * *(int*) (g_85ab80 + v8)) / 1000;
	v5 = 0;
	base = g_8680c0 + v11;
	tab = base + 0x54;
	v7 = 0x4;
	do {
		if (*(int*) (tab + v7 - 4) <= *(int*) (tab + v7)) {
			if (v5 <= 8) {
				break;
			}
			break;
		}
		v5++;
		v7 += 8;
	} while (v5 < 9);
	if (v5 == 9) {
		v5 = 9;
	}
	v9 = 0;
	if (v5 >= 1) {
		tab = base + 0x54;
		do {
			if ((int) id <= *(int*) (tab - 4)) {
				break;
			}
			v9++;
			tab += 8;
		} while (v9 < v5);
	}
	if (v5 - 1 <= v9) {
		*(int*) (g_85ab80 + v8 + 8) = *(int*) (base + 0x54 + v5 * 8);
	} else {
		int hi;

		hi = *(int*) (base + 0x54 + v9 * 8);
		if ((int) id != hi) {
			if (v9 >= 1) {
				int lo;
				int step;

				lo = *(int*) (base + 0x54 + v9 * 8 - 4);
				step = (*(int*) (stamp.b + 10) - lo) * 0xc;
				v5 = (int) (step
				    * (*(int*) (base + 0x54 + v9 * 8 + 4) - hi))
				    / ((*(int*) (base + 0x54 + v9 * 8) - lo) * 0xc)
				    + hi;
			} else {
				v5 = *(int*) (base + 0x54 + 4);
			}
		} else {
			int lo;

			lo = *(int*) (base + 0x54 + v9 * 8 + 4);
			v5 = (int) (((*(int*) (stamp.b + 10) - hi) * 0xc)
			    * (*(int*) (base + 0x54 + v9 * 8 + 12) - lo))
			    / ((*(int*) (base + 0x54 + v9 * 8 + 8) - hi) * 0xc)
			    + lo;
		}
		*(int*) (g_85ab80 + v8 + 8) = v5;
	}
	*(int*) (g_85ab80 + v8 + 8) = (*(int*) (g_85ab80 + v8 + 0xc)
	    * *(int*) (g_85ab80 + v8 + 8)) / 1000;
	v5 = 0;
	v12 = 0xc0;
	do {
		char kind;

		kind = *(char*) (lpObjektePROT + (unsigned short) *(int*) (g_85ab80 + v8 + v12 - 0x30) * 0x41);
		if (kind != 0x17 && kind != 0x25) {
			d = (double) fcn_00502450(a0, v5);
			d = (d - *(float*) (g_85ab80 + v8 + v12 - 0x10)) * g_662908
			    + *(float*) (g_85ab80 + v8 + v12 - 0x10);
			*(float*) (g_85ab80 + v8 + v12 - 0x10) = (float) d;
		}
		if (a0 != g_773d75) {
			*(int*) (g_85ab80 + v8 + v12 + 4) =
			    *(int*) (g_85ab80 + v8 + v12);
		} else {
			*(int*) (g_85ab80 + v8 + v12 + 4) =
			    fcn_005024e0(a0, v5);
		}
		*(float*) (g_85ab80 + v8 + v12 + 8) =
		    fcn_005025a0(a0, v5);
		if (*(char*) (g_85ab80 + v8 + v12 + 0x10)) {
			*(float*) (g_85ab80 + v8 + v12 - 0x10) =
			    (float) *(int*) (g_85ab80 + v8 + v12 + 4);
		}
		*(int*) (g_85ab80 + v8 + v12 - 0x20) = 0;
		*(int*) (g_85ab80 + v8 + v12 - 0x1c) = 0;
		*(int*) (g_85ab80 + v8 + v12 - 0x14) = 0;
		*(int*) (g_85ab80 + v8 + v12 - 0x18) = 0;
		v5++;
		v12 += 0x80;
	} while (v5 < 0x55);
	d = 0.0;
	if (g_14cbca0 == -1) {
		fcn_005017a0(a0);
		d = fcn_00501fe0(a0);
	}
	return d;
}
