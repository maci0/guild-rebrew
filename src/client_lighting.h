#ifndef CLIENT_LIGHTING_H
#define CLIENT_LIGHTING_H

/* Inferred lighting interface. These are access views, not storage owners. */
/* ADDRESS: GOLDTL 0x006b86d4 */
/* ADDRESS: GOLD 0x00633b04 */
extern int g_6b86d4;

/* ADDRESS: GOLDTL 0x006b8300 */
/* ADDRESS: GOLD 0x00633738 */
extern int g_6b8300;

#if defined(REBREW_GOLD)
/* Inferred names; complete backing allocations remain unknown. */
/* ADDRESS: GOLD 0x00633b10 */
extern int LightingUpdateCount;
/* ADDRESS: GOLD 0x00633b14 */
extern unsigned char LightingUpdatePending;
/* Preserve the existing byte declaration's signedness. */
/* ADDRESS: GOLD 0x00633438 */
extern char g_633438;
#endif

/* Gold uses the byte flag; TL's native implementation ignores it. */
void __cdecl UpdateSceneLighting(unsigned char flag);

#endif
