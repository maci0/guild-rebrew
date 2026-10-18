int __cdecl fcn_00430bd0(void* buf, int size, int count, void* stream);
int __cdecl fcn_0044d770(void* stream);
int __cdecl fcn_004011d0(void* stream, void* dst);
int __cdecl fcn_0044eee0(void* stream, void* table, int kind, int extra);

/* ADDRESS: GOLD 0x0044f860 */
void __cdecl fcn_0044f860(void* stream, int value)
{
    void* saved;
    int field;

    saved = stream;
    fcn_00430bd0(&stream, 4, 1, saved);
    if (fcn_0044d770(saved) == 0x2e) {
        fcn_004011d0(saved, &field);
        fcn_0044eee0(saved, (char*)0x5fc890, 7, value);
    }
}
