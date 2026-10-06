// FUNCTION: GOLD 0x0050c980
// FUNCTION: GOLDTL 0x0050fdb0

extern float g_6628cc;

unsigned short* __cdecl fcn_00508e40(int id);
float __cdecl fcn_0050f980(int a, int b, int c);

float __cdecl fcn_0050fdb0(int k, int n, int* ids)
{
	float sum;
	int cnt;
	int i;
	unsigned short* e;

	cnt = 0;
	sum = 0;
	for (i = 0; i < n; i++) {
		if (ids[i] != -1) {
			e = fcn_00508e40(ids[i]);
			if (e != 0) {
				sum = fcn_0050f980(k, *e, 0) + sum;
				cnt++;
			}
		}
	}
	if (cnt != 0) {
		return sum * 0.01 / cnt;
	}
	return g_6628cc;
}
