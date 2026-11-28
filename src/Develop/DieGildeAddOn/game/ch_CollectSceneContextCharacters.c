/* Gold scans 32 records at 0x00930600; TL scans its 768-slot world table. */
#include <string.h>

extern int d3_ActiveScene;
extern char gm_SmallEntityTable[];
extern char* ch_ContextCharacters[32];

void __cdecl ch_CollectSceneContextCharacters(void)
{
    int self;
    int n;
    int i;

    self = d3_ActiveScene;
    memset(ch_ContextCharacters, 0, sizeof(ch_ContextCharacters));

    n = 0;
    for (i = 0; i < 32; i++) {
        if (n >= 31) {
            break;
        }
        if (*(char**) (gm_SmallEntityTable + i * 0x21c + 0x184) != 0 &&
            *(int*) (*(char**) (gm_SmallEntityTable + i * 0x21c + 0x184) + 0x88) == self) {
            ch_ContextCharacters[n] = gm_SmallEntityTable + i * 0x21c;
            n++;
        }
    }
}
