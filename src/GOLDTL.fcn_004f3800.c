// FUNCTION: GOLDTL 0x004f3800
// SIZE: 253

extern float g_665370;

char* __cdecl fcn_00502cd0(int obj, int mode, ...);

float __cdecl fcn_004f3800(char* o)
{
	int sum;

	sum = 0;
	if (fcn_00502cd0(*(int*) (o + 0x5d), 2, 6, 0, 0x1ff) != 0) {
		sum = 10;
	}
	if (fcn_00502cd0(*(int*) (o + 0x5d), 2, 6, 0, 0x202) != 0) {
		sum += 10;
	}
	if (fcn_00502cd0(*(int*) (o + 0x5d), 2, 6, 0, 0x208) != 0) {
		sum += 10;
	}
	if (fcn_00502cd0(*(int*) (o + 0x5d), 2, 6, 0, 0x20d) != 0) {
		sum += 15;
	}
	if (fcn_00502cd0(*(int*) (o + 0x5d), 2, 6, 0, 0x214) != 0) {
		sum += 10;
	}
	if (fcn_00502cd0(*(int*) (o + 0x5d), 2, 6, 0, 0x216) != 0) {
		sum += 10;
	}
	if (fcn_00502cd0(*(int*) (o + 0x5d), 2, 6, 0, 0x219) != 0) {
		sum += 15;
	}
	return sum * g_665370;
}
