#ifdef REBREW_GOLD
#define CAMERA_HELPER_LIST 0x5fb5b0
#define CAMERA_HELPER_CALLBACK 0x43b670
#else
#define CAMERA_HELPER_LIST 0x67a370
#define CAMERA_HELPER_CALLBACK 0x438a80
#endif

void __cdecl d3_VisitSceneObjects(int, int, int, int, int);

/* ADDRESS: GOLDDE 0x00431ca0 */
void __cdecl d3_InvalidateSubTreeFlags(int node, int clearBit)
{
	d3_VisitSceneObjects(*(int*) CAMERA_HELPER_LIST, node, 0x1ff, CAMERA_HELPER_CALLBACK, clearBit & 0xff);
}
