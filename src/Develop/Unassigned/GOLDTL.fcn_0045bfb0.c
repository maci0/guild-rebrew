extern char* g_104049c;
extern unsigned int g_10404a0;
extern int g_10405c4;

void __cdecl fcn_0045bf70(char*);
void __cdecl fcn_0045bfb0(int);

/* ADDRESS: GOLDTL 0x0045bfb0 */
void __cdecl fcn_0045bfb0(int obj)
{
	char* o;
	char* p;
	char* q;
	unsigned int i;
	unsigned int j;
	int idx;
	int nidx;

	o = (char*) obj;
	if (o == 0 || *(int*) (o + 0x40) <= 0) {
		return;
	}
	if (*(int*) (o + 0x5c) > 0 && *(char*) (o + 0x5d) == 0) {
		p = g_104049c;
		for (i = 0; i < g_10404a0; i++, p += 0x70) {
			if (*(int*) (p + 0x40) > 0 && *(int*) (p + 0x48) == *(int*) (o + 0x48) &&
			    *(unsigned char*) (p + 0x5d) > 0) {
				fcn_0045bfb0((int) p);
			}
		}
	}
	*(int*) (o + 0x40) = *(int*) (o + 0x40) - 1;
	if (*(int*) (o + 0x40) > 0) {
		return;
	}
	if (*(char*) (o + 0x54) & 2) {
		*(int*) (o + 0x50) = 0;
	} else {
		idx = (int) (o - g_104049c) / 0x70;
		p = g_104049c;
		for (i = 0; i < g_10404a0; i++, p += 0x70) {
			if (*(int*) (p + 0x40) > 0 && (*(char*) (p + 0x54) & 2) &&
			    *(int*) (p + 0x44) == idx) {
				*(char*) (p + 0x54) = *(char*) (p + 0x54) & 0xfd;
				*(int*) (p + 0x44) = *(int*) (o + 0x44);
				nidx = (int) (p - g_104049c) / 0x70;
				q = p + 0x70;
				for (j = i + 1; j < g_10404a0; j++, q += 0x70) {
					if (*(int*) (q + 0x40) > 0 && (*(char*) (q + 0x54) & 2) &&
					    *(int*) (q + 0x44) == idx) {
						*(int*) (q + 0x44) = nidx;
					}
				}
				break;
			}
		}
		if (i == g_10404a0) {
			fcn_0045bf70(o);
		}
	}
	*(int*) (o + 0x40) = 0;
	g_10405c4 = g_10405c4 - 1;
}
