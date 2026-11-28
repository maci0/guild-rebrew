/* Import-thunk forwarder: pushes its arg straight into the IAT slot
 * at 0x005eb008 (GOLD) / 0x00662010 (GOLDTL). Declared via function pointer
 * so the call emits `call dword [0x...]` rather than a direct rel32. */
typedef void (__stdcall *thunk_t)(int);

#if defined(REBREW_GOLD)
/* ADDRESS: GOLD 0x00410430 */
void __cdecl io_CloseRegistryKey(int value)
{
    ((thunk_t) *(void**) 0x005eb008)(value);
}
#else
/* ADDRESS: GOLDTL 0x00411340 */
/* ADDRESS: GOLDDE 0x00410140 */
void __cdecl io_CloseRegistryKey(int value)
{
    ((thunk_t) *(void**) 0x00662010)(value);
}
#endif
