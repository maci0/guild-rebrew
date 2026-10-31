extern char g_7f4ca0[];
extern char* g_7e2aa0;
extern unsigned short g_774970;

typedef struct {
	unsigned char kind;
	char pad1[3];
	int a;
	int b;
	int c;
	int d;
	float f;
} Blk24;
// SIZE 0x18

char* __cdecl gm_LookupEntityRecordById(int);
float __cdecl fcn_004ff210(unsigned short, int);
int __cdecl fcn_0048fc30(int, char*, int, Blk24*, Blk24*);
char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
int __cdecl fcn_004a6210(char*, char*, int);
int __cdecl fcn_004a6550(char*, char*);
void __cdecl fcn_005e6650(char*);
void __cdecl fcn_005e5a50(int);
void __cdecl fcn_005e5ea0(int);
void __cdecl fcn_005e6360(int);
void __cdecl fcn_00586c10(int);
int __cdecl fcn_005e6e00(void);

/* ADDRESS: GOLDTL 0x005359c0 */
int __cdecl fcn_005359c0(void)
{
	char* o;
	char* e;
	Blk24 b1;
	Blk24 b2;

	switch (*(unsigned char*) 0x14cf950) {
	case 0x1e:
		return fcn_005e6e00();
	case 0x30:
		o = g_7e2aa0;
		if (o != 0) {
			fcn_005e5a50((int) o);
		}
		return;
	case 0x2e:
		o = g_7e2aa0;
		if (o != 0) {
			fcn_005e5ea0((int) o);
		}
		return;
	case 0x20:
		o = g_7e2aa0;
		if (o != 0) {
			fcn_005e6360((int) o);
		}
		return;
	case 0x12:
		o = g_7e2aa0;
		if (o != 0) {
			fcn_005e6650(o);
		}
		return;
	case 0x25:
		e = gm_LookupEntityRecordById(*(int*) (g_7f4ca0 + g_774970 * 0x21c + 0x60));
		if (e != 0) {
			fcn_004ff210(*(unsigned short*) e, -1000);
		} else {
			e = gm_LookupEntityRecordById(*(int*) (g_7f4ca0 + g_774970 * 0x21c + 0x60));
			if (e != 0) {
				fcn_004ff210(*(unsigned short*) e, -1000);
			}
		}
		return;
	case 0x14:
		if (g_7e2aa0 == 0) {
			return;
		}
		fcn_0048fc30(0, g_7f4ca0 + g_774970 * 0x21c, 0, &b2, &b1);
		return;
	case 0x16:
		o = g_7e2aa0;
		if (o == 0) {
			return;
		}
		e = gm_StartFilteredEntitySearch(1, 5, 0xf);
		if (e == 0) {
			return;
		}
		if (fcn_004a6210(g_7f4ca0 + g_774970 * 0x21c, o, (int) e) == 0) {
			return;
		}
		fcn_004a6550(g_7f4ca0 + g_774970 * 0x21c, o);
		return;
	case 0x2f:
		o = g_7e2aa0;
		if (o != 0) {
			fcn_00586c10((int) o);
		}
		break;
	}
	return;
}
