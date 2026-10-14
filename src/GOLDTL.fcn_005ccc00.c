


// SIZE 0x38
typedef struct {
	unsigned short* who;
	int f4;
	int h;
	int pad[11];
} Match;

float __cdecl fcn_0050f980(int, int, int);
void __cdecl fcn_00472380(int, int, int, int);

void __cdecl fcn_005ccc00(unsigned short* self, unsigned int n, Match* arr)
{
	unsigned int i;
	unsigned short* p;

	if (self != 0 && *self != 0xffff && n > 0) {
		for (i = 0; i < n; i++, arr++) {
			p = arr->who;
			if (p != 0 && *p != 0xffff && arr->h != -1) {
				if ((((char*) self)[2] == 6 || ((char*) self)[2] == 7) &&
				    (((char*) p)[2] == 6 || ((char*) p)[2] == 7)) {
					fcn_00472380(arr->h, 0, 100, 0);
				}
				else {
					fcn_00472380(arr->h, 0, 100, (int) fcn_0050f980(*self, *p, 1));
				}
			}
		}
	}
}
