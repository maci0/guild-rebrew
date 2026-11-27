
void __cdecl d2_TurnBookPages(void* obj, int n);

void __cdecl d2_TurnBookPagesBack(void* obj)
{
    d2_TurnBookPages(obj, -2);
}
