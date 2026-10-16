#ifndef CLIENT_METHOD_REGISTRY_H
#define CLIENT_METHOD_REGISTRY_H

/* Inferred declarations and field names; the native method stride is 0x94. */
typedef struct AM_EFFECT {
 unsigned char type;
 float value;
} AM_EFFECT;

typedef struct AM_METHOD {
 unsigned char type;
 char name[0x23];
 /* Existing opaque callback address views; invocation contracts remain unresolved. */
 void* score;
 void* start;
 void* run;
 AM_EFFECT effects[4];
 AM_EFFECT saved_effects[4];
 AM_EFFECT other_effects[4];
 int flags;
} AM_METHOD;

int __cdecl am_RegisterMethod(AM_METHOD* method, char* read_profile);
#endif
