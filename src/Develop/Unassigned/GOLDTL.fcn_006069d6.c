/* COM class-factory create path.  `mode` (arg 4, bit 0) selects which of the
 * two 0x54-byte implementations is constructed and initialised; both arms
 * share operator new (0x6508ff), the out-of-memory result 0x8007000e and the
 * final "*out = object" store.
 *
 * Native ABI is __stdcall with 7 arguments (ret 0x1c) and the constructors,
 * the initialisers and the releasing destructors all take their object in
 * ECX (__thiscall).  MSVC 6 C rejects __thiscall (C4234), so this C89
 * reconstruction keeps the algorithm and the argument order but cannot
 * reproduce the register-passed object. */
extern void *__cdecl iswupper(unsigned size);
extern void *__cdecl fcn_005fc0c8(void *self);
extern void *__cdecl fcn_005fc10c(void *self);
extern int __cdecl fcn_005fc008(void *self, int flags);
extern int __cdecl fcn_005fc024(void *self, int flags);
extern int __cdecl fcn_0060223c(void *self, int a1, int a2, int a3, int a4,
                                 int a5);
extern int __cdecl fcn_006022c0(void *self, int a1, int a2, int a3, int a4,
                                 int a5);

/* ADDRESS: GOLDTL 0x006069d6 */
int __cdecl fcn_006069d6(int a1, int a2, int a3, int mode, int a4, int a5,
                         void **out)
{
    void *obj;
    int hr;

    obj = iswupper(0x54);
    if ((mode & 1) != 0) {
        if (obj != 0) {
            obj = fcn_005fc0c8(obj);
        } else {
            obj = 0;
        }
        if (obj == 0) {
            return 0x8007000e;
        }
        hr = fcn_0060223c(obj, a1, a2, a3, a4, a5);
        if (hr < 0) {
            fcn_005fc008(obj, 1);
            return hr;
        }
    } else {
        if (obj != 0) {
            obj = fcn_005fc10c(obj);
        } else {
            obj = 0;
        }
        if (obj == 0) {
            return 0x8007000e;
        }
        hr = fcn_006022c0(obj, a1, a2, a3, a4, a5);
        if (hr < 0) {
            fcn_005fc024(obj, 1);
            return hr;
        }
    }
    *out = obj;
    return 0;
}
