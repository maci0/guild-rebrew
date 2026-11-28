#ifndef G_688118_H
#define G_688118_H

/* GOLDTL 0x688118: groups of zero-terminated id lists; a group whose first
 * id is 0 ends the table. */
typedef struct {
	int ids[4];
	char name[0x100];
	short score;
	char active;
	char pad113;
} IdGroup;
// SIZE 0x114

#endif
