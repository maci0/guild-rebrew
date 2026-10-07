extern char g_zlib_version[];
#include "../Error/error.h"
#include "../m_alloc/m_alloc.h"
#include "zlib.h"

#include <stdio.h>
#include <stdlib.h>

int __cdecl unzCloseCurrentFile(char*);
int __cdecl unzClose(char*);
typedef struct VFS_INFLATE {
	void* inbuf;            
	char* next_in;          
	unsigned int avail_in;  
	char pad_00c[4];
	char* next_out;         
	unsigned int avail_out; 
	unsigned int total_out; 
	char pad_01c[0x20];
	int in_off;             
	char pad_040[0x10];
	unsigned int crc;       
	char pad_054[4];
	unsigned int remaining; 
	unsigned int cap;       
	void* file;             
	int flag;               
	int base_off;           
} VFS_INFLATE;
// SIZE 0x6c
extern unsigned int __cdecl crc32(unsigned int crc, unsigned char* buf, unsigned int len);
extern int __cdecl inflate(void* zstrm, int flush); 

#include "../../DieGildeAddOn/game/entity.h"

int __cdecl unzCloseCurrentFile(char*);
int __cdecl unzClose(char*);
int __cdecl gzclose(int);

extern char g_stream_pool[1];
#include <string.h>

extern void __cdecl LogMessageInternal(char* file, unsigned int line, char* msg, int level);
extern int __cdecl unzReadCurrentFile(int zstrm, char* buf, unsigned int total);
extern int __cdecl gzread(void* handle, char* buf, unsigned int total);

#include <ctype.h>

extern void* __cdecl m_PoolAlloc(void* head, int size, int max_items);
extern void __cdecl m_pool_free(void* pool, void* item);

typedef struct {
	unsigned char read : 1;
	unsigned char b1 : 1;
	unsigned char b2 : 1;
	unsigned char compressed : 1;
	unsigned char b4 : 1;
	unsigned char b5 : 1;
	unsigned char b6 : 1;
	unsigned char b7 : 1;
} vfs_mode_bits;

/* Reads a single byte from a VFS stream. Advances the read
 * position and returns the byte value, or error on EOF. */

/* Data span SERVER 0x1002944c..0x100294a0
 *
 * The reference places "rb\\0\\0" (fopen mode), then the gzip magic dwords
 * 0x1f / 0x8b, then the vfs.c path and the gz-compressed-file message.
 * Without the 12-byte prefix, this TU's named strings start at 0x1002944c
 * and displace everything after them.  Callers already push/cmp the raw
 * addresses (gm_Open, vfs_OpenStream, vfs_ReadData); nothing names these
 * symbols, but they must occupy this exact span. */

char s_gzip_mode_rb[4] = { 'r', 'b', 0, 0 };

unsigned int g_gzip_magic_1f = 0x1f;

unsigned int g_gzip_magic_8b = 0x8b;

/* The client's directory tree (TL client 0x42e4d0..0x42fe60, in its order). The server never calls these
 * functions and /OPT:REF discards them. Their references still count: the file search calls KERNEL32's
 * FindFirstFileA, FindNextFileA, FindClose, FileTimeToLocalFileTime and FileTimeToSystemTime directly (the
 * reference's game library pass loads them between Error.c's and server.c's imports), remove loads
 * unlink.obj, bsearch and qsort their members, and mkdir and stricmp are old names that OLDNAMES resolves
 * after LIBCMT's first pass. The tree root and the pending-item pool are the two dwords before the stream
 * pool, as in the client (0x6b7fdc, 0x6b7fe0 below 0x6b7fe4). */
#include <io.h>
#include <direct.h>

extern char g_vfs_case_sensitive;
extern const char g_file_extension_names[];

/* SIZE 0x18 */
typedef struct VFS_FILE {
	char* name;
	unsigned int offset;
	struct VFS_DIR* source;
	int packed;
	int stamp;
	unsigned int archive;
} VFS_FILE;

/* SIZE 0x118 */
typedef struct VFS_ITEM {
	char name[0x100];
	unsigned int offset;
	struct VFS_DIR* source;
	int packed;
	int stamp;
	unsigned int archive;
	struct VFS_ITEM* next;
} VFS_ITEM;

/* SIZE 0x11c */
typedef struct VFS_DIR {
	char name[0x100];
	int count;
	VFS_FILE* files;
	struct VFS_DIR* next;
	struct VFS_DIR* child;
	struct VFS_DIR* parent;
	VFS_ITEM* items;
	char loaded;
} VFS_DIR;

extern VFS_DIR* g_vfs_root;
extern char g_vfs_item_pool[];

