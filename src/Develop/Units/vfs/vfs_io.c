#include <string.h>

typedef struct VFS_DIR VFS_DIR;

VFS_DIR* __cdecl vfs_GetSubDir(char*, VFS_DIR*);
void __cdecl vfs_AddFile(char*, VFS_DIR*, VFS_DIR*, int, int, unsigned int, unsigned int);
#include <windows.h>

extern const char g_file_extension_names[];

char* __cdecl vfs_NormalizeCase(char*);
void __cdecl vfs_ToSlashes(char*);
int __cdecl vfs_CompareNames(const char*, const char*);
VFS_DIR* __cdecl vfs_GetSubDir(char*, VFS_DIR*);
void __cdecl vfs_AddFile(char*, VFS_DIR*, VFS_DIR*, int, int, unsigned int, unsigned int);
void __cdecl vfs_FinishFiles(VFS_DIR*, char);
void __cdecl vfs_ScanArchive(char*, VFS_DIR*, unsigned int);
VFS_DIR* __cdecl fcn_0042f6d0(char*, VFS_DIR*);
int __cdecl vfs_ReadData(char* buf, int size, int count, char* stream);

/* ADDRESS: GOLD 0x0042f4d0 */
/* ADDRESS: GOLDTL 0x0042ed00 */
void __cdecl fcn_0042ed00(char* path, void* parent, int a3, int a4, int a5, int a6, int a7)
{
	char buf[0x100];
	char part[0x100];
	char* s;
	char* p;
	void* node;

	if (path[strlen(path) - 1] != '/') {
		node = parent;
		strcpy(buf, path);
		s = buf;
		p = strchr(buf, '/');
		while (p != 0) {
			strcpy(part, s);
			strchr(part, '/')[1] = 0;
			node = vfs_GetSubDir(part, node);
			s = p + 1;
			p = strchr(s, '/');
		}
		vfs_AddFile(s, node, a3, a4, a5, a6, a7);
	}
}

/* Mounts path below parent: a .BIN archive directly, or a directory tree whose
 * files and .BIN archives are added recursively; returns the new directory
 * node (sorted when parent is 0). */
/* ADDRESS: GOLDTL 0x0042f6d0 */
/* ADDRESS: GOLD 0x0042fce0 */
VFS_DIR* __cdecl fcn_0042f6d0(char* path, VFS_DIR* parent)
{
	VFS_DIR* dir;
	char* ext;
	HANDLE h;
	SYSTEMTIME st;
	FILETIME ft;
	char buf[0x100];
	char dirpath[0x100];
	WIN32_FIND_DATAA fd;
	char name[0x100];
	char sub[0x100];
	char* s;
	char found;
	int i;
	int n;

	dir = 0;
	strcpy(dirpath, path);
	vfs_NormalizeCase(dirpath);
	if (parent == 0) {
		vfs_ToSlashes(dirpath);
	}
	ext = strrchr(dirpath, '.');
	n = strlen(dirpath) - 1;
	if ((n <= 0 || (dirpath[n] != '/' && dirpath[n] != '\\')) && ext != 0) {
		for (i = 0; i <= 6; i++) {
			if (vfs_CompareNames(ext, g_file_extension_names + i * 6) == 0) {
				vfs_ScanArchive(dirpath, parent, i);
			}
		}
	} else {
		if (dirpath[strlen(dirpath) - 1] != '/') {
			strcat(dirpath, "/");
		}
		strcpy(buf, dirpath);
		strcat(buf, "*");
		strcpy(sub, buf);
		h = FindFirstFileA(buf, &fd);
		if (h != INVALID_HANDLE_VALUE) {
			if (parent != 0) {
				strcpy(buf, dirpath);
				s = strrchr(buf, '/');
				if (s != 0) {
					*s = 0;
					s = strrchr(buf, '/');
				}
				if (s != 0) {
					strcpy(name, s + 1);
					strcat(name, "/");
				} else {
					strcpy(name, "");
				}
			} else {
				strcpy(name, dirpath);
			}
			dir = vfs_GetSubDir(name, parent);
			do {
				if (strcmp(fd.cFileName, ".") == 0 || strcmp(fd.cFileName, "..") == 0) {
					continue;
				}
				if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
					strcpy(buf, dirpath);
					strcat(buf, fd.cFileName);
					strcat(buf, "/");
					fcn_0042f6d0(buf, dir);
					continue;
				}
				found = 0;
				strcpy(buf, fd.cFileName);
				vfs_NormalizeCase(buf);
				ext = strrchr(buf, '.');
				if (ext != 0) {
					for (i = 0; i <= 6; i++) {
						if (vfs_CompareNames(ext, g_file_extension_names + i * 6) == 0) {
							strcpy(sub, dirpath);
							strcat(sub, buf);
							fcn_0042f6d0(sub, dir);
							found = 1;
						}
					}
					if (found) {
						continue;
					}
				}
				FileTimeToLocalFileTime(&fd.ftLastWriteTime, &ft);
				FileTimeToSystemTime(&ft, &st);
				vfs_AddFile(buf, dir, 0, 0, 0, 0,
					((unsigned long) (st.wYear - 1980) << 25) | ((unsigned long) st.wMonth << 21)
					 | ((unsigned long) st.wDay << 16) | ((unsigned long) st.wHour << 11)
					 | ((unsigned long) st.wMinute << 5) | (st.wSecond >> 1));
			} while (FindNextFileA(h, &fd));
			FindClose(h);
		}
	}
	if (parent == 0 && dir != 0) {
		vfs_FinishFiles(dir, 1);
	}
	return dir;
}

/* ADDRESS: GOLD 0x00430d90 */
/* ADDRESS: GOLDTL 0x00430870 */
int __cdecl fcn_00430870(void* a1)
{
	char c;

	if (vfs_ReadData(&c, 1, 1, a1) == 1) {
		return c;
	}
	return -1;
}
