#ifndef CLIENT_SPRITES_H
#define CLIENT_SPRITES_H

/* Declaration view; native loops visit 32 slots, storage owner is unknown. */
/* ADDRESS: GOLD 0x00f8f0a0 */
extern char* d2_OverlaySprites[];

void __cdecl d2_FreeOverlaySprite(void* node);

#endif