extern void __cdecl m_FreeTracked(void* ptr);
VFS_FILE* __cdecl vfs_FindFile(const char* name, VFS_DIR* dir, VFS_DIR** found_dir, char recurse);
char* __cdecl vfs_GetDirPath(VFS_DIR* dir, VFS_DIR* stop, char* out);
void __cdecl vfs_ScanArchive(char* path, VFS_DIR* parent, unsigned int archive);

/* Compares two VFS names: case-insensitively when g_vfs_case_sensitive is set. */
int __cdecl vfs_CompareNames(const char* a, const char* b)
{
	if (g_vfs_case_sensitive != 0) {
		return stricmp(a, b);
	}
	return strcmp(a, b);
}

/* Upper-cases a name unless the file system is case-sensitive. */
char* __cdecl vfs_NormalizeCase(char* name)
{
	if (g_vfs_case_sensitive != 0) {
		return name;
	}
	return _strupr(name);
}

/* Turns backslashes into slashes. */
void __cdecl vfs_ToSlashes(char* p)
{
	int n;

	if (p == 0) {
		return;
	}
	n = (int) strlen(p);
	if (n <= 0) {
		return;
	}
	do {
		if (*p == '\\') {
			*p = '/';
		}
		p++;
		n--;
	} while (n != 0);
}

/* Turns slashes into backslashes. */
void __cdecl vfs_ToBackslashes(char* p)
{
	int n;

	if (p == 0) {
		return;
	}
	n = (int) strlen(p);
	if (n <= 0) {
		return;
	}
	do {
		if (*p == '/') {
			*p = '\\';
		}
		p++;
		n--;
	} while (n != 0);
}

/* Returns parent's child directory called name, creating and appending it when missing. */
VFS_DIR* __cdecl vfs_GetSubDir(char* name, VFS_DIR* parent)
{
	VFS_DIR* p;
	VFS_DIR* n;

	if (parent != 0) {
		for (p = parent->child; p != 0; p = p->next) {
			if (vfs_CompareNames(name, p->name) == 0) {
				return p;
			}
		}
	}
	n = (VFS_DIR*) m_AllocTracked(sizeof(VFS_DIR), "vfs:IGetSubDir");
	strcpy(n->name, name);
	n->loaded = 0;
	n->parent = parent;
	if (parent != 0) {
		if (parent->child == 0) {
			parent->child = n;
		} else {
			p = parent->child;
			while (p->next != 0) {
				p = p->next;
			}
			p->next = n;
		}
	}
	return n;
}

/* bsearch comparator: a name against a file entry. */
int __cdecl vfs_CompareKey(const char* key, const char** file)
{
	return strcmp(key, *file);
}

/* bsearch comparator: a name against a file entry, ignoring case. */
int __cdecl vfs_CompareKeyNoCase(const char* key, const char** file)
{
	return stricmp(key, *file);
}

/* Binary-searches dir's sorted files for name, optionally recursing into subdirectories; stores the
 * owning directory in *found_dir. */
VFS_FILE* __cdecl vfs_FindFile(const char* name, VFS_DIR* dir, VFS_DIR** found_dir, char recurse)
{
	VFS_FILE* f;

	if (name == 0 || *name == 0 || dir == 0) {
		return 0;
	}
	if (dir->count > 0 && dir->loaded != 0) {
		f = (VFS_FILE*) bsearch(name, dir->files, dir->count, sizeof(VFS_FILE),
			g_vfs_case_sensitive != 0 ? vfs_CompareKeyNoCase : vfs_CompareKey);
		if (f != 0) {
			*found_dir = dir;
			return f;
		}
	}
	if (recurse) {
		for (dir = dir->child; dir != 0; dir = dir->next) {
			f = vfs_FindFile(name, dir, found_dir, 1);
			if (f != 0) {
				return f;
			}
		}
	}
	return 0;
}

/* Adds a file to dir: inserts it into the sorted file array once the
 * directory is loaded, else appends it to the pending item list. A name
 * already present is overwritten when the new offset is larger or -1 or its
 * archive index is lower, and cleared when it repeats the offset with no
 * source; a pending-list collision also formats a message that is unused. */
