#ifdef _MSC_VER
#include <windows.h>
#else
typedef int BOOL;
typedef void *LPVOID;
typedef void *HINSTANCE;
typedef unsigned long DWORD;
#ifndef __stdcall
#define __stdcall
#endif
#ifndef __declspec
#define __declspec(x)
#endif
#endif

typedef BOOL (__stdcall *dllmain_fn)(HINSTANCE, DWORD, LPVOID);

#define G_TERMINATION_FLAG (*(DWORD *)0x100354FC)
#define G_CUSTOM_HANDLER (*(DWORD *)0x11767588)

#define PAD1_SIZE 24
#define PAD2_SIZE 24

#ifdef _MSC_VER
#pragma optimize("y", off)
#pragma auto_inline(off)
#endif

static BOOL __stdcall sub_1001B8FB(HINSTANCE h, DWORD r, LPVOID p) {
  volatile unsigned char pad[PAD1_SIZE ? PAD1_SIZE : 1];
  return ((dllmain_fn)0x1001B8FB)(h,r,p);
}

static BOOL __stdcall sub_10009310(HINSTANCE h, DWORD r, LPVOID p) {
  volatile unsigned char pad[PAD2_SIZE ? PAD2_SIZE : 1];
  return ((dllmain_fn)0x10009310)(h,r,p);
}

#ifdef _MSC_VER
#pragma auto_inline(on)
#endif

// FUNCTION: SERVER 0x1001B9D4
BOOL __stdcall entry0(HINSTANCE hinst, DWORD reason, LPVOID reserved) {
  HINSTANCE h=hinst; DWORD r=reason; LPVOID p=reserved;
  if(r==0){ if(G_TERMINATION_FLAG==0) return 0; }
  if(r!=0){
    if(r==1 || r==2){
      custom=(dllmain_fn)G_CUSTOM_HANDLER; if(custom){ if(!custom(h,r,p)) return 0; }
      if(!sub_1001B8FB(h,r,p)) return 0;
    }
  }
  fdwReason=sub_10009310(h,r,p);
  if(r==1){ if(fdwReason!=0) goto done; fdwReason=sub_1001B8FB(h,fdwReason,p); }
  if(r==0 || r==3){ tmp=sub_1001B8FB(h,r,p); if(tmp==0) fdwReason &= tmp; }
  if(fdwReason){ custom=(dllmain_fn)G_CUSTOM_HANDLER; if(custom){ fdwReason=custom(h,r,p);} }
 done:
  return fdwReason;
 ret0:
  return 0;
}

#ifdef _MSC_VER
#pragma optimize("", on)
#endif
