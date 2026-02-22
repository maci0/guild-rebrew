typedef unsigned long u32;
typedef u32 (__stdcall *fn_t)(u32,u32,u32,u32,u32,u32);
__declspec(dllexport) int __cdecl Init(void *param){
  u32 result;
  u32* G = (u32*)0x11764094;
  result = (*(fn_t*)0x10024050)(0,0,0x100093A0,(u32)param,0,(u32)&param);
  int r=0; if(result) r=1; *(G)=result; return r;
}
