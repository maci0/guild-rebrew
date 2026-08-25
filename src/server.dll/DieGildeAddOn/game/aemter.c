/* aemter.c - office slot table helpers (proper C) */

#include <stdio.h>
#include "../../Units/Error/error.h"

/* Office slot table entry - 0x18 bytes per slot. */
typedef struct {
	unsigned char id;      /* +0x00 */
	unsigned char pad1[3];
	int a;                 /* +0x04 */
	unsigned char b;       /* +0x08 */
	unsigned char pad2[3];
	int c;                 /* +0x0c */
	unsigned char type;    /* +0x10 */
	unsigned char pad3[3];
	int d;                 /* +0x14 */
} OFFICE_SLOT;

/* 24-byte copy payload fetched from the g_str_29bb8 template table. */
typedef struct {
	int f0;
	int f4;
	int f8;
	int fc;
	int f10;
	int f14;
} COPY24;

extern OFFICE_SLOT g_office_slots[];
extern COPY24 g_str_29bb8[];
void* __cdecl gm_LookupEntityRecordById(int entityId);

/* Validates whether an entity can take an office position.  Scans the
 * office slot table for the requested type; on a hit verifies the slot is
 * free (no holder, type 3, fewer than 4 incumbents) and, when a home
 * office type is given, that both table entries agree on the holder
 * byte.  Returns 1 when valid, 0 otherwise. */

// FUNCTION: SERVER 0x1000b1c0
// SYMBOL: _amt_ValidateOfficeCandidate
// SIZE: 205

int __cdecl amt_ValidateOfficeCandidate(int* arg1)
{
	unsigned char* rec;
	unsigned char b;
	OFFICE_SLOT* p;
	int i;

	rec = gm_LookupEntityRecordById(arg1[0]);
	if (rec == 0 || rec[0x168] != 0)
		return 0;

	i = 0;
	for (; i < 30; i++) {
		if (g_office_slots[i].id == ((unsigned char*) arg1)[4])
			break;
	}
	if (i >= 30)
		return 0;

	if ((g_office_slots)[i].a != -1 ||
	    (g_office_slots)[i].type != 3 ||
	    (g_office_slots)[i].c >= 4)
		return 0;
	b = (g_office_slots)[i].b;
	if (((unsigned char*) arg1)[6] != b)
		return 0;

	if (((unsigned char*) arg1)[5] != 0xff) {
		i = 0;
		for (; i < 30; i++) {
			if (g_office_slots[i].id == ((unsigned char*) arg1)[5])
				break;
		}
		if (i >= 30)
			return 0;

		if (b != (g_office_slots)[i].b ||
		    (g_office_slots)[i].a != -1 ||
		    (g_office_slots)[i].type != 3 ||
		    (g_office_slots)[i].c >= 4)
			return 0;
	}
	return 1;
}

/* Validates preconditions and assigns an office to an entity.  Performs
 * eligibility checks, then updates the office holder table and entity
 * links. */

// FUNCTION: SERVER 0x1000b290
// SYMBOL: _ValidateAndAssignOffice
// SIZE: 425

unsigned int __cdecl ValidateAndAssignOffice(unsigned int* arg1)
{
	unsigned char* rec;
	unsigned char x6;
	unsigned char x5;
	unsigned char b;
	COPY24 copy;
	int i;
	int j;

	rec = gm_LookupEntityRecordById(arg1[0]);
	if (rec == 0)
		return 0;
	if (*(unsigned short*) rec == 0xffff)
		return 0;
	if (rec[0x168] != 0)
		return 0;

	i = 0;
	for (; i < 30; i++) {
		if (g_office_slots[i].id == ((unsigned char*) arg1)[4])
			break;
	}
	if (i >= 30)
		return 0;

	x6 = ((unsigned char*) arg1)[6];
	if (x6 != (g_office_slots)[i].b)
		return 0;

	x5 = ((unsigned char*) arg1)[5];
	if (x5 != 0xff) {
		j = 0;
		for (; j < 30; j++) {
			if (g_office_slots[j].id == x5)
				break;
		}
		if (j >= 30)
			return 0;

		if ((g_office_slots)[i].b != (g_office_slots)[j].b)
			return 0;

		copy = g_str_29bb8[(g_office_slots)[i].b];
		if (copy.f0 != x6 || copy.f10 == 0)
			return 0;
		if ((g_office_slots)[i].a != -1 ||
		    (g_office_slots)[i].type != 3 ||
		    (g_office_slots)[i].c >= 4)
			return 0;
		if ((g_office_slots)[j].a != -1 ||
		    (g_office_slots)[j].c >= 4)
			return 0;

		rec[0x168] = x6;
		(g_office_slots)[i].c++;
		(g_office_slots)[j].c++;
		return 1;
	}

	if ((g_office_slots)[i].a != -1 ||
	    (g_office_slots)[i].type != 3 ||
	    (g_office_slots)[i].c >= 4)
		return 0;
	rec[0x168] = x6;
	(g_office_slots)[i].c++;
	return 1;
}

/* Validates a generic office command string.  Parses the command buffer
 * and checks that the referenced entities and office type are valid.
 * Returns 1 when valid, 0 otherwise. */

// FUNCTION: SERVER 0x1000b440
// SYMBOL: _amt_ValidateCommand
// SIZE: 133

int __cdecl amt_ValidateCommand(char* arg1)
{
	int i;

	if (((unsigned char*) arg1)[6] == 0xff)
		return 1;

	i = 0;
	for (; i < 42; i++) {
		if (g_office_slots[i].id == ((unsigned char*) arg1)[0])
			break;
	}
	if (i >= 42)
		return 0;

	if ((g_office_slots)[i].type != 1)
		return 0;
	if ((g_office_slots)[i].d != -1)
		return 0;
	if (*(int*) (arg1 + 7) != -1) {
		if (gm_LookupEntityRecordById(*(int*) (arg1 + 7)) == 0)
			return 0;
	}
	if (*(int*) (arg1 + 1) != -1) {
		if (gm_LookupEntityRecordById(*(int*) (arg1 + 1)) == 0)
			return 0;
	}
	return 1;
}
