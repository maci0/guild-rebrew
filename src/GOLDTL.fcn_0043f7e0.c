#include <stdio.h>
#include <string.h>

typedef struct
{
	unsigned char level;
	unsigned char pad1;
	unsigned char pad2;
	unsigned char pad3;
} fcn_0043f7e0_Tint;
// SIZE 0x4

typedef struct
{
	char pad0000[0x30];
	int anims[8];
	char pad0050[0x7e24 - 0x50];
	char names[8][0x40];
} fcn_0043f7e0_Floor;
// SIZE 0x8024

int __cdecl fcn_0045be40(char* name);
void __cdecl fcn_0045bfb0(int anim);
int __cdecl fcn_0045c5b0(char* name, fcn_0043f7e0_Tint tint, int a, int b);
void __cdecl fcn_0045ce90(int anim);
void __cdecl fcn_0064d530(char* dst, char* src, int n);

// FUNCTION: GOLDTL 0x43f7e0
int __cdecl fcn_0043f7e0(fcn_0043f7e0_Floor* o, char* name, int slot)
{
	fcn_0043f7e0_Tint tint;
	char msg[0x100];
	char path[0x100];

	if (slot < 0) {
		for (slot = 0; o->names[slot][0] != 0; slot++) {
		}
	}
	if (slot < 8) {
		strcpy(o->names[slot], "");
		if (o->anims[slot] != 0) {
			fcn_0045bfb0(o->anims[slot]);
			o->anims[slot] = 0;
		}
		strcpy(path, name);
		strcat(path, "_high");
		if (fcn_0045be40(path) != 0) {
			fcn_0064d530(o->names[slot], name, 0x40);
			strcpy(msg, name);
			strcat(msg, "_high");
			if (fcn_0045be40(msg) != 0) {
				*(int*) &tint = 0;
				tint.level = 0xff;
				o->anims[slot] = fcn_0045c5b0(msg, tint, 0, 0);
				if (o->anims[slot] != 0) {
					fcn_0045ce90(o->anims[slot]);
					return slot;
				}
			} else {
				strcat(msg, " not found (FloorTexture)!");
			}
			return slot;
		}
		sprintf(msg, "Floor-Texture \"%s\" not found!", name);
	}
	return -1;
}
