extern int g_8680b4[];
// FUNCTION: GOLD 0x00509ee0
// SIZE: 64
// FUNCTION: GOLDTL 0x0050d320
// SIZE: 64

void* __cdecl fcn_00502cd0(int, int, int, ...);

int __cdecl fcn_0050d320(char* entity, char season)
{
	int result;
	char* r;

	result = 0;
	r = fcn_00502cd0(*(int*) (entity + 0x178), 1, result, (int) (unsigned short) g_8680b4[season * 189]);
	if (r) {
		result = *(int*) (r + 0xe);
	}
	return result;
}
