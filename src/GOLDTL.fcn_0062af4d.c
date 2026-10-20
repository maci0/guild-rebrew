/* Restores the saved GDI object into the DC at +0x6c and clears the slot.
 * Native code materializes &self[0xa8] in ESI across the call and clears it
 * with "and dword ptr [esi],0"; this source gets the field address kept in
 * self instead, so the candidate is 42 bytes against the 35 native bytes. */
__declspec(dllimport) void *__stdcall SelectObject(void *, void *);

/* ADDRESS: GOLDTL 0x0062af4d */
int __fastcall fcn_0062af4d(void *self)
{
    char *obj;
    void *hdc;

    obj = (char *)self;
    hdc = *(void **)(obj + 0x6c);
    if (hdc != 0) {
        void **saved;

        saved = (void **)(obj + 0xa8);
        if (*saved != 0) {
            SelectObject(hdc, *saved);
            *saved = 0;
        }
    }
    return 0;
}
