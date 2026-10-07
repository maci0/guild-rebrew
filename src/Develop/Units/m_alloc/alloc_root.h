#ifndef ALLOC_ROOT_H
#define ALLOC_ROOT_H
#include "group_node.h"

extern struct GroupNode g_alloc_root;
#define g_alloc_root_name (((int*) g_alloc_root.name)[0])
#define g_alloc_root_name_4 (((int*) g_alloc_root.name)[1])
#define g_alloc_root_size_total g_alloc_root.size_total
#define g_alloc_root_count g_alloc_root.count_total
#define g_alloc_root_size_max g_alloc_root.size_max
#define g_alloc_root_count_max g_alloc_root.count_max
#define g_alloc_root_spare g_alloc_root.count
#define g_list_head g_alloc_root.next
#endif
