typedef unsigned char u8;
typedef unsigned long u32;

#ifndef _MSC_VER
#ifndef __declspec
#define __declspec(x)
#endif

#ifndef __cdecl
#define __cdecl
#endif

#ifndef __stdcall
#define __stdcall
#endif
#endif

#pragma data_seg(".text$A")
u8 __pad_text[0x2170] = { 0 };
#pragma data_seg()

#pragma code_seg(".text$B")

typedef void (__stdcall *stack_init_fn_t)(u32, void *, u32);

// FUNCTION: SERVER 0x10003170
__declspec(dllexport) u8 __cdecl fcn_10003170(u32 arg0)
{
    u8 local[0x1c];
    u32 ecx;
    u32 eax;

    ((stack_init_fn_t)(*(u32 *)0x10024018))(0x10003170, local, 0x1c);

    ecx = arg0;
    ecx &= 0xff;

    eax = ecx - 2;
    if (eax > 0x7e) {
        return 0;
    }

    switch (eax) {
    case 0: goto case_a6;
    case 1: goto ret_false_al;
    case 2: goto case_a6;
    case 3: goto ret_false_al;
    case 4: goto ret_false_al;
    case 5: goto ret_false_al;
    case 6: goto ret_false_al;
    case 7: goto ret_false_al;
    case 8: goto ret_false_al;
    case 9: goto ret_false_al;
    case 10: goto ret_false_al;
    case 11: goto ret_false_al;
    case 12: goto ret_false_al;
    case 13: goto ret_false_al;
    case 14: goto ret_true_al;
    case 15: goto ret_false_al;
    case 16: goto ret_false_al;
    case 17: goto ret_false_al;
    case 18: goto ret_false_al;
    case 19: goto ret_false_al;
    case 20: goto ret_false_al;
    case 21: goto ret_false_al;
    case 22: goto ret_false_al;
    case 23: goto ret_false_al;
    case 24: goto ret_false_al;
    case 25: goto ret_false_al;
    case 26: goto ret_false_al;
    case 27: goto ret_false_al;
    case 28: goto ret_false_al;
    case 29: goto ret_false_al;
    case 30: goto ret_true_al;
    case 31: goto ret_false_al;
    case 32: goto ret_false_al;
    case 33: goto ret_false_al;
    case 34: goto ret_false_al;
    case 35: goto ret_false_al;
    case 36: goto ret_false_al;
    case 37: goto ret_false_al;
    case 38: goto ret_false_al;
    case 39: goto ret_false_al;
    case 40: goto ret_false_al;
    case 41: goto ret_false_al;
    case 42: goto ret_false_al;
    case 43: goto ret_false_al;
    case 44: goto ret_false_al;
    case 45: goto ret_false_al;
    case 46: goto ret_false_al;
    case 47: goto ret_false_al;
    case 48: goto ret_false_al;
    case 49: goto ret_false_al;
    case 50: goto ret_false_al;
    case 51: goto ret_false_al;
    case 52: goto ret_false_al;
    case 53: goto ret_false_al;
    case 54: goto ret_false_al;
    case 55: goto ret_false_al;
    case 56: goto ret_false_al;
    case 57: goto ret_false_al;
    case 58: goto ret_false_al;
    case 59: goto ret_false_al;
    case 60: goto ret_false_al;
    case 61: goto ret_false_al;
    case 62: goto ret_true_al;
    case 63: goto ret_false_al;
    case 64: goto ret_false_al;
    case 65: goto ret_false_al;
    case 66: goto ret_false_al;
    case 67: goto ret_false_al;
    case 68: goto ret_false_al;
    case 69: goto ret_false_al;
    case 70: goto ret_false_al;
    case 71: goto ret_false_al;
    case 72: goto ret_false_al;
    case 73: goto ret_false_al;
    case 74: goto ret_false_al;
    case 75: goto ret_false_al;
    case 76: goto ret_false_al;
    case 77: goto ret_false_al;
    case 78: goto ret_false_al;
    case 79: goto ret_false_al;
    case 80: goto ret_false_al;
    case 81: goto ret_false_al;
    case 82: goto ret_false_al;
    case 83: goto ret_false_al;
    case 84: goto ret_false_al;
    case 85: goto ret_false_al;
    case 86: goto ret_false_al;
    case 87: goto ret_false_al;
    case 88: goto ret_false_al;
    case 89: goto ret_false_al;
    case 90: goto ret_false_al;
    case 91: goto ret_false_al;
    case 92: goto ret_false_al;
    case 93: goto ret_false_al;
    case 94: goto ret_false_al;
    case 95: goto ret_false_al;
    case 96: goto ret_false_al;
    case 97: goto ret_false_al;
    case 98: goto ret_false_al;
    case 99: goto ret_false_al;
    case 100: goto ret_false_al;
    case 101: goto ret_false_al;
    case 102: goto ret_false_al;
    case 103: goto ret_false_al;
    case 104: goto ret_false_al;
    case 105: goto ret_false_al;
    case 106: goto ret_false_al;
    case 107: goto ret_false_al;
    case 108: goto ret_false_al;
    case 109: goto ret_false_al;
    case 110: goto ret_false_al;
    case 111: goto ret_false_al;
    case 112: goto ret_false_al;
    case 113: goto ret_false_al;
    case 114: goto ret_false_al;
    case 115: goto ret_false_al;
    case 116: goto ret_false_al;
    case 117: goto ret_false_al;
    case 118: goto ret_false_al;
    case 119: goto ret_false_al;
    case 120: goto ret_false_al;
    case 121: goto ret_false_al;
    case 122: goto ret_false_al;
    case 123: goto ret_false_al;
    case 124: goto ret_false_al;
    case 125: goto ret_false_al;
    case 126: goto ret_true_al;
    default: goto ret_false_al;
    }

case_a6:
    eax = *(u32 *)(local + 0x14);
    if (eax == 2) {
        return 1;
    }
    if (eax == 4) {
        return 1;
    }
    return 0;

ret_true_al:
    return 1;

ret_false_al:
    return 0;
}

#pragma code_seg()
