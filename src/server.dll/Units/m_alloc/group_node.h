#ifndef GROUP_NODE_H
#define GROUP_NODE_H

/* Allocation-group list node (SIZE 0x28). Shared by m_AllocTracked.c and
 * m_ReportGroupInfo.c. Do not add to m_alloc.h: that header is included by
 * dozens of TUs that never used this layout. */
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
