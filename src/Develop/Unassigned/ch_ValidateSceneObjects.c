extern void __cdecl ch_ValidateObjectTables(void);
extern int __cdecl d3_TraverseSceneNoop(void);

/* ADDRESS: GOLDTL 0x0042e400 */
int __cdecl ch_ValidateSceneObjects(void)
{
    ch_ValidateObjectTables();
    return d3_TraverseSceneNoop();
}
