#ifndef CH_GROUND_H
#define CH_GROUND_H

#ifdef REBREW_SERVER
void __cdecl ch_PlaceOnGround(void* object, int force);
#else
int __cdecl ch_PlaceOnGround(void* object, int force);
#endif

#endif
