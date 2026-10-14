#include "../../../client_sound.h"

#include "../../../client_lighting.h"
Voice_14cbbe0* __cdecl fcn_00422460(int a, int b);

void __cdecl PlayEntitySound(char* cmd)
{
    char* e;
    Voice_14cbbe0* r;

    e = *(char**)(cmd + 0x14);
    r = fcn_00422460(0, (int)(cmd + 0x130));
    if (r != 0) {
        if (g_6b8300 != 0) {
            fcn_004193f0((char*)r, *(void**)(e + 0x34), 0x7f, 3000.0f);
        } else {
            fcn_004193f0((char*)r, *(void**)(e + 0x34), 0x7f, 1000.0f);
        }
    }
}
