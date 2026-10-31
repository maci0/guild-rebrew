typedef struct Node {
	char pad0[0x52];
	char f52[0x1e];
	int f70;
	char pad74[0x38];
	int fac;
	int fb0;
} Node;
/* SIZE 0xb4 */

void* __cdecl gm_LookupEntityRecordById(int a);
void __cdecl fcn_005100f0(int a, int b);
void __cdecl fcn_00500bb0(char* p, int a, int b, int c);
void __cdecl fcn_00546190(Node* n);

/* ADDRESS: GOLDTL 0x0057c7b0 */
void __cdecl fcn_0057c7b0(Node* o)
{
	int n;
	void* a;
	void* b;
	int h;
	int m;

	n = o->f70;
	if (n == -1 || n == -2) {
		fcn_00546190(o);
		return;
	}
	o->f70 = n + 1;
	a = gm_LookupEntityRecordById(o->fb0);
	b = gm_LookupEntityRecordById(o->fac);
	if (a == 0) {
		fcn_00546190(o);
		return;
	}
	h = *(int*) ((char*) a + 0x194);
	if (h != 0) {
		fcn_005100f0(*(int*) ((char*) a + 4), -h);
		m = h / 2;
		if (m <= 2) {
			m = 2;
		}
		if (b != 0) {
			fcn_005100f0(*(int*) ((char*) b + 4), m);
		}
	}
	if (o->f70 < 2) {
		fcn_00500bb0(o->f52, 0x18, 0, 0);
		return;
	}
	fcn_00546190(o);
}
