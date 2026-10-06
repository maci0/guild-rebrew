// FUNCTION: GOLDTL 0x00418d20

void* __cdecl fcn_00445600(int a, int b, int c, int d);
void* __cdecl fcn_00422460(int a, int b);
int __cdecl fcn_00418c80(void* a, void* b, int c, int d);

int __cdecl fcn_00418d20(int a1, int a2, int a3, int a4)
{
	void* p;
	void* q;
	int r;

	r = 0;
	p = fcn_00445600(0, 0x140, 0, a2);
	if (p != 0) {
		q = fcn_00422460(0, a1);
		if (q != 0) {
			r = fcn_00418c80(q, p, a3, a4);
		}
	}
	return r;
}
