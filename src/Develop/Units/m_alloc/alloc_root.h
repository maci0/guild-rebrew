#ifndef ALLOC_ROOT_H
#define ALLOC_ROOT_H
#include "group_node.h"

extern struct GroupNode m_AllocRoot;
#define g_alloc_root_name (((int*) m_AllocRoot.name)[0])
#define g_alloc_root_name_4 (((int*) m_AllocRoot.name)[1])
#define g_alloc_root_size_total m_AllocRoot.size_total
#define g_alloc_root_count m_AllocRoot.count_total
#define g_alloc_root_size_max m_AllocRoot.size_max
#define g_alloc_root_count_max m_AllocRoot.count_max
#define g_alloc_root_spare m_AllocRoot.count
#define g_list_head m_AllocRoot.next
#endif
