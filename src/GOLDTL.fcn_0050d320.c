extern char g_8680b4[];
// FUNCTION: GOLD 0x00509ee0
// FUNCTION: GOLDTL 0x0050d320

void* __cdecl fcn_00502cd0(int, int, int, ...);

int __cdecl fcn_0050d320(char* entity, char season)
{
	int result;
	char* r;

	result = 0;
	r = fcn_00502cd0(*(int*) (entity + 0x178), 1, result, (int) (unsigned short) ((int*)g_8680b4)[season * 189]);
	if (r) {
		result = *(int*) (r + 0xe);
	}
	return result;
}
