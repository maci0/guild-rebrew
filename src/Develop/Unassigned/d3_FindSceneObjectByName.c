extern int g_6b5cc4;
extern int g_67a370;



void __cdecl d3_VisitSceneObjects(int, int, int, void*, int);
void __cdecl d3_MatchObjectNameCallback(void);

int __cdecl d3_FindSceneObjectByName(int a1, int flags)
{
	g_6b5cc4 = 0;
	if (flags & 2) {
		d3_VisitSceneObjects(g_67a370, 0, 0x1e0, d3_MatchObjectNameCallback, a1);
		return g_6b5cc4;
	}
	d3_VisitSceneObjects(g_67a370, 0, 0x60, d3_MatchObjectNameCallback, a1);
	return g_6b5cc4;
}
