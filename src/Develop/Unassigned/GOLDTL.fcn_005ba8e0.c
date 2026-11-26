
void __cdecl d2_RunTradeInventoryPanel(void* obj, int n);

void __cdecl d2_OpenTransportPanel(void* obj)
{
    d2_RunTradeInventoryPanel(obj, 1);
}
