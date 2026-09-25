// FUNCTION: GOLD 0x004adb20
// SIZE: 137
// FUNCTION: GOLDTL 0x4adc40
// SIZE: 137

extern int g_7728c0;
extern int g_7728c4;
extern int g_7728c8;
extern int g_7728cc;
extern int g_7728d0;

unsigned int __cdecl fcn_00430910(void*, int, int, void*);

int __cdecl fcn_004adc40(void* stream)
{
	if (!(fcn_00430910(&g_7728c0, 4, 1, stream) > 0))
		return 0;
	if (!(fcn_00430910(&g_7728c4, 4, 1, stream) > 0))
		return 0;
	if (!(fcn_00430910(&g_7728c8, 4, 1, stream) > 0))
		return 0;
	if (!(fcn_00430910(&g_7728cc, 4, 1, stream) > 0))
		return 0;
	return fcn_00430910(&g_7728d0, 4, 1, stream) > 0;
}
