// FUNCTION: GOLD 0x004ea550
// SIZE: 108
// FUNCTION: GOLDTL 0x004ec2d0
// SIZE: 108

typedef struct
{
	int x0;
	int id;
	char pad[0x10];
} Rec18;
// SIZE 0x18

int __cdecl fcn_004e8b80(int kind, int max, Rec18* out);
void __cdecl fcn_004c54c0(int a, int b, int c, int d);

void __cdecl fcn_004ec2d0(char* p, int kind, int arg)
{
	Rec18 recs[6];
	int n;
	int i;

	if (kind < 1 || kind > 7) {
		return;
	}
	n = fcn_004e8b80(kind, 6, recs);
	for (i = 0; i < n; i++) {
		if (recs[i].id != *(int*) (p + 4) && recs[i].id != -1) {
			fcn_004c54c0(*(int*) (p + 4), recs[i].id, arg, 1);
		}
	}
}
