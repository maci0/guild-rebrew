#ifndef MEMTRACK_H
#define MEMTRACK_H

/* Memory tracker: g_6b6f80 points to g_6b6f64 block records; each block
 * belongs to a pool in the list starting at g_14cc5c0. */
struct MemPool {
	char name[0x10];
	int used;
	int used_blocks;
	int max;
	int max_blocks;
	int calls;
	struct MemPool* next;
};
// SIZE 0x28

typedef struct {
	struct MemPool* pool;
	char* tag;
	void* ptr;
	int size;
} MemBlock;
// SIZE 0x10

#endif
