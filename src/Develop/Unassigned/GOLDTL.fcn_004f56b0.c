


typedef struct
{
	char b[0x2d];
} S2d;
// SIZE 0x2d

int __cdecl gs_FormatStraftatTextLow(int a, S2d s, int c);
int __cdecl fcn_004f5300(int a, S2d s, int c);
int __cdecl fcn_004f53a0(int a, S2d s, int c);

int __cdecl gs_FormatStraftatText(int output, S2d rec, int count)
{
	if ((unsigned char) rec.b[0x1c] < 9) {
		return gs_FormatStraftatTextLow(output, rec, count);
	}
	if ((unsigned char) rec.b[0x1c] < 0x11) {
		return fcn_004f5300(output, rec, count);
	}
	if ((unsigned char) rec.b[0x1c] < 0x1d) {
		return fcn_004f53a0(output, rec, count);
	}
	return 0;
}
