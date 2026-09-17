#ifndef SAVE_HEADER_TAIL_H
#define SAVE_HEADER_TAIL_H

/* The 0x1002d4f0/f4/f8 defaults for the savegame header tail, as one
 * object: the three fields are adjacent and always written together.
 * Shared by ls_LoadSavegameHeader.c (reader) and link_stubs.c (the
 * defining emit site). Pack stays in this header; do not include from
 * entity.h (loadsave TUs). */
#pragma pack(1)
// SIZE 0x9
struct SaveHeaderTail {
	int a;
	int b;
	char c;
};
#pragma pack()

#endif /* SAVE_HEADER_TAIL_H */
