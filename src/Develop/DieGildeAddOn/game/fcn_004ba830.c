#include <string.h>

int __cdecl fcn_0042e410(int n);
char* __cdecl gm_LookupEntityRecordById(int id);
int __cdecl fcn_005c6270(char* rec, int mode);
int __cdecl fcn_00503fe0(int a, int b, int c);
int __cdecl fcn_00504bd0(int type);
char* __cdecl fcn_00503e80(void);
void __cdecl fcn_004c6ba0(int a, int id, int off);
void __cdecl io_FormatTextBuffer(char* buf, int fmt, int a, int b, int c, int d);
void __cdecl fcn_00545d40(int a, int b, char* buf, int overflow, int msg, int zero);

/* ADDRESS: GOLDTL 0x004ba830 */
int __cdecl fcn_004ba830(unsigned short* a0)
{
	char buf[0x100];
	int list[8];
	unsigned short* rec;
	unsigned short* slot;
	char* p;
	char* e;
	int pick;
	int count;
	int i;
	int n;
	int t;
	int v;

	count = 0;
	slot = 0;
	rec = (unsigned short*) gm_LookupEntityRecordById(*(int*) a0);
	if (rec == 0)
		return 1;
	if (fcn_005c6270((char*) rec, 0x290) == 0) {
		e = (char*) fcn_00503fe0(1, 3, (int) *rec);
		if (e != 0) {
			do {
				if (count >= 8)
					break;
				if (fcn_00504bd0((unsigned char) *e) == 1) {
					list[count] = (int) e;
					count++;
				}
				e = (char*) fcn_00503e80();
			} while (e != 0);
			if (count != 0) {
				pick = list[fcn_0042e410(count) & 0xffff];
				i = 0;
				for (p = (char*) 0x7f4e0c; (int) p < 0x85a20c; p += 0x21c, i++) {
					if (*(unsigned char*) (p - 0x16a) == 1 && *(int*) p == pick) {
						slot = (unsigned short*) (0x7f4ca0 + i * 0x21c);
						break;
					}
				}
				if (pick != 0 && slot != 0) {
					n = *(unsigned char*) ((char*) slot + 0x81);
					if (n > 0) {
						t = (fcn_0042e410(10) & 0xffff) + 5;
						if (n < t)
							v = n;
						else
							v = (fcn_0042e410(10) & 0xffff) + 5;
						fcn_004c6ba0(*(int*) (slot + 2), 1, -(int) (signed char) v);
						io_FormatTextBuffer(buf, *(unsigned short*) ((char*) a0 + 4) + 0x12e7,
						    *slot, pick, *slot, 0x16b8);
						fcn_00545d40(*(int*) (rec + 2), *(int*) (rec + 2), buf,
						    0x100 < strlen(buf), 0x603, 0);
						return 0;
					}
				}
			}
		}
	}
	return 0x400;
}
