extern unsigned char* g_90e094;
extern unsigned char* g_868050;
extern unsigned char g_773d75;

unsigned short __cdecl fcn_0042e410(int);
int __cdecl fcn_0050d320(char*, unsigned char);
int __cdecl fcn_004a48a0(char*, int);

// FUNCTION: GOLDTL 0x004976e0
// SIZE: 494

/* The inventory entry also holds a second function at 0x4978d0 (180 bytes). */
int __cdecl fcn_004976e0(int unused, char* e, int unused2, char* out, char* out2)
{
	int minv;
	char* best;
	char* p;
	int i;
	int kind;
	float f;
	float amt;

	if (out[0] == 0) {
		minv = fcn_0042e410(0x24) + 0x23;
		best = 0;
		p = ((char*)g_90e094);
		for (i = 0; i < 0x100; i++) {
			if (p[0] != 0 && *(unsigned short*) (p + 0x25) == *(unsigned short*) e && !(p[0x5a] & 0x45) &&
			    ((1 << g_868050[*(unsigned char*) p + *(unsigned char*) p * 588]) & 0x7c43b4) &&
			    p[0x5c] < minv) {
				minv = p[0x5c];
				best = p;
			}
			p += 0xa9;
		}
		if (best != 0) {
			f = fcn_0050d320(e, g_773d75) * 0.95f;
			kind = minv < 50 ? 50 : 30;
			amt = fcn_004a48a0(best, kind);
			if (amt != 0.0f && !(amt > f)) {
				out[0] = 4;
				*(int*) (out + 4) = *(int*) (best + 1);
				*(int*) (out + 8) = 1;
				*(int*) (out + 0x10) = kind;
				*(float*) (out + 0x14) = amt;
				out2[0] = 7;
				*(int*) (out2 + 4) = *(int*) (e + 4);
				*(int*) (out2 + 8) = (int) f;
				*(int*) (out2 + 0x10) = 1;
				return 0xf;
			}
		}
	} else if (out[0] == 4) {
		p = ((char*)g_90e094);
		for (i = 0; i < 0x100; i++, p += 0xa9) {
			if (p[0] != 0 && *(int*) (p + 1) == *(int*) (out + 4)) {
				if (p[0x5a] & 5) {
					return 0;
				}
				amt = fcn_004a48a0(p, *(int*) (out + 0x10));
				if (amt != 0.0f && !(amt > *(unsigned int*) (out2 + 8))) {
					*(float*) (out + 0x14) = amt;
					return 0xf;
				}
				return 0;
			}
		}
	}
	return 0;
}
