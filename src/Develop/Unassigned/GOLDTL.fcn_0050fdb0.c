


extern float g_6628cc;

unsigned short* __cdecl gm_LookupEntityRecordById(int id);
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
			e = gm_LookupEntityRecordById(ids[i]);
			if (e != 0) {
				sum = fcn_0050f980(k, *e, 0) + sum;
				cnt++;
			}
		}
	}
	if (cnt != 0) {
		return (float)(sum * 0.01 / cnt);
	}
	return g_6628cc;
}
