extern float g_664188;
extern float g_662948;
extern double g_6640f8;

char* __cdecl fcn_00493f50(int);
float __cdecl fcn_004e6d20(void);
int __cdecl fcn_004e6cb0(int);

/* ADDRESS: GOLDTL 0x00493920 */
int __cdecl fcn_00493920(char* e)
{
	float delta;
	float t;
	float sum;
	float lim;
	float weight;
	volatile float limit;
	int i;
	char* rec;

	*(int*) (e + 0x48) = 0;
	rec = (char*) fcn_00493f50(*(int*) (e + 0x38));
	t = *(float*) (e + 0xc);
	lim = t * g_664188;
	i = 0;
	sum = 0.0f;
	if (*(int*) (e + 0x3c) <= 0) {
		goto done;
	}
	for (;;) {
		weight = 0.5f;
		if (*(int*) (e + 0x40) == 0) {
			weight = 1.0f;
		}
		delta = fcn_004e6d20() * *(float*) (rec + 0xc) * weight + *(float*) (rec + 8);
		t = sum + delta;
		if (t >= limit) {
			sum = t;
			if (fcn_004e6cb0(4) != 0) {
				sum = sum * g_6640f8;
			}
			*(int*) (e + 0x48) = 1;
			goto done;
		}
		if (delta > lim) {
			sum = sum + lim;
			*(int*) (e + 0x48) = 1;
			goto done;
		}
		lim = lim * g_662948;
		i++;
		sum = t;
		if (i >= *(int*) (e + 0x3c)) {
			break;
		}
	}
done:
	*(float*) (e + 0x4c) = -sum;
	return *(int*) (e + 0x48);
}
