#ifdef REBREW_GOLD
#define CAMERA_HELPER_LIST 0x5fb5b0
#define CAMERA_HELPER_CALLBACK 0x43b670
#else
#define CAMERA_HELPER_LIST 0x67a370
#define CAMERA_HELPER_CALLBACK 0x438a80
#endif

void __cdecl fcn_004379a0(int, int, int, int, int);

void __cdecl fcn_00438ac0(int a1, int a2)
{
	fcn_004379a0(*(int*) CAMERA_HELPER_LIST, a1, 0x1ff, CAMERA_HELPER_CALLBACK, a2 & 0xff);
}
