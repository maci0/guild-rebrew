#include <string.h>
#include "Develop/Units/d3/d3_d3d.h"
void __cdecl m_FreeTracked(void*);
void __cdecl fcn_004475f0(char*);
void __cdecl fcn_00438b40(char*, float*);
void __cdecl fcn_00438cb0(char*, float*);
void __cdecl fcn_00439c60(char*);
void __cdecl fcn_0045ef50(void*);
void __cdecl fcn_0045e610(void*, int);
void* __cdecl fcn_0045eea0(int, int, int);
void __cdecl fcn_0045cdf0(char*);
void __cdecl fcn_00438e60(char*, int, int, void*);
void __cdecl fcn_0043a6f0(int, int, int);
#define I32(p) (*(int*)(p))
#define U32(p) (*(unsigned int*)(p))
#define U8(p) (*(unsigned char*)(p))
#define F32(p) (*(float*)(p))

/* ADDRESS: GOLD 0x004478e0 */
char __cdecl fcn_004478e0(int index, char force)
{
    char* old;
    char* next;
    char* camera;
    void* ddraw;
    void* copySource;
    void* copyDest;
    int copyBytes;

    if (index >= 0x40) {
        return 0;
    }
    if (index != I32(0x633444)) {
        if (!force && I32(0xfb9900) != 0 && I32(0xfb9908) != 0) {
            m_FreeTracked((void*)I32(0xfb9908));
            I32(0xfb9908) = 0;
            I32(0xfb9900) = 0;
            I32(0xfb9904) = 0;
        }
        old = (char*)0xfd7ba0 + I32(0x633444) * 0x3e0;
        I32(old + 0x80) = I32(0xfc52f0);
        I32(old + 0x84) = I32(0xfc28f4);
        if (I32(old + 0x80) == 0xfc2700 && I32(old + 0x84) == 0xfc2700) {
            I32(old + 0x84) = 0;
            I32(old + 0x80) = 0;
        }
        I32(old + 0xa4) = I32(0xfb98f4);
        I32(old + 0xa8) = I32(0xfb9598);
        if (I32(old + 0xa4) == 0xfb9280 && I32(old + 0xa8) == 0xfb9280) {
            I32(old + 0xa8) = 0;
            I32(old + 0xa4) = 0;
        }
        I32(old + 0xac) = I32(0x633738);
        I32(old + 0xb8) = I32(0x633dd4);
        I32(old + 0x3d8) = I32(0x63349c);
        I32(old + 0xbc) = I32(0x5fcc78);
        I32(old + 0xc0) = I32(0x5fcc7c);
        I32(old + 0xc4) = I32(0x5fcc80);
        I32(old + 0xc8) = I32(0x633b1c);
        I32(old + 0xcc) = I32(0x633b20);
        I32(old + 0xd0) = I32(0x633b24);
        copyDest = old + 0x128;
        copySource = (void*)0xfba9c0;
        copyBytes = 0x2a0;
        __asm {
            mov edi, copyDest
            mov esi, copySource
            mov ebx, copyBytes
            lea ecx, [edi+edi*2]
            and ecx, 3
            sub ebx, ecx
            jle short copy_tail_0
            rep movsb
            mov ecx, ebx
            and ebx, 3
            shr ecx, 2
            rep movsd
        copy_tail_0:
            add ecx, ebx
            rep movsb
        }
        I32(old + 0xd4) = I32(0x6334a0);
        I32(old + 0xd8) = I32(0xfc29bc);
        I32(old + 0xdc) = I32(0xfc5340);
        copyDest = old + 0xe0;
        copySource = (void*)0xfba960;
        copyBytes = 0x48;
        __asm {
            mov edi, copyDest
            mov esi, copySource
            mov ebx, copyBytes
            lea ecx, [edi+edi*2]
            and ecx, 3
            sub ebx, ecx
            jle short copy_tail_1
            rep movsb
            mov ecx, ebx
            and ebx, 3
            shr ecx, 2
            rep movsd
        copy_tail_1:
            add ecx, ebx
            rep movsb
        }
        I32(old + 0x3cc) = I32(0x5fb5c0);
        I32(old + 0x3d0) = I32(0x5fb5c4);
        U8(old + 0x3dc) = U8(0x633450);
        I32(old + 0x88) = I32(0x6338c4);
        camera = (char*)I32(0x6338c4);
        if (camera != 0) {
            memcpy(old + 0x8c, camera + 0x4c, 12);
            memcpy(old + 0x98, camera + 0x84, 12);
        }
        next = (char*)0xfd7ba0 + index * 0x3e0;
        if (I32(next + 0x80) == 0) {
            fcn_004475f0(next);
        }
        I32(0xfb98f4) = I32(next + 0xa4);
        I32(0xfc28f4) = I32(next + 0x84);
        I32(0x633dd4) = I32(next + 0xb8);
        I32(0xfc52f0) = I32(next + 0x80);
        I32(0x63349c) = I32(next + 0x3d8);
        I32(0x633738) = I32(next + 0xac);
        I32(0x5fb5c4) = I32(next + 0x3d0);
        I32(0xfb9598) = I32(next + 0xa8);
        I32(0x5fb5c0) = I32(next + 0x3cc);
        I32(0x5fcc78) = I32(next + 0xbc);
        I32(0x5fcc7c) = I32(next + 0xc0);
        I32(0x5fcc80) = I32(next + 0xc4);
        I32(0x633b1c) = I32(next + 0xc8);
        I32(0xfc2dec) = 0;
        I32(0x633b20) = I32(next + 0xcc);
        I32(0x633b24) = I32(next + 0xd0);
        F32(0x5fcc74) = F32(0x5fcc78) * 0.3f + (F32(0x5fcc7c) * 0.59f + F32(0x5fcc80) * 0.11f);
        copyDest = (void*)0xfba960;
        copySource = next + 0xe0;
        copyBytes = 0x48;
        __asm {
            mov edi, copyDest
            mov esi, copySource
            mov ebx, copyBytes
            lea ecx, [edi+edi*2]
            and ecx, 3
            sub ebx, ecx
            jle short copy_tail_2
            rep movsb
            mov ecx, ebx
            and ebx, 3
            shr ecx, 2
            rep movsd
        copy_tail_2:
            add ecx, ebx
            rep movsb
        }
        copyDest = (void*)0xfba9c0;
        copySource = next + 0x128;
        copyBytes = 0x2a0;
        __asm {
            mov edi, copyDest
            mov esi, copySource
            mov ebx, copyBytes
            lea ecx, [edi+edi*2]
            and ecx, 3
            sub ebx, ecx
            jle short copy_tail_3
            rep movsb
            mov ecx, ebx
            and ebx, 3
            shr ecx, 2
            rep movsd
        copy_tail_3:
            add ecx, ebx
            rep movsb
        }
        I32(0x633444) = index;
        I32(0x5fb5b0) = (int)next;
        if (I32(0xfba944) == I32(0x6338c4)) {
            I32(0xfba944) = I32(next + 0x88);
        }
        I32(0x6338c4) = I32(next + 0x88);
        camera = (char*)I32(0x6338c4);
        if (camera != 0) {
            fcn_00438b40(camera, (float*)(next + 0x8c));
            fcn_00438cb0((char*)I32(0x6338c4), (float*)(next + 0x98));
            fcn_00439c60((char*)I32(0x6338c4));
        }
        if (force) {
            return 1;
        }
        if (I32(0x633738) != 0) {
            if (I32(0x633df8) != 0) {
                fcn_0045ef50((void*)I32(0x633df8));
                I32(0x633df8) = 0;
            }
        } else if (I32(0x633df8) != 0) {
            fcn_0045e610((void*)I32(0x633df8), 0);
        } else {
            I32(0x633df8) = (int)fcn_0045eea0(0, -I32(0x633dcc), 1);
            fcn_00438e60((char*)I32(0x5fb5b0), 0, 0xc0, (void*)fcn_0045cdf0);
        }
        I32(0xfc2dc8) = I32(0xfc2de0);
        I32(0xfc2dcc) = 0;
        fcn_0043a6f0(I32(next + 0xd8), I32(next + 0xdc), I32(next + 0xd4));
    } else if (force) {
        return 1;
    }
    U8(0x6339db) = 0;
    if (U8(0x633450) != 0 && I32(0x633414) != 0 && I32(0x633b04) <= 0 && ((U32(0x6339dc)++ & 0xf) == 0)) {
        ddraw = (void*)I32(0x633414);
        d3d_LastResult = (*(int(__stdcall**)(void*))(*(char**)ddraw + 0x2c))(ddraw);
        if (d3d_LastResult != 0) {
            fcn_00418e90("D:\\develop\\Units\\d3\\d3_interface.c", 0x2aa, "d3d_D3D->lpVtbl->EvictManagedTextures(d3d_D3D)");
        }
    }
    U8(0x6339db) = 1;
    return 1;
}
