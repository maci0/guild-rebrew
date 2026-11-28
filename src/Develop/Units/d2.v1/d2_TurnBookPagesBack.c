
void __cdecl d2_TurnBookPages(void* obj, int n);

/* ADDRESS: GOLDDE 0x0051ddc0 */
void __cdecl d2_TurnBookPagesBack(void* obj)
{
    d2_TurnBookPages(obj, -2);
}
