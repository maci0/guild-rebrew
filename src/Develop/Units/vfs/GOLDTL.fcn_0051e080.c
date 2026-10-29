#include <string.h>

struct VFS_DIR;
extern struct VFS_DIR* g_6b7fdc;
extern int __cdecl CloseVfsStream(void* stream);

void* __cdecl vfs_Tfopen(const char* name, const char* mode, struct VFS_DIR* root);
unsigned int __cdecl vfs_fwrite(const void* data, int size, int count, void* stream);
void __cdecl fcn_0051e9d0(void);
void __cdecl fcn_0051ea70(void);
int __cdecl fcn_0051e490(void* stream, int flags);
int __cdecl fcn_0051eb20(void* stream);
int __cdecl fcn_0051ebc0(void* stream);
int __cdecl fcn_0051ecf0(void* stream);
int __cdecl fcn_0051f170(void* stream);
int __cdecl ls_SaveEntities(void* stream);
int __cdecl fcn_0051ffc0(void* stream);
int __cdecl fcn_00520310(void* stream);
int __cdecl fcn_00520860(void* stream);
int __cdecl fcn_005208e0(void* stream);
int __cdecl fcn_00520d80(void* stream);
int __cdecl fcn_00520d90(void* stream);
int __cdecl fcn_005212c0(void* stream);
int __cdecl fcn_00521420(void* stream);
int __cdecl fcn_00521530(void* stream);
int __cdecl fcn_00521840(void* stream);
int __cdecl amt_fio_SaveAemter(void* stream);
int __cdecl fcn_004f49e0(void* stream);
int __cdecl fcn_004b64b0(void* stream);
int __cdecl fcn_004edd30(void* stream);
int __cdecl fcn_004adc40(void* stream);
int __cdecl fcn_004c0740(void* stream);
int __cdecl fcn_005922e0(void* stream);
int __cdecl fcn_005b1f10(void* stream);

/* ADDRESS: GOLDTL 0x0051e080 */
int __cdecl fcn_0051e080(char* name, char* slot, int flags)
{
	void* stream;

	stream = vfs_Tfopen(name, "wb", g_6b7fdc);
	if (stream == 0)
		return 0;
	strcpy((char*) 0x7e2480, slot);
	fcn_0051e9d0();
	if (fcn_0051e490(stream, flags) == 0) {
		CloseVfsStream(stream);
		fcn_0051ea70();
		return 0;
	}
	vfs_fwrite((void*) 0x699364, 4, 1, stream);
	vfs_fwrite((void*) 0x7749d0, 4, 1, stream);
	vfs_fwrite((void*) 0x7f4c00, 0xe, 1, stream);
	vfs_fwrite((void*) 0x773d75, 1, 1, stream);
	vfs_fwrite(*(char**) 0x773da8 + 4, 4, 1, stream);
	vfs_fwrite((void*) 0x773d68, 4, 1, stream);
	vfs_fwrite((void*) 0x773d6c, 4, 1, stream);
	vfs_fwrite((void*) 0x773d70, 4, 1, stream);
	vfs_fwrite((void*) 0x773d7c, 4, 1, stream);
	vfs_fwrite((void*) 0x100dc00, 0x18, 1, stream);
	vfs_fwrite((void*) 0x699368, 4, 1, stream);
	vfs_fwrite((void*) 0x773d38, 4, 1, stream);
	if (fcn_0051ebc0(stream) == 0) {
		CloseVfsStream(stream);
		fcn_0051ea70();
		return 0;
	}
	if (fcn_0051ecf0(stream) == 0) {
		CloseVfsStream(stream);
		fcn_0051ea70();
		return 0;
	}
	if (fcn_0051f170(stream) == 0) {
		CloseVfsStream(stream);
		fcn_0051ea70();
		return 0;
	}
	if (ls_SaveEntities(stream) == 0) {
		CloseVfsStream(stream);
		fcn_0051ea70();
		return 0;
	}
	if (fcn_00520310(stream) == 0) {
		CloseVfsStream(stream);
		fcn_0051ea70();
		return 0;
	}
	if (amt_fio_SaveAemter(stream) == 0) {
		CloseVfsStream(stream);
		fcn_0051ea70();
		return 0;
	}
	if (fcn_0051eb20(stream) == 0) {
		CloseVfsStream(stream);
		fcn_0051ea70();
		return 0;
	}
	if (!(flags & 2)) {
		if (fcn_004f49e0(stream) == 0) {
			CloseVfsStream(stream);
			fcn_0051ea70();
			return 0;
		}
		if (fcn_00520860(stream) == 0) {
			CloseVfsStream(stream);
			fcn_0051ea70();
			return 0;
		}
		if (fcn_005208e0(stream) == 0) {
			CloseVfsStream(stream);
			fcn_0051ea70();
			return 0;
		}
		if (fcn_00520d80(stream) == 0) {
			CloseVfsStream(stream);
			fcn_0051ea70();
			return 0;
		}
		if (fcn_00520d90(stream) == 0) {
			CloseVfsStream(stream);
			fcn_0051ea70();
			return 0;
		}
		if (fcn_005212c0(stream) == 0) {
			CloseVfsStream(stream);
			fcn_0051ea70();
			return 0;
		}
		if (fcn_00521420(stream) == 0) {
			CloseVfsStream(stream);
			fcn_0051ea70();
			return 0;
		}
		if (fcn_00521530(stream) == 0) {
			CloseVfsStream(stream);
			fcn_0051ea70();
			return 0;
		}
		if (fcn_00521840(stream) == 0) {
			CloseVfsStream(stream);
			fcn_0051ea70();
			return 0;
		}
		if (fcn_0051ffc0(stream) == 0) {
			CloseVfsStream(stream);
			fcn_0051ea70();
			return 0;
		}
		if (fcn_004b64b0(stream) == 0) {
			CloseVfsStream(stream);
			fcn_0051ea70();
			return 0;
		}
		if (fcn_005922e0(stream) == 0) {
			CloseVfsStream(stream);
			fcn_0051ea70();
			return 0;
		}
		if (fcn_005b1f10(stream) == 0) {
			CloseVfsStream(stream);
			fcn_0051ea70();
			return 0;
		}
		if (fcn_004edd30(stream) == 0) {
			CloseVfsStream(stream);
			fcn_0051ea70();
			return 0;
		}
		if (fcn_004adc40(stream) == 0) {
			CloseVfsStream(stream);
			fcn_0051ea70();
			return 0;
		}
		if (fcn_004c0740(stream) == 0) {
			CloseVfsStream(stream);
			fcn_0051ea70();
			return 0;
		}
	}
	CloseVfsStream(stream);
	fcn_0051ea70();
	return 1;
}
