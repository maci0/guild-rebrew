typedef unsigned long u32;
typedef u32 (__stdcall *fn_t)(u32,u32,u32,u32,u32,u32);
__declspec(dllexport) int __cdecl Init(void *param){
  u32 result;
  { fn_t f = (fn_t)*(u32*)0x10024050; result = f(0,0,0x100093A0,(u32)param,0,(u32)&param); }
  { u32 *g = (u32*)0x11764094; *g = result; }
  return result != 0;
}
