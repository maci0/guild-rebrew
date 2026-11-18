#ifndef CRIME_DESCRIPTION_H
#define CRIME_DESCRIPTION_H

typedef struct {
	int name;
	unsigned char unk_04[0x10];
} CRIME_DESCRIPTION_VIEW;
/* SIZE 0x14 */

extern CRIME_DESCRIPTION_VIEW g_14aa314[];

#endif
