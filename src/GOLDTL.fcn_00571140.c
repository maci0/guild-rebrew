#pragma pack(push, 2)
typedef struct {
	int a;
	int b;
	int c;
	short d;
} Cpy14;
#pragma pack(pop)

double __cdecl fcn_0050fdb0(int, int, void*);
int __cdecl gm_SearchTable67(int);
void __cdecl fcn_00529160(int, int, int, void*);
void __cdecl fcn_00500bb0(void*, int, int, int);

/* ADDRESS: GOLDTL 0x00571140 */
void __cdecl fcn_00571140(char* obj)
{
	int value;
	int id;
	Cpy14* dst;
	char* p;

	value = *(int*) (*(unsigned short*) (obj + 0xac) * 0x41 + 0x22 + *(int*) 0x99ec10);
	*(int*) (obj + 0xb0) = value;
	dst = (Cpy14*) (obj + 0x52);
	*dst = *(Cpy14*) (obj + 0x44);
	*(Cpy14*) (obj + 0x60) = *(Cpy14*) (obj + 0x44);
	*(float*) (obj + 0xb4) = (float) value;
	*(float*) (obj + 0xc4) = (float) ((fcn_0050fdb0(*(unsigned short*) (obj + 8), 8, obj + 0x8c) - *(double*) 0x662908) * *(double*) 0x662ad8);
	*(char*) (obj + 0xc8) = 0;
	id = gm_SearchTable67(*(int*) (obj + 0xb8));
	for (p = (char*) 0x7f4ca0; (int) p < 0x85a0a0; p += 0x21c) {
		if (*(int*) (p + 0x17c) == (int) obj) {
			fcn_00529160(id, 0, *(unsigned short*) p, obj);
		}
	}
	fcn_00500bb0(dst, 0, 0, 1);
}
