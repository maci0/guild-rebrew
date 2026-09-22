// FUNCTION: GOLDTL 0x004774a0
// SIZE: 16
/* Guarded COM call: if g_007725ec is set, call [ecx+0x1c] with it. */
extern int g_007725ec; /* 0x007725ec */
typedef void (__stdcall *comfn_t)(int self);

void __cdecl fcn_004774a0(void)
{
    int self = g_007725ec;
    if (self != 0) {
        ((comfn_t) *(void**) (*(int*) self + 0x1c))(self);
    }
}
