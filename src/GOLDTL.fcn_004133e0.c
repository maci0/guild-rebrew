// FUNCTION: GOLDTL 0x004133e0
// SIZE: 160

#define MIN(a, b) ((a) > (b) ? (b) : (a))
#define MAX(a, b) ((a) < (b) ? (b) : (a))

extern int g_6b8014;
void __cdecl fcn_00438100(char* e, int cam, int f);
char* __cdecl fcn_00455910(char* e, int h, char* p);

int __cdecl fcn_004133e0(char* e, float* lo, float* hi)
{
	float* q;
	int i;
	char* p;

	*hi = 0.0f;
	*lo = 0.0f;
	if (*(int*) (e + 0x218) == 4) {
		fcn_00438100(e, g_6b8014, 0);
		p = fcn_00455910(e, *(int*) (e + 0x1cc), *(char**) (e + 0x1ec) + 8);
		if (p != 0) {
			q = (float*) (p + 4);
			*lo = *q;
			*hi = *q;
			for (i = 7; i != 0; i--) {
				*lo = MIN(*q, *lo);
				*hi = MAX(*q, *hi);
				q += 20;
			}
			return 0;
		}
	}
	return 1;
}
