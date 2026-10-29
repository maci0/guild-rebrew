#pragma pack(2)
typedef struct
{
	int hour;
	int minute;
	int second;
	short extra;
} fcn_005729e0_Clock;
#pragma pack()
// SIZE 0xe

int __cdecl fcn_0042e410(int code);
int __cdecl fcn_00500bb0(char* sel, int a, int b, int c);

/* ADDRESS: GOLDTL 0x005729e0 */
void __cdecl fcn_005729e0(char* p)
{
	*(fcn_005729e0_Clock*) (p + 0x52) = *(fcn_005729e0_Clock*) (p + 0x44);
	*(fcn_005729e0_Clock*) (p + 0x60) = *(fcn_005729e0_Clock*) (p + 0x44);
	fcn_00500bb0(p + 0x52, 7,
	    (fcn_0042e410(0x1e) & 0xffff) + 0x1e, 0);
}
