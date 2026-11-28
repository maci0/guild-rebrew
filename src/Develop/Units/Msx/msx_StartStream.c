__declspec(dllimport) void __stdcall AIL_start_stream(int);
extern char msx_Initialized[];


int __cdecl msx_FindStreamIndex(int);
typedef void (__stdcall* fcn_0042ad60_f)(int);

/* ADDRESS: GOLDDE 0x004252d0 */
int __cdecl msx_StartStream(int a1)
{
	int result = 0;

	if (*(int*) &msx_Initialized != 0) {
		if (msx_FindStreamIndex(a1) >= 0) {
			AIL_start_stream(a1);
		} else {
			result = -1;
		}
	} else {
		result = -1;
	}
	return result;
}
