#ifndef D3_ANIMATION_H
#define D3_ANIMATION_H

/* Inferred names; the native call passes all 12 bytes by value. */
typedef struct D3_ANIMATION_OPTIONS {
	unsigned char mode;
	unsigned char layer;
	unsigned char pad2[2];
	unsigned int loop : 1;
	unsigned int reverse : 1;
	unsigned int pad4 : 30;
	unsigned char blend : 1;
	unsigned char queue : 1;
	unsigned char pad8[3];
} D3_ANIMATION_OPTIONS;

/* Reconstructed animation byte views; no allocation ownership is implied. */
char* __cdecl fcn_00433ba0(const char* name);
char* __cdecl fcn_0044c620(char* path, char* name, char loop);
char* __cdecl fcn_0044e1e0(char* path, char* name, char loop);
void __cdecl fcn_00434760(char* animation, char force);

#endif
