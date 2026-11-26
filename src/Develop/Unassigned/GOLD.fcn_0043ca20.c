extern char* d3_ActiveCamera;
extern char* g_fc28f4;
extern char g_fc2700[];
extern int g_67a370;

void __cdecl d3_SetActiveCamera(char*);
void __cdecl d3_SetObjectRotation(char*, char*);

/* ADDRESS: GOLD 0x0043ca20 */
void __cdecl fcn_0043ca20(char* o)
{
	if (*(int*) (o + 0x218) == 3 && d3_ActiveCamera == 0) {
		d3_SetActiveCamera(o);
		d3_SetObjectRotation(o, o + 0x84);
	}
	if (*(int*) (o + 0x218) != 0) {
		*(char**) (o + 0x1f4) = g_fc28f4;
		*(char**) (o + 0x1f0) = g_fc2700;
		*(char**) (g_fc28f4 + 0x1f0) = o;
		g_fc28f4 = o;
		o[0x210] |= 3;
	}
	*(int*) (o + 0x208) = g_67a370;
}
