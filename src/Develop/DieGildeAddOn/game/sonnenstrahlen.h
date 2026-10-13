#ifndef SONNENSTRAHLEN_H
#define SONNENSTRAHLEN_H

/* Inferred interface; native constructors return their scene object. */
char* __cdecl CreateSonnenstrahlen(void);
void __cdecl StartSonnenstrahlen(char* objekt);
void __cdecl StopSonnenstrahlen(char* objekt, int phase);

#endif
