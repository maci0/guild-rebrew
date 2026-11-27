
// fcn_004c8990 — fcn_0052fb80(0x53bd80); if(arg2) *arg2=1; return 0.

int __cdecl main_ExitToFrameHandler(int);

int __cdecl cm_ExExitToFrameLoop(int unused, char* result)
{
	(void) unused;
	main_ExitToFrameHandler(0x53bd80);
	if (result != 0) {
		*result = 1;
	}
	return 0;
}
