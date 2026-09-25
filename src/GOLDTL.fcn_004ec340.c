// FUNCTION: GOLDTL 0x004ec340
// SIZE: 208

typedef struct
{
	int x0;
	int id;
	char pad[0x10];
} Rec18;

extern float g_662910;
extern float g_6628a8;

int __cdecl fcn_004e8b80(int kind, int max, Rec18* out);
unsigned short* __cdecl fcn_00508e40(int id);
double __cdecl fcn_0050f980(int a, int b, int c);

float __cdecl fcn_004ec340(unsigned short* p, int kind)
{
	Rec18 recs[6];
	float sum;
	int count;
	int n;
	int i;
	unsigned short* q;

	sum = 0;
	if (kind < 1 || kind > 7) {
		return g_6628a8;
	}
	n = fcn_004e8b80(kind, 6, recs);
	count = 0;
	for (i = 0; i < n; i++) {
		if (recs[i].id != *(int*) (p + 2) && recs[i].id != -1) {
			q = fcn_00508e40(recs[i].id);
			if (q != 0) {
				sum += fcn_0050f980(*p, *q, 1) * g_662910;
				count++;
			}
		}
	}
	if (count != 0) {
		sum = sum / count;
	}
	return sum;
}