void __cdecl vfs_AddFile(char* name, VFS_DIR* dir, VFS_DIR* source, int stamp, int packed, unsigned int archive, unsigned int offset)
{
	VFS_FILE* f;
	VFS_FILE* mem;
	VFS_ITEM* it;
	VFS_ITEM* prev;
	VFS_DIR* found;
	char* names;
	int lo;
	int hi;
	int mid;
	int i;
	int len;
	int off;
	char* dst;
	char* src;
	int cnt;
	char msg[0x400];
	char dir_path[0x400];

	prev = 0;
	if (dir->loaded != 0) {
		f = vfs_FindFile(name, dir, &found, 0);
		if (f == 0) {
			if (dir->files != 0) {
				lo = 0;
				hi = dir->count - 1;
				while (hi >= lo) {
					mid = (lo + hi) >> 1;
					if (vfs_CompareNames(name, dir->files[mid].name) > 0) {
						lo = mid + 1;
					} else {
						hi = mid - 1;
					}
				}
				if (mid >= dir->count) {
					mid = dir->count;
				} else if (vfs_CompareNames(name, dir->files[mid].name) > 0) {
					mid++;
				}
				len = strlen(name) + 1;
				for (i = 0; i < dir->count; i++) {
					len += strlen(dir->files[i].name) + 1;
				}
				mem = (VFS_FILE*) m_AllocTracked(len + (dir->count + 1) * sizeof(VFS_FILE), "vfs:AddFile(sorted, insert)");
				names = (char*) (mem + dir->count + 1);
				for (i = 0; i < dir->count; i++) {
					strcpy(names, dir->files[i].name);
					dir->files[i].name = names;
					names += strlen(dir->files[i].name) + 1;
				}
				off = mid * sizeof(VFS_FILE);
				dst = (char*) mem;
				src = (char*) dir->files;
				__asm {
					mov edi, dst
					mov esi, src
					mov ebx, off
					lea ecx, [edi+edi*2]
					and ecx, 3
					sub ebx, ecx
					jle short L1
					rep movsb
					mov ecx, ebx
					and ebx, 3
					shr ecx, 2
					rep movsd
				L1:
					add ecx, ebx
					rep movsb
				}
				dst = (char*) (mem + mid + 1);
				src = (char*) dir->files + off;
				cnt = dir->count * sizeof(VFS_FILE) - off;
				__asm {
					mov edi, dst
					mov esi, src
					mov ebx, cnt
					lea ecx, [edi+edi*2]
					and ecx, 3
					sub ebx, ecx
					jle short L2
					rep movsb
					mov ecx, ebx
					and ebx, 3
					shr ecx, 2
					rep movsd
				L2:
					add ecx, ebx
					rep movsb
				}
				m_FreeTracked(dir->files);
				dir->files = mem;
				f = (VFS_FILE*) ((char*) mem + off);
			} else {
				dir->count = 0;
				dir->files = (VFS_FILE*) m_AllocTracked(strlen(name) + 1 + sizeof(VFS_FILE), "vfs:AddFile(sorted, first)");
				names = (char*) (dir->files + 1);
				f = dir->files;
			}
			strcpy(names, name);
			f->name = names;
			f->offset = offset;
			f->source = source;
			f->stamp = stamp;
			f->packed = packed;
			f->archive = archive;
			dir->count++;
			return;
		}
		if (offset > f->offset || offset == (unsigned int) -1 || archive < f->archive) {
			f->offset = offset;
			f->archive = archive;
			f->source = source;
			f->stamp = stamp;
			f->packed = packed;
		} else if (offset == f->offset && source == 0) {
			f->source = 0;
			f->stamp = 0;
			f->packed = 0;
			f->archive = 0;
		}
		return;
	}
	for (it = dir->items; it != 0; it = it->next) {
		if (vfs_CompareNames(name, it->name) == 0) {
			char old_path[0x400] = "";
			char new_path[0x400] = "";

			vfs_GetDirPath(dir, g_vfs_root, dir_path);
			if (it->source != 0) {
				vfs_GetDirPath(it->source, g_vfs_root, old_path);
				*strrchr(old_path, '/') = 0;
				strcat(old_path, g_file_extension_names + it->archive * 6);
				strcat(old_path, " ");
			}
			if (source != 0) {
				vfs_GetDirPath(source, g_vfs_root, new_path);
				*strrchr(new_path, '/') = 0;
				strcat(new_path, g_file_extension_names + archive * 6);
			}
			sprintf(msg, "vfs: name collision: \"%s%s\" %s%s", dir_path, name, old_path, new_path);
			if (offset > it->offset || offset == (unsigned int) -1 || archive < it->archive) {
				it->offset = offset;
				it->source = source;
				it->stamp = stamp;
				it->packed = packed;
				it->archive = archive;
			} else if (offset == it->offset && source == 0) {
				it->source = 0;
				it->stamp = 0;
				it->packed = 0;
				it->archive = 0;
			}
			return;
		}
		prev = it;
	}
	if (dir->items == 0) {
		it = (VFS_ITEM*) m_PoolAlloc(g_vfs_item_pool, sizeof(VFS_ITEM), 0x80);
		dir->items = it;
	} else {
		it = (VFS_ITEM*) m_PoolAlloc(g_vfs_item_pool, sizeof(VFS_ITEM), 0x80);
		prev->next = it;
	}
	strncpy(it->name, name, 0xff);
	it->source = source;
	it->stamp = stamp;
	it->packed = packed;
	it->archive = archive;
	it->offset = offset;
	it->next = 0;
}

