extern int g_6b7d7c;
extern int MemUsed;
extern char* g_6b7d78;
extern char g_14cbae0[];
extern char g_678f70[]; /* Unloading Samplebank %s ... MemUsed before unloading %d bytes. */
extern char g_678f28[]; /* Finished unloading Samplebank %s ... MemUsed after unloading %d bytes. */

char* __cdecl sb_FindVoiceBySample(int, int*);
void __cdecl sb_StopVoice(char*, int);
void __cdecl m_FreeTracked(void*);
int __cdecl fcn_0064d41a(char*, char*, ...);

/* ADDRESS: GOLDTL 0x004230e0 */
int __cdecl fcn_004230e0(char* a0)
{
	int r;
	char* bank;
	char* prev;
	char* name;
	char* s;

	int i;
	int left;

	r = 0;
	prev = 0;
	if (g_6b7d7c == 0) {
		return 1;
	}
	if (MemUsed == 0 || a0 == 0) {
		r = -1; goto done;
	}
	bank = g_6b7d78;
	if (bank == 0) {
		goto done;
	}
	do {
		if (bank == a0) {
			goto found;
		}
		prev = bank;
		bank = *(char**) (bank + 0x13c);
	} while (bank != 0);
	goto done;
found:
	left = --(*(int*) (bank + 0x140));
	if (left > 0) {
		goto done;
	}
	if (prev != 0) {
		*(char**) (prev + 0x13c) = *(char**) (bank + 0x13c);
	} else {
		g_6b7d78 = *(char**) (bank + 0x13c);
	}
	name = a0 + 0x32;
	fcn_0064d41a(g_14cbae0, g_678f70, name, MemUsed);
	i = 0;
	if (*(int*) (bank + 0x134) > 0) {
		do {
			if (*(int*) (*(char**) (bank + 0x138) + i * 0x40 + 0x38) != 0) {
				*(int*) &a0 = 0;
				s = sb_FindVoiceBySample(*(char**) (bank + 0x138) + i * 0x40, (int*) &a0);
				while (s != 0) {
					sb_StopVoice(s, 0);
					*(int*) (s + 4) = 0;
					(*(int*) &a0)++;
					s = sb_FindVoiceBySample(*(char**) (bank + 0x138) + i * 0x40, (int*) &a0);
				}
				if (*(char*) (*(char**) (bank + 0x138) + i * 0x40 + 0x36) == 1) {
					MemUsed += -12 - *(int*) (*(char**) (*(char**) (bank + 0x138) + i * 0x40 + 0x38) + 4);
				} else {
					MemUsed += -12 - *(int*) (*(char**) (*(char**) (bank + 0x138) + i * 0x40 + 0x38) + 8);
				}
				m_FreeTracked(*(char**) (*(char**) (bank + 0x138) + i * 0x40 + 0x38));
				*(char**) (*(char**) (bank + 0x138) + i * 0x40 + 0x38) = 0;
			}
			i++;
		} while (i < *(int*) (bank + 0x134));
	}
	MemUsed += -0x144 - *(int*) (bank + 0x134) * 0x40;
	fcn_0064d41a(g_14cbae0, g_678f28, name, MemUsed);
	m_FreeTracked(bank);
done: return r;
}
