// FUNCTION: GOLD 0x005e1a0c
// SIZE: 14
/* Vtable-thunk, word-sized id: add 4, reload, return *(short*)(arg-4). */
int __cdecl fcn_005e1a0c(int* obj)
{
    *obj += 4;
    return *(short*) ((char*) *obj - 4);
}
