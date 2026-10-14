

int __cdecl fcn_004e8b80(int, int, void*);
int __cdecl fcn_00508e40(int);

// SIZE 0x18
typedef struct {
	int a;
	int id;
	int pad[4];
} Slot;

int __cdecl fcn_005bd7c0(int max, int a, int* out)
{
	int n;
	int cnt;
	int i;
	int r;

	n = fcn_004e8b80(a, 6, (void*) 0x775288);
	cnt = 0;
	for (i = 0; i < n; i++) {
		if (cnt >= max) {
			break;
		}
		r = fcn_00508e40(((Slot*) 0x775288)[i].id);
		if (r != 0) {
			out[cnt++] = r;
		}
	}
	return cnt;
}
