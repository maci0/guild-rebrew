
// fcn_005086b0 — sum [n+0xe] over iteration.

int __cdecl fcn_004ffe90(int, int, int, int);
int __cdecl fcn_004ffcc0(void);

int __cdecl gm_SumContainerGold(int containerId)
{
	int total;
	char* entry;
	total = 0;
	entry = (char*) fcn_004ffe90(containerId, 1, 4, 9);
	if (entry != 0) {
		do {
			total += *(int*) (entry + 0xe);
			entry = (char*) fcn_004ffcc0();
		} while (entry != 0);
	}
	return total;
}
