


typedef struct
{
	char b[0x2d];
} S2d;
// SIZE 0x2d

int __cdecl gs_FormatStraftatTextLow(int a, S2d s, int c);
int __cdecl gs_FormatStraftatTextMid(int a, S2d s, int c);
int __cdecl gs_FormatStraftatTextHigh(int a, S2d s, int c);

/* ADDRESS: GOLDDE 0x004e1750 */
int __cdecl gs_FormatStraftatText(int output, S2d rec, int count)
{
	if ((unsigned char) rec.b[0x1c] < 9) {
		return gs_FormatStraftatTextLow(output, rec, count);
	}
	if ((unsigned char) rec.b[0x1c] < 0x11) {
		return gs_FormatStraftatTextMid(output, rec, count);
	}
	if ((unsigned char) rec.b[0x1c] < 0x1d) {
		return gs_FormatStraftatTextHigh(output, rec, count);
	}
	return 0;
}
