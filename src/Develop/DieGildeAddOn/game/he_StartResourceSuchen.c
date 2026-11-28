#pragma pack(2)
typedef struct
{
	int hour;
	int minute;
	int second;
	short extra;
} ACTION_CLOCK14;
#pragma pack()
// SIZE 0xe

int __cdecl fcn_0042e410(int code);
int __cdecl gm_AddTime(char* sel, int a, int b, int c);

/* ADDRESS: GOLDTL 0x005729e0 */
/* ADDRESS: GOLDDE 0x00558970 */
void __cdecl he_StartResourceSuchen(char* p)
{
	*(ACTION_CLOCK14*) (p + 0x52) = *(ACTION_CLOCK14*) (p + 0x44);
	*(ACTION_CLOCK14*) (p + 0x60) = *(ACTION_CLOCK14*) (p + 0x44);
	gm_AddTime(p + 0x52, 7,
	    (fcn_0042e410(0x1e) & 0xffff) + 0x1e, 0);
}