/* Adds a file path below parent: creates the directories of its path, then the file. */
void __cdecl vfs_AddPath(char* path, VFS_DIR* parent, VFS_DIR* source, int stamp, int packed, unsigned int archive, unsigned int offset)
{
	char buf[0x100];
	char part[0x100];
	char* s;
	char* p;
	VFS_DIR* node;

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
		vfs_AddFile(s, node, source, stamp, packed, archive, offset);
	}
}

/* qsort comparator: orders two file entries by name. */
int __cdecl vfs_CompareFiles(const char** a, const char** b)
{
	return strcmp(*a, *b);
}

/* qsort comparator: orders two file entries by name, ignoring case. */
int __cdecl vfs_CompareFilesNoCase(const void* a, const void* b)
{
	return stricmp(*(const char**) a, *(const char**) b);
}

/* Turns a directory's pending items into its sorted file array, then does the same for its
 * subdirectories and following siblings when recurse is set. */
void __cdecl vfs_FinishFiles(VFS_DIR* dir, char recurse)
{
	VFS_ITEM* e;
	VFS_ITEM* next;
	char* names;
	int n;
	int len;
	int i;

	if (dir->items != 0 && dir->loaded == 0) {
		len = 0;
		n = 0;
		for (e = dir->items; e != 0; e = e->next) {
			n++;
			len += strlen(e->name) + 1;
		}
		dir->count = n;
		dir->files = (VFS_FILE*) m_AllocTracked(len + n * sizeof(VFS_FILE), "vfs:FinishedFiles");
		names = (char*) (dir->files + dir->count);
		for (e = dir->items, i = 0; e != 0; e = next) {
			strcpy(names, e->name);
			dir->files[i].name = names;
			dir->files[i].offset = e->offset;
			dir->files[i].source = e->source;
			dir->files[i].stamp = e->stamp;
			dir->files[i].packed = e->packed;
			dir->files[i].archive = e->archive;
			i++;
			names += strlen(e->name) + 1;
			next = e->next;
			m_pool_free(g_vfs_item_pool, e);
		}
		dir->items = 0;
		if (g_vfs_case_sensitive != 0) {
			qsort(dir->files, dir->count, sizeof(VFS_FILE), vfs_CompareFilesNoCase);
		} else {
			qsort(dir->files, dir->count, sizeof(VFS_FILE), vfs_CompareFiles);
		}
	} else if (dir->items == 0) {
		dir->count = 0;
	}
	dir->loaded = 1;
	if (recurse) {
		if (dir->child != 0) {
			vfs_FinishFiles(dir->child, 1);
		}
		if (dir->next != 0) {
			vfs_FinishFiles(dir->next, 1);
		}
	}
}

/* Walks the '/'-separated directory path from dir down its children;
 * returns the matching node, dir for an empty path, or 0 when path is 0
 * or a component is missing. */
VFS_DIR* __cdecl vfs_FindDir(char* path, VFS_DIR* dir)
{
	char buf[0x100];
	char name[0x100];
	char* p;
	VFS_DIR* cur;
	VFS_DIR* c;

	cur = dir;
	if (path == 0) {
		return 0;
	}
	if (*path != 0) {
		strcpy(buf, path);
		vfs_NormalizeCase(buf);
		if (buf[strlen(buf) - 1] != '/') {
			strcat(buf, "/");
		}
		strcpy(name, buf);
		for (p = strchr(name, '/'); p != 0 && cur != 0; p = strchr(name, '/')) {
			p++;
			strcpy(buf, p);
			*p = 0;
			for (c = cur->child; c != 0; c = c->next) {
				if (vfs_CompareNames(c->name, name) == 0) {
					break;
				}
			}
			cur = c;
			strcpy(name, buf);
		}
	}
	return cur;
}

/* Looks a path up: resolves its directory part, then the file name, which may start with '*' to search
 * the subdirectories too; returns the file entry and stores its directory in *found_dir. */
VFS_FILE* __cdecl vfs_LookupPath(char* path, VFS_DIR* root, VFS_DIR** found_dir)
{
	VFS_DIR* dir;
	char* p;
	char* s;
	VFS_FILE* f;
	char buf[0x100];
	char name[0x100];

	dir = root;
	strcpy(buf, path);
	vfs_NormalizeCase(buf);
	vfs_ToSlashes(buf);
	p = buf;
	while (*p != 0 && *p == '/') {
		p++;
	}
	strcpy(name, p);
	if (p != buf) {
		strcpy(buf, name);
	}
	s = strrchr(buf, '/');
	if (s != 0) {
		s++;
		strcpy(name, s);
		*s = 0;
		dir = vfs_FindDir(buf, dir);
		if (dir == 0) {
			return 0;
		}
	}
	if (name[0] == '*') {
		f = vfs_FindFile(name + 1, dir, &dir, 1);
	} else {
		f = vfs_FindFile(name, dir, &dir, 0);
	}
	if (f != 0) {
		*found_dir = dir;
	}
	return f;
}

