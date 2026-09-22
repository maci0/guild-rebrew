#ifndef OFFICE_SLOT_H
#define OFFICE_SLOT_H

/* Packed office-slot record (0x18). Shared by aemter2.c and
 * amt_ExecuteOfficeAssignment.c. Pack stays in this header; do not
 * include from entity.h (loadsave TUs). */
#pragma pack(push, 1)
// SIZE 0x18
typedef struct {
	char type;         /* +0 */
	char pad0[3];
	int entityId;      /* +4 */
	char role;         /* +8 */
	char pad1[3];
	int count;         /* +0xc */
	char state;        /* +0x10 */
	char pad2[3];
	int assignmentId;  /* +0x14 */
} OfficeSlot;
#pragma pack(pop)

#endif /* OFFICE_SLOT_H */
