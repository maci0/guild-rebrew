#include <stdlib.h>
#include <string.h>

// SIZE 0x18
struct file_42ee50 {
	char* name;
	int offset;
	int size;
	int packed;
	int stamp;
	int flags;
};

extern char g_6b7fe0[];
extern char g_6b7fe8;

struct file_42ee50* __cdecl fcn_0041db70(int size, const char* tag);
void __cdecl m_pool_free(char*, char*);
int __cdecl fcn_0042ee30(const void*, const void*);
int __cdecl fcn_0042edf0(const void*, const void*);

// FUNCTION: GOLD 0x42f620
// FUNCTION: GOLDTL 0x42ee50

/* Turns a VFS directory's list of added files into its sorted file array,
 * then does the same for the subdirectories and following siblings. */
void __cdecl fcn_0042ee50(char* dir, char recurse)
{
	char* e;
	char* next;
	char* names;
	int n;
	int len;
	int i;

	if (*(char**) (dir + 0x114) != 0 && dir[0x118] == 0) {
		len = 0;
		n = 0;
		for (e = *(char**) (dir + 0x114); e != 0; e = *(char**) (e + 0x114)) {
			n++;
			len += strlen(e) + 1;
		}
		*(int*) (dir + 0x100) = n;
		*(struct file_42ee50**) (dir + 0x104) = fcn_0041db70(len + n * sizeof(struct file_42ee50), "vfs:FinishedFiles");
		names = (char*) (*(struct file_42ee50**) (dir + 0x104) + *(int*) (dir + 0x100));
		for (e = *(char**) (dir + 0x114), i = 0; e != 0; e = next) {
			strcpy(names, e);
			(*(struct file_42ee50**) (dir + 0x104))[i].name = names;
			(*(struct file_42ee50**) (dir + 0x104))[i].offset = *(int*) (e + 0x100);
			(*(struct file_42ee50**) (dir + 0x104))[i].size = *(int*) (e + 0x104);
			(*(struct file_42ee50**) (dir + 0x104))[i].stamp = *(int*) (e + 0x10c);
			(*(struct file_42ee50**) (dir + 0x104))[i].packed = *(int*) (e + 0x108);
			(*(struct file_42ee50**) (dir + 0x104))[i].flags = *(int*) (e + 0x110);
			i++;
			names += strlen(e) + 1;
			next = *(char**) (e + 0x114);
			m_pool_free(g_6b7fe0, e);
		}
		*(char**) (dir + 0x114) = 0;
		if (g_6b7fe8 != 0) {
			qsort(*(struct file_42ee50**) (dir + 0x104), *(int*) (dir + 0x100), sizeof(struct file_42ee50), fcn_0042ee30);
		} else {
			qsort(*(struct file_42ee50**) (dir + 0x104), *(int*) (dir + 0x100), sizeof(struct file_42ee50), fcn_0042edf0);
		}
	} else if (*(char**) (dir + 0x114) == 0) {
		*(int*) (dir + 0x100) = 0;
	}
	dir[0x118] = 1;
	if (recurse) {
		if (*(char**) (dir + 0x10c) != 0) {
			fcn_0042ee50(*(char**) (dir + 0x10c), 1);
		}
		if (*(char**) (dir + 0x108) != 0) {
			fcn_0042ee50(*(char**) (dir + 0x108), 1);
		}
	}
}
