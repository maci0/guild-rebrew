/*
 * Native operand map (0x005ce800):
 *   arg1 int id; arg2 int* out; arg3 int* value; arg4 int* slots;
 *   arg5 unsigned char* type; arg6 int text; arg7..arg10 16-byte config
 *   passed by value; arg11 int* handle; arg12 object pointer.
 *   Callers 0x5cefa0, 0x5cf000, 0x5cf320 push twelve dwords.
 */

typedef struct fcn_005ce800_Config {
    unsigned int flags;
    int pad4;
    int pad8;
    int padc;
} fcn_005ce800_Config;

typedef struct fcn_005ce800_Source {
    char pad00[0x38];
    float value38;
} fcn_005ce800_Source;

extern char* g_entity_type_table; /* 0x868050, BSS pointer */
extern unsigned char g_773d75;    /* 0x773d75, BSS */
extern int g_772514;              /* 0x772514, BSS */
extern float g_662cf8;            /* 0x662cf8, .rdata, 100.0f */

int __cdecl fcn_004727a0(int k, int i);
int __cdecl fcn_00472250(int k, int i, int j);
void __cdecl d2_SetElementValue(int element, ...);
int __cdecl fcn_00519190();
int __cdecl fcn_004677e0(int x, int y, int a3, int a4, int a5, int a6,
                         int a7, int win);

/* ADDRESS: GOLDTL 0x005ce800 */
void __cdecl fcn_005ce800(int id, int* out, int* value, int* slots,
                          unsigned char* type, int text,
                          unsigned int flags, int pad7, int pad8, int pad9,
                          int* handle, fcn_005ce800_Source* source)
{
    unsigned char* entry;
    int bit;
    int element;
    float f;

    fcn_004727a0(id, 1);
    fcn_00519190("$C");
    fcn_00519190(0x1949);
    fcn_004727a0(id, 2);
    fcn_00519190("$C$A");

    bit = flags & 1;
    element = fcn_00472250(id, 2,
                           fcn_00519190(0x194f, 2, text, bit + 0x1951));
    slots[0] = element;
    d2_SetElementValue(element, bit);
    slots[1] = -1;
    slots[2] = -1;
    slots[3] = -1;

    entry = (unsigned char*) (g_entity_type_table + *type + *type * 0x24c);
    if (*entry != 5) {
        bit = (flags >> 1) & 1;
        element = fcn_00472250(id, 2,
                               fcn_00519190(0x1954, 2, text,
                                            bit + 0x1955));
        slots[1] = element;
        d2_SetElementValue(element, bit);

        bit = (flags >> 2) & 1;
        element = fcn_00472250(id, 2,
                               fcn_00519190(0x1957, 2, text,
                                            bit + 0x1958));
        slots[2] = element;
        d2_SetElementValue(element, bit);

        bit = (flags >> 3) & 1;
        element = fcn_00472250(id, 2,
                               fcn_00519190(0x195a, 2, text,
                                            bit + 0x195b));
        slots[3] = element;
        d2_SetElementValue(element, bit);
    }

    element = fcn_00472250(id, 2,
                           fcn_00519190(0x1953, text, g_773d75));
    *out = element;
    d2_SetElementValue(element, 1000, 9000, *value);

    if (*entry != 5 && source != 0) {
        fcn_00519190(0x42c2);
        element = fcn_004677e0(100, 300, 200, 50, 150, 123, 0x1002,
                               g_772514);
        *handle = element;
        f = source->value38;
        d2_SetElementValue(element, 50, 150, (int) (f * g_662cf8));
        return;
    }
    *handle = -1;
}
