#ifndef EVIDENCE_LINK_H
#define EVIDENCE_LINK_H

#include "Develop/client_types.h"

/* Two IDs occupy each eight-byte evidence entry. */
typedef Pair_99f800 CRIME_EVIDENCE_LINK;
// SIZE 0x8
extern CRIME_EVIDENCE_LINK g_99f800[0x800];

#endif
