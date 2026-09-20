// FUNCTION: GOLD 0x005e19ef
/* Vtable-thunk: add 4 to *arg, reload, return *(arg-4). COM-style.
 * Wall: reference keeps eax live across `add [eax],4` + two loads (13B);
 * the param-slot reload costs a second mov (17B) under every spelling tried.
 * Parked. */
int __cdecl fcn_005e19ef(int* obj)
{
    *obj += 4;
    return ((int*) *obj)[-1];
}
