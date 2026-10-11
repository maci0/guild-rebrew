#ifndef GROUP_NODE_H
#define GROUP_NODE_H

/* Allocation-group node (SIZE 0x28) shared by every tracker build.
 * Keep this layout private to memory tracking; unrelated translation units
 * do not use it. */
// SIZE 0x28
struct GroupNode {
	char name[0x10];
	int size_total;   /* 0x10 */
	int count_total;  /* 0x14 */
	int size_max;     /* 0x18 */
	int count_max;    /* 0x1c */
	int count;        /* 0x20 */
	struct GroupNode* next; /* 0x24 */
};

#endif /* GROUP_NODE_H */
