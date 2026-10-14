


void* __cdecl fcn_00502cd0(int, int, int, ...);
void* __cdecl gm_NextEntityQueryMatch(void);

int __cdecl fcn_0050d2f0(char* entity)
{
	int sum;
	char* r;

	sum = 0;
	r = fcn_00502cd0(*(int*) (entity + 0x178), 1, 4, 9);
	if (r) {
		do {
			sum += *(int*) (r + 0xe);
			r = gm_NextEntityQueryMatch();
		} while (r);
	}
	return sum;
}
