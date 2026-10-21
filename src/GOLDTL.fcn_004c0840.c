typedef struct Rec24 {
	int v[6];
} Rec24;
// SIZE 0x18

typedef struct Rec64 {
	int id;
	int kind;
	Rec24 a;
	Rec24 b;
} Rec64;
// SIZE 0x40

int __cdecl fcn_005218f0(void* dst, int size, int count, int handle);
void* __cdecl m_alloc(int size, char* file);
void __cdecl m_FreeTracked(void* p);
int __cdecl fcn_00501510(int id);
char* __cdecl fcn_004be1f0(int head);

/* ADDRESS: GOLDTL 0x004c0840 */
/* Reads a table of 0x40-byte records and appends each record to its owner list. */
int __cdecl fcn_004c0840(int handle)
{
	Rec64* rec;
	char* buf;
	char* x;
	char* dst;
	int n;
	int i;
	int k;

	n = handle;
	if (fcn_005218f0(&n, 4, 1, handle) == 0)
		return 0;
	buf = (char*) m_alloc(n * 0x40, (char*) 0x681748);
	for (i = 0; i < n; i++) {
		rec = (Rec64*) (buf + i * 0x40);
		if (fcn_005218f0(&rec->id, 4, 1, handle) == 0)
			return 0;
		if (fcn_005218f0(&rec->kind, 4, 1, handle) == 0)
			return 0;
		if (fcn_005218f0(&rec->a, 0x18, 1, handle) == 0)
			return 0;
		if (fcn_005218f0(&rec->b, 0x18, 1, handle) == 0)
			return 0;
	}
	for (i = 0; i < n; i++) {
		rec = (Rec64*) (buf + i * 0x40);
		x = (char*) fcn_00501510(rec->id);
		*(int*) (x + 0x29) = 0;
		do {
			dst = (char*) fcn_004be1f0(*(int*) (x + 0x29));
			if (*(int*) (x + 0x29) == 0)
				*(int*) (x + 0x29) = (int) dst;
			*(int*) (dst + 4) = rec->kind;
			*(int*) dst = rec->id;
			*(Rec24*) (dst + 8) = rec->a;
			*(Rec24*) (dst + 0x20) = rec->b;
			i++;
			rec = (Rec64*) ((char*) rec + 0x40);
		} while (i < n && rec != 0 && *(int*) (x + 2) == rec->id);
	}
	m_FreeTracked(buf);
	return 1;
}
