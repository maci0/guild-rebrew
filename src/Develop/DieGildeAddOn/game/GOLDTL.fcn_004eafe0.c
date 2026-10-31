/* Rec: 0x18-byte producer record (client_types.h Rec18_68da68). */
typedef struct Rec {
	unsigned char id;
	char pad1[3];
	int x4;
	unsigned char type;
	char pad9[3];
	int xc;
	unsigned char x10;
	char pad11[7];
} Rec;
/* SIZE 0x18 */

int __cdecl fcn_004e8cb0(int all, int max, Rec* out);
unsigned char* __cdecl gm_LookupEntityRecordById(int id);
void __cdecl fcn_004ea560(Rec* r, int type);
int __cdecl fcn_004e8240(unsigned char id, unsigned char* ea, unsigned char* eb, int x1, int x2);
int __cdecl fcn_004c4450(int v);
void __cdecl fcn_00535960(void);
int __cdecl fcn_005463a0(int, int, int);
void __cdecl amt_calc_zuenfte(int n);
void __cdecl fcn_004ea620(void);
void __cdecl fcn_004ea9a0(void);

/* ADDRESS: GOLDTL 0x004eafe0 */
void __cdecl fcn_004eafe0(void)
{
	Rec out[7];
	unsigned char* q;
	unsigned char t;
	int n;
	int i;
	int k;
	int lo;
	int hi;
	int v;
	int x;
	int tt;

	n = fcn_004e8cb0(1, 7, out);
	if (n > 0) {
		for (i = 0; i < n; i++) {
			x = out[i].x4;
			if (x == -1) {
				continue;
			}
			t = out[i].type;
			tt = out[i].type;
			switch (tt) {
			case 0x1c:
				lo = 1;
				hi = 6;
				break;
			case 0x1d:
				lo = 0x28;
				hi = 0x2d;
				break;
			case 0x1e:
				lo = 0x22;
				hi = 0x27;
				break;
			case 0x1f:
				lo = 0x2e;
				hi = 0x33;
				break;
			case 0x20:
				lo = 0x3a;
				hi = 0x3f;
				break;
			case 0x21:
				lo = 0x40;
				hi = 0x45;
				break;
			case 0x22:
				lo = 0xd;
				hi = 0x12;
				break;
			default:
				continue;
			}
			q = gm_LookupEntityRecordById(x);
			if (q == 0)
				goto body;
			if (q[8] == 0)
				goto body;
			if (q[0x169] == t) {
				k = q[0x164];
				if (k >= lo && k <= hi)
					goto skip;
			}
		body:
			fcn_004ea560((Rec*) q, tt);
			v = fcn_004e8240(out[i].id, 0, 0, 4, 0xff);
			while (v != -1 && fcn_004c4450(v) == 0) {
				fcn_00535960();
			}
		skip:
			;
		}
	}
	if (fcn_005463a0(1, 0, 0x80) == 0) {
		amt_calc_zuenfte(0x1e);
		amt_calc_zuenfte(0x1f);
		amt_calc_zuenfte(0x20);
		amt_calc_zuenfte(0x21);
	}
	fcn_004ea620();
	fcn_004ea9a0();
}
