#ifndef CUTSCENE_H
#define CUTSCENE_H

void __cdecl cut_FreeCutscene(int id);
#ifndef REBREW_GOLD
void __cdecl cut_FreeAllCutscenes(void);
#endif
int __cdecl cut_AddParticipant(int id, int participant);
int __cdecl cut_RemoveParticipant(int id, int participant);

#endif
