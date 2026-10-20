#include <ctype.h>
#include <string.h>

struct VFS_DIR;

typedef struct VFS_FILE_42ff50 {
	char* name;
	unsigned int offset;
	struct VFS_DIR* source;
	int packed;
	int stamp;
	unsigned int archive;
} VFS_FILE_42ff50;

typedef struct {
	unsigned char read : 1;
	unsigned char b1 : 1;
	unsigned char b2 : 1;
	unsigned char compressed : 1;
	unsigned char b4 : 1;
	unsigned char b5 : 1;
	unsigned char b6 : 1;
	unsigned char b7 : 1;
} VFS_MODE_BITS_42ff50;

void* __cdecl fcn_0042f120(char*, struct VFS_DIR*, struct VFS_DIR**);
void __cdecl fcn_0042f240(VFS_FILE_42ff50*, struct VFS_DIR*, struct VFS_DIR*, char*);
void __cdecl fcn_0042e540(char*);
void __cdecl fcn_0042e570(char*);
void __cdecl fcn_0042e520(char*);
void* __cdecl fcn_00464650(char*);
int __cdecl unzClose(char*);
int __cdecl fcn_00465790(char*, unsigned long, unsigned long);
int __cdecl fcn_00464a90(char*, unsigned long*, char*, unsigned long, void*, void*, void*, void*);
int __cdecl fcn_00465020(char*);
int __cdecl fcn_00464eb0(char*);
void* __cdecl m_PoolAlloc(void*, int, int);
void* __cdecl gzopen(char*, char*);
void* __cdecl fopen(char*, char*);
char* __cdecl strupr(char*);
int __cdecl fcn_0042fcd0(char*, struct VFS_DIR*);
void __cdecl fcn_0042ed00(char*, struct VFS_DIR*, int, int, int, int, int);
void __cdecl fcn_0041d9e0(char*);
int __cdecl sprintf(char*, const char*, ...);

/* ADDRESS: GOLDTL 0x0042ff50 */
void* __cdecl fcn_0042ff50(const char* cpath, const char* cmode, struct VFS_DIR* root)
{
	char* path;
	char* mode;
	char* stream;
	unsigned char packed;
	unsigned char binary;
	unsigned char read;
	struct VFS_DIR* dir;
	char* modes[2];
	char* p;
	VFS_FILE_42ff50* file;
	char* zip;
	void* h;
	int err;
	char name[0x100];
	char entry[0x100];
	char arch[0x100];
	unsigned long info[0x14];

	path = (char*) cpath;
	mode = (char*) cmode;
	stream = 0;
	if (!path || !*path || !mode || !root)
		return 0;
	read = 1;
	binary = 1;
	packed = 1;
	for (p = mode; *p; p++) {
		switch (toupper(*p)) {
		case 'B':
			binary = 1;
			break;
		case 'N':
			packed = 0;
			break;
		case 'R':
			read = 1;
			break;
		case 'T':
			binary = 0;
			break;
		case 'W':
			read = 0;
			break;
		case 'Z':
			packed = 1;
			break;
		}
	}
	if (!read)
		goto write_path;
	file = (VFS_FILE_42ff50*) fcn_0042f120(path, root, &dir);
	if (file) {
		if (file->source) {
			fcn_0042f240(0, file->source, 0, arch);
			strcat(arch, (char*) 0x6790c4 + file->archive * 6);
			fcn_0042e570(arch);
			zip = (char*) fcn_00464650(arch);
			if (zip) {
				fcn_0042f240(file, dir, file->source, entry);
				strupr(entry);
				if ((unsigned long) file->stamp > 0) {
					fcn_00465790(zip, file->stamp, file->packed);
					if (fcn_00464a90(zip, info, name, 0x100, 0, 0, 0, 0) == 0) {
						strupr(name);
						fcn_0042e540(name);
						if (info[8] > 0 && strcmp(entry, name) == 0)
							goto open_member;
					}
					goto close_zip;
				}
				do {
					if (fcn_00464a90(zip, info, name, 0x100, 0, 0, 0, 0) == 0) {
						strupr(name);
						fcn_0042e540(name);
						if (info[8] > 0 && strcmp(entry, name) == 0)
							goto open_member;
					}
				} while (fcn_00464eb0(zip) == 0);
close_zip:
				unzClose(zip);
				goto not_found;
open_member:
				err = fcn_00465020(zip);
				if (err != 0)
					goto close_zip;
				stream = (char*) m_PoolAlloc((void*) 0x6b7fe4, 0x140, 0x10);
				((VFS_MODE_BITS_42ff50*) (stream + 0x13c))->b2 = 1;
				((VFS_MODE_BITS_42ff50*) (stream + 0x13c))->b4 = 1;
				*(char**) (stream + 0x100) = zip;
				goto opened;
			}
			goto not_found;
		}
		modes[0] = "rt";
		modes[1] = "rb";
		fcn_0042f240(file, dir, 0, arch);
		fcn_0042e570(arch);
	} else {
		goto not_found;
	}
	if (packed) {
		h = gzopen(arch, modes[binary]);
	} else {
		h = fopen(arch, modes[binary]);
	}
	if (h == 0)
		goto not_found;
	stream = (char*) m_PoolAlloc((void*) 0x6b7fe4, 0x140, 0x10);
	*(void**) (stream + 0x100) = h;
	((VFS_MODE_BITS_42ff50*) (stream + 0x13c))->b4 = 0;
opened:
	strcpy(stream, path);
	((VFS_MODE_BITS_42ff50*) (stream + 0x13c))->b5 = 0;
	((VFS_MODE_BITS_42ff50*) (stream + 0x13c))->read = 1;
set_mode:
	((VFS_MODE_BITS_42ff50*) (stream + 0x13c))->b1 = binary;
	((VFS_MODE_BITS_42ff50*) (stream + 0x13c))->compressed = packed;
	*(int*) 0x6b7fec = *(int*) 0x6b7fec + 1;
	return stream;

write_path:
	for (p = path; *p == '\\' || *p == '/'; p++) {
	}
	strcpy(name, p);
	fcn_0042e540(name);
	strcpy(entry, name);
	fcn_0042e520(name);
	file = (VFS_FILE_42ff50*) fcn_0042f120(name, root, &dir);
	if (!file || file->source) {
		if (!fcn_0042fcd0(entry, root))
			return 0;
		if (!file) {
			fcn_0042ed00(name, root, 0, 0, 0, 0, -1);
			file = (VFS_FILE_42ff50*) fcn_0042f120(name, root, &dir);
			if (!file) {
				sprintf(entry, "vfs_Tfopen: Could write to \"%s\"!!", path);
				fcn_0041d9e0(entry);
				return stream;
			}
		}
	}
	modes[0] = "wt";
	modes[1] = "wb";
	file->offset = -1;
	file->source = 0;
	file->stamp = 0;
	fcn_0042f240(file, dir, 0, arch);
	fcn_0042e570(arch);
	if (packed) {
		h = gzopen(arch, modes[binary]);
	} else {
		h = fopen(arch, modes[binary]);
	}
	if (h == 0)
		return 0;
	stream = (char*) m_PoolAlloc((void*) 0x6b7fe4, 0x140, 0x10);
	*(void**) (stream + 0x100) = h;
	strcpy(stream, path);
	((VFS_MODE_BITS_42ff50*) (stream + 0x13c))->read = 0;
	((VFS_MODE_BITS_42ff50*) (stream + 0x13c))->b5 = 0;
	goto set_mode;

not_found:
	sprintf(name, "vfs_Tfopen: Could not find \"%s\"!!", path);
	return 0;
}
