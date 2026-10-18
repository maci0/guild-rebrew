#include <string.h>
#include "Develop/DieGildeAddOn/game/ch_motion.h"
#include "Develop/Units/d3/d3_animation.h"
char* __cdecl fcn_00401040(char* path);
void __cdecl fcn_00425bf0(char* script, unsigned int position, const char* message);

/* ADDRESS: GOLDTL 0x0040eff0 */
/* ADDRESS: GOLD 0x0040e0e0 */
int __cdecl AttachAnimLooped(char** character, char** animation, int* kind)
{
    D3_ANIMATION_OPTIONS options;
    char path[256];
    char name[256];
    char resolved[256];
    char* object;
    char* short_name;
    char* draw;
    char** slot;
    int i;
    char copied;

    object = *character;
    if (g_6b7ebc != 0 && *(void**) (g_6b7ebc + 0x44) == (void*) AttachAnimLooped) {
        draw = *(char**) (object + 0x1ec);
        /* Native pointer-cell views; complete slot records remain unresolved. */
#ifdef REBREW_GOLD
        slot = (char**) (draw + 0x178);
#else
        slot = (char**) (draw + 0x484);
#endif
        for (i = 0; i < 3; i++, slot = (char**) ((char*) slot + 0x7c)) {
            if (draw != 0 && *slot != 0) {
                *(void**) (g_6b7e98 + 0xc60) = (void*) AttachAnimLooped;
                return 0;
            }
        }
        return 0;
    }
    strcpy(path, *animation);
    strcat(path, ".baf");
    i = 0;
    do {
        copied = path[i];
        name[i] = copied;
        i++;
    } while (copied != 0);
    short_name = fcn_00401040(name);
    if (short_name != 0) {
        strcpy(resolved, short_name);
    }
    if (path[0] != 0 && object != 0 && *(char**) (object + 0x1cc) != 0) {
        if (fcn_00433ba0(name) == 0) {
            d3_LoadAnimStream(path, name, 0);
        }
        memset(&options, 0, sizeof(options));
        *(int*) &options = 0;
        options.queue = 1;
        options.layer = *kind == 1 ? 0x10 : 0;
        options.mode = (unsigned char) *kind;
        options.reverse = 0;
        options.loop = 1;
        if (fcn_00434970(*(char**) (object + 0x1cc), name, options) == 0) {
            fcn_00425bf0(g_6b7e98, *(unsigned int*) (g_6b7e98 + 0x118),
                "AttachAnimLooped(): Could not find animation-file...");
        }
    }
    if (*(int*) (g_6b7e98 + 0xc84) == 1) {
        *(void**) (g_6b7e98 + 0xc60) = (void*) AttachAnimLooped;
    }
    return 0;
}
