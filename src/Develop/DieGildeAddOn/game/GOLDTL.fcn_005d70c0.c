


#include <string.h>

typedef struct
{
	int x0;
	int x4;
	__int64 mask;
	int x10;
	char pad14[0x3c];
} Query;
// SIZE 0x50

extern __int64 g_666018;

char* __cdecl gm_LookupEntityRecordById(int);
int __cdecl gm_CalcBecircenFavor(char*, char*, int);
void __cdecl cm_RequestModifyHealth(int, int);
void __cdecl cm_RequestCopyEntityData(int, int, int, int);
void __cdecl io_FormatTextBuffer(void*, int, ...);
int __cdecl d2_OpenTargetPicker(Query*, char*, int, void*);
int __cdecl d2_ShowBecircenDialog(unsigned short*);

int __cdecl gm_HandleBecircen(char* e, char* o)
{
	int r;
	int n;
	int v;
	char* p;

	r = 0;
	if (e[2] != 6 && e[2] != 7) {
		n = *(int*) (o + 4);
		if (*(int*) (e + 0x194) < n || n < 1 || n > 5) {
			return 0x60;
		}
		p = gm_LookupEntityRecordById(*(int*) (o + 0x214));
		if (p == 0) {
			return 0x60;
		}
		n = *(int*) (o + 4);
		v = gm_CalcBecircenFavor(e, p, n);
		cm_RequestModifyHealth(*(int*) (e + 4), -n);
		cm_RequestCopyEntityData(*(int*) (e + 4), *(int*) (p + 4), v, 1);
		return 0x10;
	} else {
		Query q;
		char buf[0x40];

		memset(&q, 0, sizeof(q));
		q.x4 = 0x400;
		q.x10 = 6;
		q.mask = g_666018;
		if (e[9] == 0) {
			io_FormatTextBuffer(buf, 0x1dae, 0x1daf);
		} else {
			io_FormatTextBuffer(buf, 0x1dae, 0x1db0);
		}
		if (d2_OpenTargetPicker(&q, buf, 0, (void*) d2_ShowBecircenDialog) != 0) {
			r = 1;
		}
	}
	return r;
}
