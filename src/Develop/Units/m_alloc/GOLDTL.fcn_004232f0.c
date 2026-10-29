extern int g_6b7d74;
extern int* g_6b7d78;
extern int g_6b7d7c;

// SIZE 0x40
typedef struct Sample {
	char pad0[0x36];
	unsigned char kind;
	char pad37;
	int* ptr;
	char pad3c[4];
} Sample;

typedef struct Bank Bank;

// SIZE 0x144
struct Bank {
	char pad0[0x134];
	int count;
	Sample* samples;
	Bank* next;
	int f140;
};

void __cdecl m_FreeTracked(int);
char* __cdecl fcn_00422760(int, int*);
void __cdecl fcn_004237f0(void*, int);

/* ADDRESS: GOLDTL 0x004232f0 */
void __cdecl fcn_004232f0(void)
{
	Bank* bank;
	Sample* smp;
	char* p;
	int i;
	int idx;

	if (g_6b7d7c == 0) {
		return;
	}
	if (g_6b7d74 == 0) {
		return;
	}
	bank = (Bank*) g_6b7d78;
	while (bank != 0) {
		bank->f140 = 0;
		i = 0;
		if (bank->count > 0) {
			do {
				if (bank->samples[i].ptr != 0) {
					idx = 0;
					p = fcn_00422760((int) &bank->samples[i], &idx);
					while (p != 0) {
						fcn_004237f0(p, 0);
						*(int*) (p + 4) = 0;
						idx++;
						p = fcn_00422760((int) &bank->samples[i], &idx);
					}
					smp = &bank->samples[i];
					if (smp->kind != 1) {
						g_6b7d74 += -12 - *(int*) ((char*) smp->ptr + 8);
					} else {
						g_6b7d74 += -12 - *(int*) ((char*) smp->ptr + 4);
					}
					m_FreeTracked((int) smp->ptr);
					smp->ptr = 0;
					smp->ptr = 0;
				}
				i++;
			} while (i < bank->count);
		}
		p = (char*) bank->next;
		g_6b7d74 += -0x144 - bank->count * 0x40;
		m_FreeTracked((int) bank);
		bank = (Bank*) p;
	}
	g_6b7d78 = 0;
}