/* Writes the path of file (or of dir itself, without its trailing '/', when
 * file is 0) relative to dir's ancestor stop into out; returns out, or 0
 * when dir is 0. */
char* __cdecl vfs_GetFilePath(VFS_FILE* file, VFS_DIR* dir, VFS_DIR* stop, char* out)
{
	char tmp[0x100];
	VFS_DIR* p;

	if (dir == 0) {
		return 0;
	}
	if (dir != stop) {
		strcpy(out, dir->name);
		if (file != 0) {
			strcat(out, file->name);
			p = dir;
			while (p->parent != 0 && p->parent != stop) {
				p = p->parent;
				strcpy(tmp, p->name);
				strcat(tmp, out);
				strcpy(out, tmp);
			}
			return out;
		} else {
			out[strlen(out) - 1] = 0;
			p = dir;
			while (p->parent != 0 && p->parent != stop) {
				p = p->parent;
				strcpy(tmp, p->name);
				strcat(tmp, out);
				strcpy(out, tmp);
			}
		}
	} else {
		strcpy(out, file->name);
	}
	return out;
}

/* Writes the path of dir relative to its ancestor stop into out. */
char* __cdecl vfs_GetDirPath(VFS_DIR* dir, VFS_DIR* stop, char* out)
{
	char tmp[0x100];
	VFS_DIR* p;

	p = dir;
	if (p == 0) {
		return 0;
	}
	strcpy(out, p->name);
	while (p != 0) {
		if (p->parent == stop) {
			break;
		}
		p = p->parent;
		strcpy(tmp, p->name);
		strcat(tmp, out);
		strcpy(out, tmp);
	}
	return out;
}

/* Strips the directory path of dir (root first) from the front of path and
 * writes the remainder into out; returns 0 when path is not below dir. */
