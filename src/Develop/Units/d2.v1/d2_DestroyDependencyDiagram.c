
void __cdecl d2_FreeWindowSlot(int value);

void __cdecl d2_DestroyDependencyDiagram(void)
{
    extern int g_00770af0;
    d2_FreeWindowSlot(g_00770af0);
}
