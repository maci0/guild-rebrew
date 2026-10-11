#ifndef MEMTRACK_H
#define MEMTRACK_H

/* Memory tracker: g_6b6f80 points to g_6b6f64 block records; each block
 * belongs to a pool in the list starting at g_14cc5c0. */
#include "Develop/Units/m_alloc/group_node.h"

typedef struct {
	struct GroupNode* pool;
	char* tag;
	void* ptr;
	int size;
} MemBlock;
// SIZE 0x10

#endif
