extern char* g_868050;
extern char g_7f4ca0[];

int __cdecl fcn_0050c710(unsigned char* p, int a, int b);
char* __cdecl fcn_0050dc90(int arg1);
char* __cdecl fcn_00508e40(int id);
float __cdecl fcn_004ff040(char* e);
float __cdecl fcn_0050fdb0(int k, int n, int* ids);

/* ADDRESS: GOLDTL 0x00510260 */
float __cdecl fcn_00510260(unsigned char* a0, int a1, int a2)
{
	float a;
	float f;
	float sum;
	float avg;
	float bonus;
	int count;
	int i;
	char* v4;
	char* e;
	char* ent;
	int* arr;

	arr = (int*) a2;
	i = 0;
	avg = 0.0f;
	count = 0;
	sum = 0.0f;
	bonus = 0.0f;
	v4 = g_868050 + (int) *a0 * 0x24d;
	a = (float) (fcn_0050c710(a0, 1, 1) * 0.01 + 1.0);
	e = fcn_0050dc90((int) a0);
	if (e == 0) {
		e = (char*) 0x7f4ca0 + (int) *(unsigned short*) (a0 + 0x27) * 0x21c;
	}
	if (*(unsigned char*) (e + 2) == 6 || *(unsigned char*) (e + 2) == 7) {
		f = (float) (*(unsigned char*) (e + 0x81) * 0.000992063492063492);
	} else {
		f = 0.0f;
	}
	a = (float) (a + f);
	if (a1 >= 1) {
		do {
			if (arr[i] != -1) {
				ent = fcn_00508e40(arr[i]);
				if (ent != 0) {
					sum = (float) (fcn_004ff040(ent) + sum);
					if (*(char*) (v4 + 0x22f) == *(char*) (ent + 0x165)) {
						bonus = (float) (bonus + 0.3);
					}
					count++;
				}
			}
			i++;
		} while (i < a1);
	}
	if (count != 0) {
		avg = sum * (1.0f / count);
		bonus = (1.0f / count) * bonus;
	}
	f = (float) (fcn_0050fdb0(*(unsigned short*) (a0 + 0x27), a1, a2) - 0.5);
	f = (float) (f * 0.25);
	if (*(unsigned char*) (a0 + 0x5b) & 0x10) {
		a = a + 0.1f;
	}
	f = (float) (f + a + (*(int*) (a0 + 0x41) - 2) * 0.1);
	return (bonus + avg) * f;
}
