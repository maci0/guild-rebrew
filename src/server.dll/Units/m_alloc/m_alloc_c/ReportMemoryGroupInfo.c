// FUNCTION: SERVER 0x10006990
#include <stdio.h>
#include <string.h>

#pragma intrinsic(memset, strcmp, strcpy)

void __cdecl ReportFatalError(char*, unsigned int, char*); /* 0x10003520 */
void __cdecl ReportMessage(char* msg);
void* __cdecl malloc(unsigned int size); /* 0x1001a7f7 - game malloc */
void __cdecl ReportMemoryGroupInfo(const char* toggle);
extern void __cdecl LogMessageInternal(const char*, int, const char*, int);
// CFLAGS: /O2 /Gd

struct GroupNode {
	char name[0x10];
	int size_total;   /* 0x10 */
	int count_total;  /* 0x14 */
	int size_max;     /* 0x18 */
	int count_max;    /* 0x1c */
	int count;        /* 0x20 */
	struct GroupNode* next; /* 0x24 */
};

void* __cdecl fcn_1001aff0(const char* haystack, const char* needle);
char* __cdecl fcn_1001a540(const char* s, int c);
extern int g_array_count;
extern int g_stat1;
extern int g_stat2;
extern int g_stat3;
extern int g_stat4;
extern void* g_array_ptr;
extern char g_alloc_root_name; /* 0x117640a0 - root group node */

void __cdecl ReportMemoryGroupInfo(const char* toggle)
{
	char buf[0x400];
	char buf2[0x10];
	struct GroupNode* node;
	char* slot;
	int i;
	char match;
	char* p;

	if (g_stat1 == 0 && g_stat2 == 0) {
		sprintf(buf, "[*] Memory-Subsystem-Information:\n--> max_used %i blocks in %i bytes (%ik).", g_stat4, g_stat3, g_stat3 >> 10);
		} else {
		sprintf(buf, "[*] Memory-Subsystem-Information: [*]\n--> max_used %i blocks in %i bytes (%ik). %i block(s) left in %i (%ik) bytes.", g_stat4, g_stat3, g_stat3 >> 10, g_stat2, g_stat1, g_stat1 >> 10);
	}
	LogMessageInternal("D:\\Develop\\Units\\m_alloc\\m_alloc.c", 0x1b5, buf, 1);
	LogMessageInternal("D:\\Develop\\Units\\m_alloc\\m_alloc.c", 0x1b6, "---g-r-o-u-p---i-n-f-o-s---", 1);
	node = (struct GroupNode*) &g_alloc_root_name;
	while (node != 0) {
		if (toggle != 0 && fcn_1001aff0(node->name, toggle) != 0) {
			match = 1;
		} else {
			match = 0;
		}
		if (node->count_max > 0) {
			if (node->name[0] != '!' || node->count_total != 0 || match != 0) {
				if (toggle == 0 || match != 0) {
					strcpy(buf2, node->name);
					p = fcn_1001a540(buf2, 0x3a);
					if (p != 0) {
						*p = 0;
					}
					if (node->size_total == 0 && node->count_total == 0) {
						sprintf(buf, "[%s] w/ %i (%ik) bytes in %i block(s) (called %i times).", buf2, node->size_max, node->size_max >> 10, node->count_max, node->count);
		} else {
						sprintf(buf, "[%s] -> w/ %i/%i (%ik/%ik) bytes in %i/%i block(s) (called %i times).", buf2, node->size_total, node->size_max, node->size_total >> 10, node->size_max >> 10, node->count_total, node->count_max, node->count);
					}
					LogMessageInternal("D:\\Develop\\Units\\m_alloc\\m_alloc.c", 0x1cc, buf, 1);
					if (match != 0) {
						for (i = 0, slot = (char*) g_array_ptr; i < g_array_count; i++, slot += 0x10) {
							if (*(char**) (slot + 8) != 0 && *(struct GroupNode**) slot == node) {
								sprintf(buf, "{%s} w/ %i bytes (%ik).", *(char**) (slot + 4), *(int*) (slot + 0xc), *(int*) (slot + 0xc) >> 10);
								LogMessageInternal("D:\\Develop\\Units\\m_alloc\\m_alloc.c", 0x1d5, buf, 1);
							}
						}
						LogMessageInternal("D:\\Develop\\Units\\m_alloc\\m_alloc.c", 0x1d8, "---g-r-o-u-p---d-o-n-e---", 1);
					}
				}
			}
		}
		node = node->next;
	}
	LogMessageInternal("D:\\Develop\\Units\\m_alloc\\m_alloc.c", 0x1dc, "---d-u-m-p---d-o-n-e---", 1);
}

