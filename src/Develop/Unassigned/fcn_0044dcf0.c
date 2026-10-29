extern void __cdecl fcn_004011f0(void *p, void *field);
extern void *__cdecl fcn_0041db70(int size, void *pool);
extern char g_0067b854;

/* ADDRESS: GOLDTL 0x0044dcf0 */
void __cdecl fcn_0044dcf0(void *p, char *obj)
{
    int count;

    fcn_004011f0(p, obj + 0xc);
    count = *(int *)(obj + 0xc);
    *(int *)(obj + 8) = 0;
    if (count > 0)
        *(void **)(obj + 0x10) = fcn_0041db70(count * 224, &g_0067b854);
}
