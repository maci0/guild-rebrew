#include <string.h>

char* __cdecl fcn_0064d470(char* string, char* find);
char* __cdecl fcn_0064e2f9(char* path, char* mode);
int __cdecl fcn_0064ebe4(void* buffer, int size, int count, char* file);
int __cdecl fcn_0064e1fd(char* file);
int __cdecl fcn_0064d3f8(void);
int __cdecl fcn_0042a510(int handle, void* out);
void __cdecl fcn_0042a7c0(int handle);
void __cdecl fcn_0042a7f0(int handle);
int __cdecl fcn_0042a5d0(int handle, char* flag, void* data, int size);
int __cdecl fcn_00423920(char* path);
int __cdecl fcn_00423b80(char* name);
int __cdecl fcn_00424700(char* name);
void* __cdecl fcn_00423ac0(char* name);
void* __cdecl m_alloc(int size, char* tag);
void __cdecl m_FreeTracked(void* pointer);

/* ADDRESS: GOLDTL 0x00425550 */
int __cdecl fcn_00425550(char* name, char* ext)
{
	char path[256];
	int result;
	char* found;
	char* file;
	void* data;
	int size;
	int index;

	result = 0;
	file = fcn_0064d470(name, (char*) 0x6790c4);
	if (file == 0) {
		size = fcn_00424700(name);
		index = fcn_0064d3f8() % size;
		data = fcn_00423ac0(name);
		if (data == 0) {
			return result;
		}
		found = *(char**) ((char*) data + 0x38);
		if (found == 0) {
			return result;
		}
		while (index != 0) {
			index--;
			found = *(char**) (found + 0x104);
			if (found == 0) {
				return result;
			}
		}
		if (found == 0) {
			return result;
		}
		return fcn_00425550(found, ext);
	}
	if (*(int*) 0x6b7d80 == 0) {
		if (fcn_0042a510(*(int*) 0x6b7d7c, (void*) 0x6b7d80) == -1) {
			result = -1;
			return result;
		}
	}
	fcn_0042a7c0(*(int*) 0x6b7d80);
	if (*(void**) 0x6b7d84 != 0) {
		m_FreeTracked(*(void**) 0x6b7d84);
		*(int*) 0x6b7d84 = 0;
	}
	strcpy(path, name);
	found = fcn_0064d470(path, (char*) 0x679010);
	if (found != 0) {
		*found = 0;
		strcat(path, ext);
		strcat(path, name + (found - path) + 5);
	}
	size = fcn_00423920(path);
	if (size == 0) {
		result = -1;
		return result;
	}
	data = m_alloc(size, (char*) 0x6790b4);
	*(void**) 0x6b7d84 = data;
	if (data == 0) {
		result = -1;
		return result;
	}
	file = fcn_0064e2f9(path, (char*) 0x6750e8);
	if (file == 0) {
		m_FreeTracked(data);
		*(int*) 0x6b7d84 = 0;
		result = -1;
		return result;
	}
	if (fcn_0064ebe4(data, size, 1, file) != 1) {
		m_FreeTracked(data);
		*(int*) 0x6b7d84 = 0;
		result = -1;
		fcn_0064e1fd(file);
		return result;
	}
	if (fcn_00423b80(name) == 1) {
		found = (char*) 0x678fb8;
	} else {
		found = (char*) 0x678fb0;
	}
	if (fcn_0042a5d0(*(int*) 0x6b7d80, found, data, size) == 0) {
		fcn_0042a7f0(*(int*) 0x6b7d80);
		fcn_0064e1fd(file);
		return result;
	}
	m_FreeTracked(data);
	*(int*) 0x6b7d84 = 0;
	result = -1;
	fcn_0064e1fd(file);
	return result;
}
