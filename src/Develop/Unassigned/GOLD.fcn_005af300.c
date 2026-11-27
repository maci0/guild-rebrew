
/* Lua getupvalue-style forwarder: f(obj, 2). Callee at 0x005af320. */
void __cdecl d2_RunTradeTransportPanel(void* obj, int n);

void __cdecl d2_ShowTradeTransportMode2(void* obj)
{
    d2_RunTradeTransportPanel(obj, 2);
}
