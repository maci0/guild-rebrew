#include <string.h>

typedef struct CH_DUMMY_PICKS {
	char* item[0x20];
	int count;
} CH_DUMMY_PICKS;
/* Inferred 32-pointer result view; native stack allocation is 0x84 bytes. */

extern int d3_ActiveScene;

void __cdecl d3_VisitSceneObjects(char*, int, int, void*, CH_DUMMY_PICKS*);
int __cdecl ch_CollectMatchingDummyNodes(char*, CH_DUMMY_PICKS*);
int __cdecl ch_RandomIndex(unsigned short);

/* Original source-unit home is unproved; retained beside its selection caller. */
/* ADDRESS: GOLD 0x00406340 */
/* ADDRESS: GOLDTL 0x00406ee0 */
int __cdecl ch_CollectMatchingDummyNodes(char* object, CH_DUMMY_PICKS* picks)
{
    char names[15][64] = {
        "dummy_WAIT", "dummy_FEGEN1", "dummy_FEGEN2", "dummy_FEGEN3",
        "dummy_FEGEN4", "dummy_PAUSE", "dummy_PAUSE2",
        "dummy_AUSGANGdummy_LAUFEN1", "dummy_LAUFEN2", "dummy_LAUFEN3",
        "dummy_LAUFEN4", "dummy_STEHPLATZ_01", "dummy_STEHPLATZ_02",
        "dummy_STEHPLATZ_03"
    };
    int i;

    for (i = 0; i < 15; i++) {
        if (names[i][0] != 0 && strstr(object, names[i]) != 0) {
            picks->item[picks->count] = object;
            picks->count++;
            break;
        }
    }
    return picks->count < 32;
}


/* Fills p through the ch_CollectMatchingDummyNodes scene callback and returns a random
 * entry, or 0 when p.count is 0. The inventory entry also holds a second
 * function at 0x407390 (632 bytes). */
/* ADDRESS: GOLDTL 0x00407330 */
char* __cdecl ch_SelectRandomDummy(void)
{
	CH_DUMMY_PICKS p;

	memset(&p, 0, sizeof(p));
	d3_VisitSceneObjects(((char*)d3_ActiveScene), 0, 0x100, (void*) ch_CollectMatchingDummyNodes, &p);
	if (p.count == 0) {
		return 0;
	}
	return p.item[(unsigned short) ch_RandomIndex((unsigned short) p.count)];
}
