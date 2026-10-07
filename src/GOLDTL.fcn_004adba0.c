// FUNCTION: GOLD 0x004ada80
// FUNCTION: GOLDTL 0x4adba0

extern int g_7728c0;
extern int g_7728c4;
extern int g_7728c8;
extern int g_7728cc;
extern int g_7728d0;

int __cdecl ls_ReadVfsDataChecked(void* outBuffer, int elementSize, int elementCount, void* streamCtx);

int __cdecl fcn_004adba0(void* stream)
{
	if (!ls_ReadVfsDataChecked(&g_7728c0, 4, 1, stream)) {
		g_7728d0 = g_7728cc = g_7728c4 = g_7728c8 = g_7728c0 = -1;
		return 0;
	}
	if (!ls_ReadVfsDataChecked(&g_7728c4, 4, 1, stream)) {
		g_7728d0 = g_7728cc = g_7728c4 = g_7728c8 = g_7728c0 = -1;
		return 0;
	}
	if (!ls_ReadVfsDataChecked(&g_7728c8, 4, 1, stream)) {
		g_7728d0 = g_7728cc = g_7728c4 = g_7728c8 = g_7728c0 = -1;
		return 0;
	}
	if (!ls_ReadVfsDataChecked(&g_7728cc, 4, 1, stream)) {
		g_7728d0 = g_7728cc = g_7728c4 = g_7728c8 = g_7728c0 = -1;
		return 0;
	}
	if (!ls_ReadVfsDataChecked(&g_7728d0, 4, 1, stream)) {
		g_7728d0 = g_7728cc = g_7728c4 = g_7728c8 = g_7728c0 = -1;
		return 0;
	}
	return 1;
}
