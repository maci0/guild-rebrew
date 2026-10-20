#pragma pack(push, 1)
/* SIZE 0x24d */
typedef struct {
	char pad0[0x23];
	unsigned short ids[0x40];
	char pad_a3[0x1a6];
	int value;
} Lvl50cf;

/* SIZE 0x41 */
typedef struct {
	unsigned char kind;
	char pad1[0x40];
} Kind50cf;
#pragma pack(pop)

extern unsigned char* g_868050;
extern char* g_99ec10;
extern float g_662910;

float __cdecl fcn_0050b980(int, unsigned char);
char* __cdecl fcn_00502cd0(int, int, int, int);

/* ADDRESS: GOLDTL 0x0050cf50 */
int __cdecl fcn_0050cf50(unsigned char* a0, int a1)
{
	Lvl50cf* lvl;
	char* t;
	char* q;
	unsigned char k;
	unsigned char flag;
	/* two slots: the native frame is 8 bytes while only one holds the
	   int/float accumulator pun at [ebp-8] */
	int acc[2];
	int i;
	int id;

	lvl = (Lvl50cf*) (g_868050 + a0[0] * 0x24d);
	acc[0] = lvl->value * 0xf00;
	t = 0;
	flag = 0;
	for (i = 0; i < 0x40; i++) {
		if (lvl->ids[i] == 0) {
			break;
		}
		id = lvl->ids[i] & 0x7fff;
		k = ((Kind50cf*) g_99ec10)[id].kind;
		if (!flag) {
			if (k == 2 || k == 6) {
				t = fcn_00502cd0(*(int*) (a0 + 0x5d), 1, 0, id);
				if (t != 0) {
					acc[0] = (int) (*(float*) &acc[0] + fcn_0050b980(*(unsigned short*) t, *(unsigned char*) (t + 0x12)));
					if (i < 0x3f) {
						k = ((Kind50cf*) g_99ec10)[lvl->ids[i + 1] & 0x7fff].kind;
						if (k != 2 && k != 6) {
							flag = 1;
						}
					}
				}
			}
		} else {
			if (t != 0) {
				q = fcn_00502cd0(*(int*) (t + 0x14), 1, 0, id);
				if (q != 0) {
					acc[0] = (int) (*(float*) &acc[0] + fcn_0050b980(*(unsigned short*) q, *(unsigned char*) (q + 0x12)));
				}
				if (i < 0x3f) {
					k = ((Kind50cf*) g_99ec10)[lvl->ids[i + 1] & 0x7fff].kind;
					if (k == 2 || k == 6) {
						flag = 0;
					}
				}
			}
		}
	}
	return (int) (acc[0] * (g_662910 * a1));
}