char* __cdecl vfs_GetRelativePath(const char* path, VFS_DIR* dir, char* out)
{
	int len;
	int nlen;
	int i;
	VFS_DIR* cur;
	VFS_DIR* p;
	char buf[0x100];
	char tmp[0x100];

	strcpy(buf, path);
	vfs_NormalizeCase(buf);
	vfs_ToSlashes(buf);
	cur = g_vfs_root;
	while (cur != 0) {
		len = strlen(buf);
		nlen = strlen(cur->name);
		if (g_vfs_case_sensitive != 0) {
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
		for (p = dir; p != 0 && p->parent != cur; p = p->parent) {
		}
		cur = p;
	}
	strcpy(out, buf);
	return out;
}

/* Writes the path of the directory path names below stop into out; returns out, or 0 when it is missing. */
char* __cdecl vfs_GetDirPathOf(char* path, VFS_DIR* root, VFS_DIR* stop, char* out)
{
	VFS_DIR* dir;

	dir = vfs_FindDir(path, root);
	if (dir != 0) {
		if (dir != stop) {
			vfs_GetDirPath(dir, stop, out);
		} else {
			strcpy(out, "");
		}
		return out;
	}
	return 0;
}

/* Writes the path of the file path names below stop into out; returns out, or 0 when it is missing. */
char* __cdecl vfs_GetFilePathOf(char* path, VFS_DIR* root, VFS_DIR* stop, char* out)
{
	VFS_FILE* f;

	f = vfs_LookupPath(path, root, &root);
	if (f != 0) {
		vfs_GetFilePath(f, root, stop, out);
		return out;
	}
	return 0;
}

/* Mounts path below parent: a .BIN archive directly, or a directory tree
 * whose files and .BIN archives are added recursively; returns the new
 * directory node (sorted when parent is 0). */
VFS_DIR* __cdecl vfs_ScanDir(char* path, VFS_DIR* parent)
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
					vfs_ScanDir(buf, dir);
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
							vfs_ScanDir(sub, dir);
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


char* __cdecl unzOpen(const char* path);
int __cdecl unzGetCurrentFileInfo(char* file, unsigned long* info, char* name, unsigned long name_size, void* extra, unsigned long extra_size, char* comment, unsigned long comment_size);
int __cdecl unzGetFilePos(char* file, unsigned long* pos, unsigned long* num);
int __cdecl unzGoToNextFile(char* file);

/* Mounts every entry of a zip archive under a directory named after the archive. */
void __cdecl vfs_ScanArchive(char* path, VFS_DIR* parent, unsigned int archive)
{
	char* zip;
	VFS_DIR* dir;
	char* name;
	unsigned long pos;
	unsigned long num;
	unsigned long info[0x14];
	char buf[0x100];

	zip = unzOpen(path);
	if (zip == 0) {
		return;
	}
	strcpy(buf, path);
	*strrchr(buf, '.') = 0;
	name = strrchr(buf, '/');
	if (name == 0) {
		name = buf;
	} else {
		name++;
	}
	strcat(name, "/");
	dir = vfs_GetSubDir(name, parent);
	do {
		if (unzGetCurrentFileInfo(zip, info, buf, 0x100, 0, 0, 0, 0) == 0) {
			vfs_NormalizeCase(buf);
			vfs_ToSlashes(buf);
			if (info[7] > 0) {
				unzGetFilePos(zip, &pos, &num);
				vfs_AddPath(buf, dir, dir, pos, num, archive, info[4]);
			}
		}
	} while (unzGoToNextFile(zip) == 0);
	unzClose(zip);
}

/* Frees dir, its siblings and their subtrees with their files and pending items. */
void __cdecl vfs_FreeDirs(VFS_DIR* n)
{
	VFS_DIR* next;
	VFS_ITEM* it;
	VFS_ITEM* nx;

	while (n != 0) {
		it = n->items;
		next = n->next;
		while (it != 0) {
			nx = it->next;
			m_pool_free(g_vfs_item_pool, it);
			it = nx;
		}
		if (n->files != 0) {
			m_FreeTracked(n->files);
			n->files = 0;
		}
		if (n->child != 0) {
			vfs_FreeDirs(n->child);
		}
		m_FreeTracked(n);
		n = next;
	}
}

/* Creates every missing directory of path below dir. */
char __cdecl vfs_MakeDirs(char* path, VFS_DIR* dir)
{
	char* s;
	long h;
	char p[0x100];
	char rest[0x100];
	char cur[0x100];
	char base[0x100];
	struct _finddata_t fd;

	if (path == 0 || *path == 0) {
		return 0;
	}
	strcpy(p, path);
	s = strrchr(p, '/');
	if (s != 0) {
		vfs_GetDirPath(dir, 0, base);
		s[1] = 0;
		strcpy(rest, p);
		s = strchr(rest, '/');
		while (s != 0) {
			s++;
			strcpy(p, s);
			*s = 0;
			strcat(base, rest);
			strcpy(cur, base);
			s = strrchr(cur, '/');
			if (s != 0) {
				*s = 0;
			}
			h = _findfirst(cur, &fd);
			if (h == -1) {
				if (mkdir(cur) != 0) {
					return 0;
				}
			} else {
				_findclose(h);
			}
			strcpy(rest, p);
			s = strchr(rest, '/');
		}
	}
	return 1;
}

/* Deletes a loose file (one not inside an archive) from disk and from its directory's file array. */
char __cdecl vfs_RemoveFile(char* path, VFS_DIR* root)
{
	VFS_DIR* dir;
	char buf[0x100];
	VFS_FILE* e;
	VFS_DIR* d;

	e = vfs_LookupPath(path, root, &dir);
	if (e != 0 && e->source == 0) {
		d = dir;
		if (d != 0 && d->loaded != 0) {
			vfs_GetFilePath(e, d, 0, buf);
			vfs_ToBackslashes(buf);
			if (--d->count == 0) {
				m_FreeTracked(d->files);
				d->files = 0;
			} else {
				memmove(e, e + 1, (d->count - (e - d->files)) * sizeof(VFS_FILE));
			}
			return remove(buf) == 0;
		}
	}
	return 0;
}

int __cdecl CloseVfsStream(void* stream)
{
	int result;
	int n;
	unsigned int value;
	char* write_cursor;

	result = 0;
	if (stream != 0) {
		if (*(unsigned char*) ((char*) stream + 0x13c) & 0x20) {
			if (*(unsigned char*) ((char*) stream + 0x13c) & 8) {
				if (*(unsigned char*) ((char*) stream + 0x13c) & 1) {
					inflateEnd((char*) stream + 0x100);
				} else {
					deflate((char*) stream + 0x100, 4);
					deflateEnd((char*) stream + 0x100);
					if (*(unsigned int*) ((char*) stream + 0x110) >= 8) {
						write_cursor = *(char**) ((char*) stream + 0x10c);
						value = *(unsigned int*) ((char*) stream + 0x138);
						n = 4;
						do {
							*write_cursor = (char) value;
							value >>= 8;
							write_cursor++;
						} while (--n != 0);
						value = *(unsigned int*) ((char*) stream + 0x108);
						n = 4;
						do {
							*write_cursor = (char) value;
							value >>= 8;
							write_cursor++;
						} while (--n != 0);
						*(unsigned int*) ((char*) stream + 0x114) += 8;
						*(char**) ((char*) stream + 0x10c) += 8;
						*(unsigned int*) ((char*) stream + 0x110) -= 8;
					}
				}
			}
			if (!(*(unsigned char*) ((char*) stream + 0x13c) & 1)) {
				result = *(unsigned int*) ((char*) stream + 0x114);
			}
		} else {
				if (*(void**) ((char*) stream + 0x100) != 0) {
					if ((*(unsigned char*) ((char*) stream + 0x13c) & 1) && (*(unsigned char*) ((char*) stream + 0x13c) & 0x10)) {
						unzCloseCurrentFile(*(void**) ((char*) stream + 0x100));
						unzClose(*(void**) ((char*) stream + 0x100));
					} else if (*(unsigned char*) ((char*) stream + 0x13c) & 8) {
						gzclose((int) *(void**) ((char*) stream + 0x100));
					} else {
						fclose(*(void**) ((char*) stream + 0x100));
					}
				}
		}
		g_stream_count--;
		m_pool_free((int*) &g_stream_pool, stream);
	}
	return result;
}

int __cdecl vfs_ReadData(char* buf, int size, int count, char* stream)
{
	char name[0x100];
	int result;
	char* zstrm;
	/* The target homes the cursor pointer at [ebp-0xc] and the byte count
	 * at [ebp-8].  The count's home comes from the copy prelude, which
	 * names it as an asm operand; this local supplies the cursor's. */
	int zp;
	int total;
	char flags;

	result = -1;
	if (stream == 0) {
		goto done;
	}
	flags = *(unsigned char*) (stream + 0x13c);
	if (!(flags & 1)) {
		goto done;
	}
	zstrm = stream + 0x100;
	zp = (int) zstrm;
	if (*(int*) zstrm == 0 && !(flags & 0x20)) {
		goto done;
	}
	total = size * count;
	if ((flags & 0x20) && !(flags & 8)) {
		unsigned int avail;

		avail = *(unsigned int*) (stream + 0x104);
		if (avail < (unsigned int) total) {
			total = (int) avail;
		}
	}
	if (total == 0) {
		result = total;
		goto done;
	}
	if (buf == 0) {
		goto done;
	}
	if (flags & 0x20) {
		if (flags & 8) {
			*(char**) (stream + 0x10c) = buf;
			*(int*) (stream + 0x110) = total;
			inflate((void*) zp, 2);
			result = total - *(int*) (stream + 0x110);
			goto done;
		}
		{
			char* fsrc;

			fsrc = *(char**) zp;
			/* The original's copy is the 24-byte hand-written alignment
			 * prelude (docs/msvc6-allocator.md Finding 19): dest-align,
			 * then dwords, then the remainder, with a short-count fallback.
			 * No msvc6 C memcpy spelling emits it. */
			__asm {
				mov edi, buf
				mov esi, fsrc
				mov ebx, total
				lea ecx, [edi+edi*2]
				and ecx, 3
				sub ebx, ecx
				jle short L1
				rep movsb
				mov ecx, ebx
				and ebx, 3
				shr ecx, 2
				rep movsd
			L1:
				add ecx, ebx
				rep movsb
			}
		}
		result = total;
		*(char**) zp += total;
		{
			int avail;
			int consumed;
			avail = *(int*) (stream + 0x104);
			consumed = *(int*) (stream + 0x108);
			avail -= total;
			consumed += total;
			*(int*) (stream + 0x104) = avail;
			*(int*) (stream + 0x108) = consumed;
		}
		goto done;
	}
	if (flags & 0x10) {
		result = unzReadCurrentFile(*(int*) zstrm, buf, (unsigned int) total);
		flags = *(unsigned char*) (stream + 0x13c);
		if (!(flags & 4)) {
			goto done;
		}
		if ((unsigned int) result < 2) {
			goto done;
		}
		*(unsigned char*) (stream + 0x13c) = (unsigned char) (flags & ~4);
		if ((unsigned int) *(unsigned char*) buf != *(unsigned int*) &g_gzip_magic_1f ||
		    (unsigned int) *(unsigned char*) (buf + 1) != *(unsigned int*) &g_gzip_magic_8b) {
			goto done;
		}
		sprintf(name, "vfs: gz-compressed file (\"%s\") in zip found!", stream);
		LogMessageInternal("D:\\Develop\\Units\\vfs\\vfs.c", 0x5b4, name, 1);
		goto done;
	}
	if (flags & 8) {
		result = gzread(*(char**) zstrm, buf, total);
		goto done;
	}
	result = fread(buf, size, count, *(char**) zstrm);
done:
	return result;
}

int __cdecl vfs_OpenStream(unsigned char* buf, unsigned int size, char* mode_flags)
{
	char* stream;
	char* path_cursor;
	int result;
	int mode14;
	unsigned char mode13;
	unsigned char mode18;

	result = 0;
	*(unsigned char*) &mode14 = 1;
	mode18 = 1;
	mode13 = 1;
	if (buf == 0 || size <= 0) {
		goto done;
	}
	for (path_cursor = mode_flags; *path_cursor != 0; path_cursor++) {
	switch (toupper(*path_cursor)) {
		case 'N':
			mode18 = 0;
			mode13 = 0;
			break;
		case 'R':
			*(unsigned char*) &mode14 = 1;
			break;
		case 'W':
			*(unsigned char*) &mode14 = 0;
			break;
		case 'Z':
			mode18 = 1;
			mode13 = 0;
			break;
		default:
			break;
		}
	}
	stream = (char*) m_PoolAlloc((void*) &g_stream_pool, 0x140, 0x10);
	*(unsigned char*) (stream + 0x13c) = (unsigned char) ((*(unsigned char*) (stream + 0x13c) & 0xeb) | 0x22);
	if (*(unsigned char*) &mode14 != 0) {
		if (mode13 != 0) {
			if (size <= 10) {
				mode18 = 0;
			} else if (buf[0] == *(int*) &g_gzip_magic_1f && buf[1] == *(int*) &g_gzip_magic_8b) {
				mode18 = 1;
				goto inflate_setup;
			} else {
				mode18 = 0;
			}
		} else if (mode18 != 0) {
			goto inflate_setup;
		}
		*(char**) (stream + 0x100) = (char*) buf;
		*(unsigned int*) (stream + 0x104) = size;
		*(int*) (stream + 0x108) = 0;
		goto finalize;
	inflate_setup:
		*(char**) (stream + 0x100) = (char*) buf + 10;
		*(unsigned int*) (stream + 0x104) = size - 10;
		*(int*) (stream + 0x10c) = 0;
		*(int*) (stream + 0x110) = 0;
		*(int*) (stream + 0x120) = 0;
		*(int*) (stream + 0x124) = 0;
		if (inflateInit2_((void*) (stream + 0x100), -0xf, (char*) &g_zlib_version, 0x38) == 0) {
			goto finalize;
		}
		goto cleanup;
	}
	if (mode18 != 0) {
		if (size < 0x12) {
			goto cleanup;
		}
		buf[0] = *(unsigned char*) &g_gzip_magic_1f;
		buf[1] = *(unsigned char*) &g_gzip_magic_8b;
		buf[2] = 8;
		buf[8] = 0;
		buf[7] = 0;
		buf[6] = 0;
		buf[5] = 0;
		buf[4] = 0;
		buf[3] = 0;
		buf[9] = 0xb;
		*(char**) (stream + 0x100) = 0;
		*(unsigned int*) (stream + 0x104) = 0;
		*(char**) (stream + 0x10c) = (char*) buf + 10;
		*(unsigned int*) (stream + 0x110) = size - 10;
		*(int*) (stream + 0x120) = 0;
		*(int*) (stream + 0x124) = 0;
		*(int*) (stream + 0x138) = crc32(0, 0, 0);
		if (deflateInit2_((void*) (stream + 0x100), -1, 8, -0xf, 8, 0, (char*) &g_zlib_version, 0x38) != 0) {
			goto cleanup;
		}
		*(int*) (stream + 0x114) = 0xa;
	} else {
		*(char**) (stream + 0x10c) = (char*) buf;
		*(unsigned int*) (stream + 0x110) = size;
		*(int*) (stream + 0x114) = 0;
	}
finalize:
	if (stream != 0) {
		g_stream_count = g_stream_count + 1;
		((vfs_mode_bits*) (stream + 0x13c))->read = *(unsigned char*) &mode14;
		((vfs_mode_bits*) (stream + 0x13c))->compressed = mode18;
		sprintf(stream, "0x%08X -> length: %u, read: %u compressed: %u", buf, size, (unsigned char) mode14, mode18);
	}
	result = (int) stream;
done:
	return result;
cleanup:
	m_pool_free((void*) &g_stream_pool, stream);
	return 0;
}

/* Mounts the file system rooted at name; flag selects case-insensitive compares. Returns whether the
 * root was found. TL client 0x431070; getcwd is called by its old name. */
int __cdecl vfs_init(char* name, char flag)
{
	char cwd[0x100];
	char buf[0x100];

	g_stream_count = 0;
	g_vfs_case_sensitive = flag;
	g_vfs_root = vfs_ScanDir(name, 0);
	getcwd(cwd, 0x100);
	sprintf(buf, "vfs_init: root -> \"%s\" relative to \"%s\"", name, cwd);
	*(int*) g_vfs_item_pool = 0;
	return g_vfs_root != 0;
}
