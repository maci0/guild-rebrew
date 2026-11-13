/* Builds the stock-object D3DX mesh: copies positions, attributes and indices
 * into the locked buffers, welds and optimizes it, then clones it to FVF 0x112. */

#include <string.h>

typedef unsigned short u16;
typedef unsigned char u8;

long __stdcall D3DXCreateMeshFVF(int a, int b, int c, int d, int e, int* f);
long __stdcall D3DXWeldVertices(void* mesh, void* eps, int* adj_in, int* adj_out,
                            int* face_remap, void** vert_remap);
void* __cdecl fcn_0041db70(int size, char* tag);
void __cdecl fcn_0041ddd0(void* p);
extern int g_6b5de0;
extern int g_14ce728;

typedef long(__stdcall* LockFn)(void*, int, void*);
typedef long(__stdcall* UnlockFn)(void*);

/* ADDRESS: GOLDTL 0x0044aec0 */
int __cdecl fcn_0044aec0(char* o)
{
    int** mesh;
    int i;
    int j;
    int k;
    int* buf;
    int* vb;
    u16* ib;
    int eps[11];
    int r;
    int fill_len;
    void* fill_dst;

    r = 0;
    if (D3DXCreateMeshFVF(*(int*) (o + 0x4c), *(int*) (o + 0x4c) * 3, 0x110, 0x112,
                     g_6b5de0, (int*) &mesh) < 0)
        return r;
    *(int*) (o + 0x27c) = (int) fcn_0041db70(*(int*) (o + 0x44) * 0xc,
                                             "d3io:StockObjectVertices");
    for (i = 0; i < *(int*) (o + 0x44); i++) {
        ((int*) *(int*) (o + 0x27c))[i * 3 + 0] = ((int*) (*(int*) (o + 0x40) + i * 0x18))[0];
        ((int*) *(int*) (o + 0x27c))[i * 3 + 1] = ((int*) (*(int*) (o + 0x40) + i * 0x18))[1];
        ((int*) *(int*) (o + 0x27c))[i * 3 + 2] = ((int*) (*(int*) (o + 0x40) + i * 0x18))[2];
    }
    *(int*) (o + 0x280) = (int) fcn_0041db70(*(int*) (o + 0x4c) * 6, "d3io:Indices");
    if (((LockFn) (*mesh)[0x58 / 4])(mesh, 0, &buf) >= 0) {
        for (i = 0; i < *(int*) (o + 0x4c); i++) {
            buf[i] = *(int*) (*(int*) (o + 0x48) + i * 0x38 + 0x28);
            for (j = 0; j < 3; j++)
                ((u16*) *(int*) (o + 0x280))[i * 3 + j] =
                    *(u16*) (*(int*) (o + 0x48) + i * 0x38 + 0x18 + j * 4);
        }
        ((UnlockFn) (*mesh)[0x5c / 4])(mesh);
    }
    if (((LockFn) (*mesh)[0x38 / 4])(mesh, 0, &vb) >= 0) {
        for (i = 0; i < *(int*) (o + 0x4c); i++) {
            for (j = 0; j < 3; j++) {
                k = *(int*) (*(int*) (o + 0x48) + i * 0x38 + 0x18 + j * 4);
                vb[(i * 3 + j) * 8 + 0] = *(int*) (*(int*) (o + 0x40) + k * 0x18 + 0x00);
                vb[(i * 3 + j) * 8 + 1] = *(int*) (*(int*) (o + 0x40) + k * 0x18 + 0x04);
                vb[(i * 3 + j) * 8 + 2] = *(int*) (*(int*) (o + 0x40) + k * 0x18 + 0x08);
                vb[(i * 3 + j) * 8 + 3] = *(int*) (*(int*) (o + 0x40) + k * 0x18 + 0x0c);
                vb[(i * 3 + j) * 8 + 4] = *(int*) (*(int*) (o + 0x40) + k * 0x18 + 0x10);
                vb[(i * 3 + j) * 8 + 5] = *(int*) (*(int*) (o + 0x40) + k * 0x18 + 0x14);
                vb[(i * 3 + j) * 8 + 6] = *(int*) (*(int*) (o + 0x48) + i * 0x38 + j * 8);
                vb[(i * 3 + j) * 8 + 7] = *(int*) (*(int*) (o + 0x48) + i * 0x38 + j * 8 + 4);
            }
        }
        ((UnlockFn) (*mesh)[0x3c / 4])(mesh);
    }
    if (((LockFn) (*mesh)[0x40 / 4])(mesh, 0, &ib) >= 0) {
        for (i = 0; i < *(int*) (o + 0x4c); i++) {
            for (j = 0; j < 3; j++)
                ib[i * 3 + j] = (u16) (i * 3 + j);
        }
        ((UnlockFn) (*mesh)[0x44 / 4])(mesh);
    }
    buf = (int*) fcn_0041db70(*(int*) (o + 0x4c) * 0xc, "d3io:Adjacency");
    fill_len = sizeof(eps);
    fill_dst = eps;
    __asm {
        mov edi, fill_dst
        mov ebx, fill_len
        xor eax, eax
        lea ecx, [edi+edi*2]
        and ecx, 3
        sub ebx, ecx
        jle short eps_fill_done
        rep stosb
        mov ecx, ebx
        and ebx, 3
        shr ecx, 2
        rep stosd
    eps_fill_done:
        add ecx, ebx
        rep stosb
    }
    D3DXWeldVertices(mesh, eps, 0, buf, 0, 0);
    ((long(__stdcall*) (void*, int, int*, int*, int*, void**)) (*mesh)[0x64 / 4])(
        mesh, 0x6000000, buf, 0, 0, 0);
    fcn_0041ddd0(buf);
    buf = 0;
    ((long(__stdcall*) (void*, int, int, int, int*)) (*mesh)[0x28 / 4])(
        mesh, 0x660, 0x112, g_6b5de0, &r);
    g_14ce728 = ((UnlockFn) (*mesh)[8 / 4])(mesh);
    return r;
}
