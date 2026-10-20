extern int __cdecl fcn_0064d228(void);
extern int __cdecl fcn_0064d3f8(void);

/* ADDRESS: GOLDTL 0x00417870 */

/* Update the animated particle records of an emitter.  Each active record
 * integrates its position, ages the elapsed timer and re-seeds itself when it
 * expires; the live records are counted and, once the emitter is enabled, the
 * free records up to half its capacity are seeded and the dirty flag cleared. */
char __cdecl fcn_00417870(char* a0, int a1)
{
	char* rec;
	char* base;
	int i;
	int half;
	int count;
	__int64 t;
	float v;
	float f;

	count = 0;
	half = (int) (*(unsigned int*) (a0 + 0x20) >> 1);
	base = *(char**) (a0 + 0x28);
	{
		for (i = 0; i < *(int*) (a0 + 0xd8); i++) {
			rec = base + i * 0x54;
			if (*(unsigned char*) (rec + 0x51) & 1) {
				t = (__int64) (unsigned int) (a1 - *(int*) (rec + 0x30));
				v = (float) t * *(float*) 0x662a2c;
				*(float*) (rec + 0x38) = *(float*) (rec + 0x10) + *(float*) rec;
				*(float*) (rec + 0x3c) = *(float*) (rec + 0x14) + *(float*) (rec + 4);
				*(float*) (rec + 0x40) = *(float*) (rec + 0x18) + *(float*) (rec + 8);
				*(float*) (rec + 0x48) = *(float*) 0x662948 * v + *(float*) (rec + 0x48);
				*(float*) (rec + 4) = *(float*) (rec + 4) - v;
				if (*(float*) (rec + 0x3c) < *(double*) 0x662b00)
					*(unsigned char*) (rec + 0x51) &= 0xfe;
				*(float*) (rec + 0x18) = *(float*) (rec + 0x40);
				*(float*) (rec + 0x10) = *(float*) (rec + 0x38);
				*(float*) (rec + 0x14) = *(float*) (rec + 0x3c);
				f = *(float*) (rec + 0x3c) * *(float*) 0x662acc + *(float*) 0x662914;
				if (*(float*) 0x6628a8 > f)
					f = *(float*) 0x6628a8;
				*(unsigned char*) (rec + 0x4f) = (unsigned char) (int) f;
				if (!(*(unsigned char*) (rec + 0x51) & 1))
					count++;
			}
		}
	}
	if (!(*(int*) (a0 + 0x20) & 1) && count >= *(int*) (a0 + 0xd8))
		return 0;
	if ((*(int*) (a0 + 0x20) & 1) != 0 && count > half) {
		for (i = 0; i < *(int*) (a0 + 0xd8); i++) {
			if (i >= half)
				break;
			rec = base + i * 0x54;
			if (!(*(unsigned char*) (rec + 0x51) & 1)) {
				*(unsigned char*) (rec + 0x51) |= 1;
				*(float*) (rec + 0x38) = (float) fcn_0064d3f8() * *(float*) 0x662a18 - *(float*) 0x6628cc;
				*(float*) (rec + 0x3c) = (*(float*) (a0 + 4) + *(float*) 0x6628a0) *
				                            (float) fcn_0064d3f8() * *(float*) 0x662a18 +
				                        *(float*) (a0 + 0xc);
				*(float*) (rec + 0x40) = (float) fcn_0064d3f8() * *(float*) 0x662a18 - *(float*) 0x6628cc;
				*(float*) rec = (float) fcn_0064d3f8() * *(float*) (a0 + 4) * *(float*) 0x662af8 -
				                *(float*) (a0 + 4);
				v = (*(float*) (rec + 0x3c) - *(float*) 0x662af4) * *(float*) (a0 + 8);
				*(float*) (rec + 4) = v - ((float) fcn_0064d3f8() * *(float*) 0x662af0 +
				                           *(float*) 0x6629d0);
				*(float*) (rec + 8) = ((*(float*) (rec + 0x3c) - *(float*) 0x662af4) +
				                          *(float*) (rec + 4)) *
				                         *(float*) a0 +
				                     (float) fcn_0064d3f8() * *(float*) 0x662a40 +
				                     *(float*) 0x6628d8;
				*(int*) (rec + 0x30) = a1;
				*(float*) (rec + 0x10) = *(float*) (rec + 0x38);
				*(int*) (rec + 0x48) = *(int*) (a0 + 0xe4);
				*(float*) (rec + 0x14) = *(float*) (rec + 0x3c);
				*(float*) (rec + 0x18) = *(float*) (rec + 0x40);
				f = *(float*) (rec + 0x3c) * *(float*) 0x662acc + *(float*) 0x662914;
				if (*(float*) 0x6628a8 > f)
					f = *(float*) 0x6628a8;
				*(unsigned char*) (rec + 0x4f) = (unsigned char) (int) f;
			}
		}
		*(int*) (a0 + 0x20) &= ~1;
	}
	return 1;
}
