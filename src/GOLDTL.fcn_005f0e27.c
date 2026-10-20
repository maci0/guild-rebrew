/* ADDRESS: GOLDTL 0x005f0e27 */
void __cdecl fcn_005f0e27(void *self, unsigned int a1, unsigned int a2)
{
    void *obj;

    obj = *(void **)((char *)self + 0x28);
    (*(void (__stdcall **)(void *, int, int, unsigned int, unsigned int))
      ((char *)(*(void **)obj) + 0x2c))(obj, 0, 0, a1, a2 | 0x800);
}
