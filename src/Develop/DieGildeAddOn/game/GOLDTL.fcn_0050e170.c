
/* ADDRESS: GOLDTL 0x0050dfd0 */
/* 52 native calls supply an unused second dword; int is an inferred carrier. */
int __cdecl fcn_0050dfd0(char* a1, int unused)
{
	int n;

	if (*(unsigned short*) a1 == 0x1dd) {
		n = *(int*) (a1 + 0xe);
		return (n + 2) * 5;
	}
	n = *(int*) (a1 + 0xe);
	if (n == 3) {
		return 0x50;
	}
	return n * 20;
}

typedef struct ENT_50e170 ENT_50e170;
struct ENT_50e170 {
    unsigned char pad_000[0x14];
    int id;
    unsigned char pad_018[4];
    unsigned char f1c;
};

extern int __cdecl fcn_0050dfd0(char* a1, int a2);
extern unsigned short* __cdecl fcn_00502cd0(int container_id, int arg_count, ...);
extern int __cdecl gm_NextEntityQueryMatch(void);

/* ADDRESS: GOLDTL 0x0050e170 */
int __cdecl fcn_0050e170(ENT_50e170* p0, int a1, int a2)
{
    int total;
    int n;
    unsigned short* p;
    int i;

    total = fcn_0050dfd0((char*) p0, a1);
    p = fcn_00502cd0(p0->id, 1, 0, a1);
    if (p != 0) {
        n = total - *(int*) ((char*) p + 0xe);
        if (n > a2) {
            return a2;
        }
        return n;
    }
    i = 0;
    if (fcn_00502cd0(p0->id, 1, 5) != 0) {
        do {
            i++;
        } while (gm_NextEntityQueryMatch() != 0);
    }
    if (i >= (int) p0->f1c) {
        return 0;
    }
    if (total >= a2) {
        return a2;
    }
    return total;
}
