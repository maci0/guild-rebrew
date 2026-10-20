#pragma pack(push, 1)
typedef struct
{
	int f00;
	int f04;
	int f08;
	short f0c;
} S54b820_Clock;
#pragma pack(pop)

extern S54b820_Clock g_7f4c00;

void __cdecl fcn_00500bb0(S54b820_Clock* clock, int arg2, int arg3, int arg4);
void __cdecl fcn_004c5530(int a1);
void __cdecl fcn_004c5620(int a1, char* e);
char* __cdecl fcn_00508e40(int a1);

/* ADDRESS: GOLDTL 0x0054b820 */
void __cdecl fcn_0054b820(char* e)
{
	char buf[0xf8];
	char* found;
	int i;

	*(int*) (e + 0x70) = 0;
	if ((e[0x78] & 4) != 0) {
		return;
	}
	*(S54b820_Clock*) (e + 0x52) = g_7f4c00;
	fcn_00500bb0((S54b820_Clock*) (e + 0x52), 0x18, 0, 0);
	*(short*) (e + 0x56) = 0x14;
	*(int*) (e + 0x58) = 0;
	if (*(int*) (e + 0xc0) == 1) {
		for (i = 0; i < 4; i++) {
			found = fcn_00508e40(*(int*) (e + 0xac + i * 4));
			if (found != 0) {
				buf[4] = 0x36;
				*(int*) (buf + 8) = *(int*) (found + 4);
				*(int*) (buf + 0xc) = -1;
				*(int*) (buf + 0x68) = 1;
				*(S54b820_Clock*) (buf + 0x58) = *(S54b820_Clock*) (e + 0x52);
				*(int*) (buf + 0x6c) = *(int*) (e + 4);
				if (found[2] == 6 || found[2] == 7) {
					buf[0x36] = 9;
				}
				else {
					buf[0x36] = 1;
				}
				fcn_004c5530((int) buf);
			}
		}
	}
	fcn_004c5620(0, e);
}
