
extern unsigned char* g_entity_ptr;
extern char* g_entity_type_table;
int __cdecl fcn_004ef710(void*, void*);
void* __cdecl fcn_004ef7c0(void*, void*, void*, int (__cdecl*)(void*, void*), int);

/* ADDRESS: GOLD 0x004f2540 */
int __cdecl fcn_004f2540(int owner, unsigned char** out, int* result)
{
    unsigned char* entry;
    int i;
    int found;

    *out = 0;
    *result = 0;
    entry = g_entity_ptr;
    for (i = 0; i < 0x100; i++, entry += 0xa9) {
        if (*entry != 0 && g_entity_type_table[*entry * 0x24d] == 0x1d) {
            found = (int) fcn_004ef7c0((void*) owner, entry, 0, fcn_004ef710, 0xff);
            if (found != 0) {
                *out = entry;
                *result = found;
                return 1;
            }
        }
    }
    return 0;
}
