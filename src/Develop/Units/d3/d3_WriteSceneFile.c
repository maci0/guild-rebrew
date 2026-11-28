#include "Develop/Units/d3/client_lighting.h"
#include "Develop/Units/d3/d3_object.h"

#include "Develop/DieGildeAddOn/game/game_data.h"
extern char* g_6338c4;
extern int g_fc52f0;
int __cdecl vfs_Tfopen(char*, const char*, int);
void __cdecl vfs_WriteDword(int, unsigned int);
void __cdecl vfs_WriteCString(int, char*);
void __cdecl vfs_WriteVec3(int, int*);
void __cdecl fcn_004011f0(int, unsigned char);
int __cdecl d3_GetNextSceneNode(int);
void __cdecl wr_object(int, int);
void __cdecl d3_SaveFloor(int, char*);
struct Event;
void __cdecl d3_WriteEventTable(int, struct Event*);
void __cdecl CloseVfsStream(int);

/* ADDRESS: GOLD 0x0044aa10 */
void __cdecl d3_WriteSceneFile(char* path, int supplied)
{
    int stream;
    int node;
    int count;
    int i;
    char* preset;
    unsigned int* value;

    stream = supplied;
    if (!stream) {
        stream = vfs_Tfopen(path, (char*) 0x5f8324, *(int*) 0x6333fc);
        if (!stream)
            return;
    }
    vfs_WriteDword(stream, 0x3a6c00bb);
    vfs_WriteCString(stream, g_6338c4);
    vfs_WriteDword(stream, *(unsigned int*) 0x5fcc74);
    vfs_WriteVec3(stream, (int*) 0x5fcc78);
    vfs_WriteVec3(stream, (int*) 0x633b1c);
    vfs_WriteDword(stream, *(unsigned int*) (g_5fb5b0 + 0xb4));
    vfs_WriteDword(stream, *(unsigned int*) 0x6334a0);
    vfs_WriteDword(stream, *(unsigned int*) 0xfc29bc);
    vfs_WriteDword(stream, *(unsigned int*) 0xfc5340);
    preset = (char*) 0xfba9cc;
    do {
        vfs_WriteVec3(stream, (int*) (preset - 0xc));
        vfs_WriteVec3(stream, (int*) preset);
        value = (unsigned int*) (preset + 0x10);
        i = 6;
        do {
            vfs_WriteDword(stream, value[-1]);
            vfs_WriteDword(stream, value[0]);
            vfs_WriteDword(stream, value[1]);
            value += 3;
        } while (--i);
        preset += 0x60;
    } while ((int) preset < 0xfbac6c);
    count = 0;
    for (node = g_fc52f0; node != (int) g_fc2700; node = d3_GetNextSceneNode(node))
        count++;
    vfs_WriteDword(stream, count);
    node = g_fc52f0;
    while (node != (int) g_fc2700) {
        wr_object(stream, node);
        node = d3_GetNextSceneNode(node);
    }
    fcn_004011f0(stream, g_6b8300 != 0);
    if (g_6b8300)
        d3_SaveFloor(stream, (char*) g_6b8300);
    d3_WriteEventTable(stream, *(struct Event**) (g_5fb5b0 + 0x3c8));
    if (!supplied)
        CloseVfsStream(stream);
}
