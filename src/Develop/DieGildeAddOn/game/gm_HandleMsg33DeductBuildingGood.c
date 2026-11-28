#include <string.h>

typedef struct GM_MSG33_REQUEST {
	int id;
	unsigned short f4;
} GM_MSG33_REQUEST;

int __cdecl fcn_0042e410(int a0);
unsigned char* __cdecl gm_LookupEntityRecordById(int id);
int __cdecl gm_HasActiveSpecialObject(void* p, int n);
int __cdecl gm_DeductRandomBuildingGood(void* q, int* out, float f);
int __cdecl fcn_00503fe0(int a0, int a1, int a2);
void __cdecl io_FormatTextBuffer(char* out, int fmt, ...);
void __cdecl fcn_00545e80(int a0, int a1, char* s, int flag, int a4,
                         int a5, int a6, int a7, int a8);

/* ADDRESS: GOLDTL 0x004bae40 */
/* ADDRESS: GOLDDE 0x004a8ee0 */
int __cdecl gm_HandleMsg33DeductBuildingGood(GM_MSG33_REQUEST* request)
{
	int n;
	float f0;
	int v;
	char buf[0x200];
	unsigned char* q;
	int h;
	unsigned int len;
	int flag;
	double d;

	n = fcn_0042e410(0xf) & 0xffff;
	d = (double) n + 5.0;
	f0 = (float) (d * 0.01);
	q = gm_LookupEntityRecordById(request->id);
	if (q == 0) {
		return 1;
	}
	if (gm_HasActiveSpecialObject(q, 0x290) == 0) {
		if (gm_DeductRandomBuildingGood(q, &v, f0) != 0) {
			h = fcn_00503fe0(1, 1, v);
			if (h != 0) {
				io_FormatTextBuffer(buf, request->f4 + 0x12e7, h,
				             (int) (f0 * 1e+02f));
				len = strlen(buf);
				fcn_00545e80(*(int*) ((char*) q + 4), *(int*) ((char*) q + 4),
				             buf, 0x100 < len, 0x603, *(int*) ((char*) h + 1), -1, 0, 0);
				return 0;
			}
		}
	}
	return 0x400;
}
