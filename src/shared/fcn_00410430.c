// FUNCTION: GOLDTL 0x411340
// SIZE: 12


/* Import-thunk forwarder: pushes its arg straight into the IAT slot
 * at 0x00662010. Declared via function pointer so the call emits
 * `call dword [0x...]` rather than a direct rel32. */
typedef void (__stdcall *thunk_t)(int);

void __cdecl fcn_00410430(int value)
{
    ((thunk_t) *(void**) 0x00662010)(value);
}
