#include <string.h>
#include <ctype.h>

/* SIZE 0x11c */
typedef struct VFS_DIR {
	char name[0x100];
	int count;
	void* files;
	struct VFS_DIR* next;
	struct VFS_DIR* child;
	struct VFS_DIR* parent;
	void* items;
	char loaded;
} VFS_DIR;

extern VFS_DIR* g_6b7fdc;
extern char g_6b7fe8;
extern int __cdecl fcn_0042e520(int a);
extern void __cdecl fcn_0042e540(char* p);

/* ADDRESS: GOLDTL 0x0042f4d0 */
char* __cdecl fcn_0042f4d0(const char* path, VFS_DIR* dir, char* out)
{
	int len;
	int nlen;
	int i;
	VFS_DIR* cur;
	VFS_DIR* p;
	char buf[0x100];
	char tmp[0x100];

	strcpy(buf, path);
	fcn_0042e520((int) buf);
	fcn_0042e540(buf);
	cur = g_6b7fdc;
	while (cur != 0) {
		len = (int) strlen(buf);
		nlen = (int) strlen(cur->name);
		if (g_6b7fe8 != 0) {
			for (i = 0; i < len; i++) {
				if (i >= nlen || toupper(cur->name[i]) != toupper(buf[i])) {
					break;
				}
			}
		} else {
			for (i = 0; i < len; i++) {
				if (i >= nlen || cur->name[i] != buf[i]) {
					break;
				}
			}
		}
		if (i != nlen) {
			return 0;
		}
		strcpy(tmp, buf + i);
		strcpy(buf, tmp);
		p = dir;
		while (p != 0 && p->parent != cur) {
			p = p->parent;
		}
		cur = p;
	}
	strcpy(out, buf);
	return out;
}
