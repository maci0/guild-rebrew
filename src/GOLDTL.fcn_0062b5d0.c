/* D3DX8 band (external_ranges 0x5e0000-0x64ffff): C++ library code. The
 * callees are thiscall members (self in ecx, one stack argument, callee
 * pops). C89 has no __thiscall, so they are declared __fastcall with a
 * dummy register argument to keep the stack argument and ret N identical.
 */
extern void *g_775f60;

void *__cdecl iswupper(int size);
void *__fastcall fcn_0062abf8(void *self);
int __fastcall fcn_0062af7c(void *self, int ignored, int arg);
void __fastcall fcn_0062ad3f(void *self, int ignored, int arg);

int __cdecl fcn_0062b5d0(int id, void **out)
{
    void **p;
    void *mem;
    void *obj;
    int hr;

    p = (void **)g_775f60;
    while (p != 0) {
        if ((int)p[1] == id) {
            p[0] = (void *)((int)p[0] + 1);
            *out = p;
            return 0;
        }
        p = (void **)p[0x2b];
    }
    mem = iswupper(0xb0);
    obj = (void *)0;
    if (mem != 0)
        obj = fcn_0062abf8(mem);
    if (obj == 0)
        return (int)0x8007000e;
    hr = fcn_0062af7c(obj, 0, id);
    if (hr < 0) {
        fcn_0062ad3f(obj, 0, 1);
        return hr;
    }
    *out = obj;
    return 0;
}
