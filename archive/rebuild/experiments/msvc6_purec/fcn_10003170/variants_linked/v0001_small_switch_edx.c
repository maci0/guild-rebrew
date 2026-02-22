
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

typedef void (__stdcall *stack_init_fn_t)(u32, void *, u32);

#pragma data_seg(".text$A")
u8 __pad_text[0x2170] = { 0 };
#pragma data_seg()

#pragma code_seg(".text$B")

#pragma data_seg(".text$C")
u8 kClass[127] = {
  0, 2, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2,
  2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2,
  2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
  2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2,
  2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
  2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
  2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
  2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1
};
#pragma data_seg()

// FUNCTION: SERVER 0x10003170
__declspec(dllexport) u8 __cdecl fcn_10003170(u32 arg0) {
  u8 local[0x1c];
  u32 ecx;
  u32 eax;
  u32 edx;

  ((stack_init_fn_t)(*(u32*)0x10024018))(0x10003170, local, 0x1c);

  ecx = arg0;
  ecx &= 0xff;
  eax = ecx - 2;
  if (eax > 0x7e) {
    return 0;
  }

  edx = 0;
  ((u8 *)&edx)[0] = kClass[eax];
  switch (edx) {
    case 0:
      eax = *(u32 *)(local + 0x14);
      if (eax == 2) {
        return 1;
      }
      if (eax == 4) {
        return 1;
      }
      return 0;
    case 1:
      return 1;
    default:
      return 0;
  }
}

#pragma code_seg()
