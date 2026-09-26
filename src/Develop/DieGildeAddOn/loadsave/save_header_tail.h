#ifndef SAVE_HEADER_TAIL_H
#define SAVE_HEADER_TAIL_H

/* Layout of the 9-byte savegame header tail ("Savegame" at 0x1002d4f0).
 * ls_LoadSavegameHeader.c defines the bytes as a char array (a struct
 * object makes msvc6 8-align the TU's .data, 4 bytes past the reference)
 * and copies them through this type.  Pack stays in this header; do not
 * include from entity.h (loadsave TUs). */
#pragma pack(1)
// SIZE 0x9
struct SaveHeaderTail {
	int a;
	int b;
	char c;
};
#pragma pack()

#endif /* SAVE_HEADER_TAIL_H */
