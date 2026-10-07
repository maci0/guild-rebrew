// FUNCTION: GOLDTL 0x0050dac0
// FUNCTION: GOLD 0x0050a640

extern char g_7f4ca0[];

int __cdecl fcn_0050d2a0(char* slot);
char* __cdecl fcn_00503fe0(int a, int b, int c);
int __cdecl fcn_0050cf50(char* e, int k);
int __cdecl fcn_0050d3c0(char* e);
char* __cdecl fcn_00503e80(void);

int __cdecl fcn_0050dac0(int raw_idx)
{
	unsigned short idx;
	char* slot;
	char* ent;
	int total;

	idx = (unsigned short) raw_idx;
	if (idx >= 0x300) {
		return -1;
	}
	slot = g_7f4ca0 + idx * 0x21c;
	if (*(unsigned short*) slot == 0xffff) {
		return -1;
	}
	total = fcn_0050d2a0(slot);
	ent = fcn_00503fe0(1, 3, idx);
	if (ent) {
		do {
			total += fcn_0050cf50(ent, *(signed char*) (ent + 0x5c));
			total += fcn_0050d3c0(ent);
			ent = fcn_00503e80();
		} while (ent);
	}
	return total;
}
