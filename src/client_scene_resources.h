#ifndef CLIENT_SCENE_RESOURCES_H
#define CLIENT_SCENE_RESOURCES_H

/* Inferred Gold record and field names; native array stride is 0x80. */
typedef struct SCENE_RESOURCE {
	char name[0x40];
	int level;
	void *tracked;
	char pad48[4];
	int alias;
	int id;
	char pad54[0x0c];
	void *com60;
	void *com64;
	unsigned char flags;
	char pad69[7];
	unsigned char byte70;
	unsigned char byte71;
	char pad72[2];
	unsigned int shifted;
	unsigned int value;
	unsigned char result;
	unsigned char extra;
	char pad7e[2];
} SCENE_RESOURCE;


/* Declaration views; allocation and storage owners are unknown. */
/* ADDRESS: GOLD 0x00fb9074 */
extern SCENE_RESOURCE* g_104049c;
/* ADDRESS: GOLD 0x00fb9084 */
extern unsigned int g_10404a0;
/* ADDRESS: GOLD 0x00633f00 */
extern int g_6b8af0;

void __cdecl fcn_0045fbb0(SCENE_RESOURCE* resource);
SCENE_RESOURCE* __cdecl fcn_004605b0(const char* name, unsigned int style,
    unsigned char flags, unsigned char control);
void __cdecl fcn_004481e0(SCENE_RESOURCE* resource);
void __cdecl fcn_0045d9e0(char* owner, const char* name);
void __cdecl fcn_00460210(char* name, SCENE_RESOURCE* resource);
void __cdecl fcn_00460e40(SCENE_RESOURCE* resource, int selector);

#endif
