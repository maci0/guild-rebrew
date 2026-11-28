extern char gm_EntitySlotTable[];
#include <string.h>

int __cdecl fcn_0042e410(int n);
char* __cdecl gm_LookupEntityRecordById(int id);
int __cdecl gm_HasActiveSpecialObject(char* rec, int mode);
int __cdecl fcn_00503fe0(int a, int b, int c);
int __cdecl fcn_00504bd0(int type);
char* __cdecl fcn_00503e80(void);
void __cdecl cm_RequestModifyEntityLevel(int a, int id, int off);
void __cdecl io_FormatTextBuffer(char* buf, int fmt, int a, int b, int c, int d);
void __cdecl he_PostEntityMessage(int a, int b, char* buf, int overflow, int msg, int zero);

/* ADDRESS: GOLDTL 0x004ba830 */
/* ADDRESS: GOLDDE 0x004a88d0 */
int __cdecl gm_HandleMsg30DamageWorker(unsigned short* request)
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
	rec = (unsigned short*) gm_LookupEntityRecordById(*(int*) request);
	if (rec == 0)
		return 1;
	if (gm_HasActiveSpecialObject((char*) rec, 0x290) == 0) {
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
				for (p = (char*) ((int) &gm_EntitySlotTable + 0x16c); (int) p < ((int) &gm_EntitySlotTable + 0x6556c); p += 0x21c, i++) {
					if (*(unsigned char*) (p - 0x16a) == 1 && *(int*) p == pick) {
						slot = (unsigned short*) ((int) &gm_EntitySlotTable + i * 0x21c);
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
						cm_RequestModifyEntityLevel(*(int*) (slot + 2), 1, -(int) (signed char) v);
						io_FormatTextBuffer(buf, *(unsigned short*) ((char*) request + 4) + 0x12e7,
						    *slot, pick, *slot, 0x16b8);
						he_PostEntityMessage(*(int*) (rec + 2), *(int*) (rec + 2), buf,
						    0x100 < strlen(buf), 0x603, 0);
						return 0;
					}
				}
			}
		}
	}
	return 0x400;
}
