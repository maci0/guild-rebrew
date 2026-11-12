#include <string.h>
extern void* g_6b7d80;
extern void* g_6b7d84;
extern int g_6b7d7c;
extern char g_679010[];
extern char g_6750e8[];

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
	char path[0x104];
	int result;
	char* found;
	char* file;
	void* data;
	int size;
	int index;

	result = 0;
	file = strstr(name, ".");
	if (file != 0) {
		if ((int) g_6b7d80 == 0) {
			if (fcn_0042a510(g_6b7d7c, &g_6b7d80) == -1) {
				goto fail;
			}
		}
		fcn_0042a7c0((int) g_6b7d80);
		if (g_6b7d84 != 0) {
			m_FreeTracked(g_6b7d84);
			g_6b7d84 = 0;
		}
		strcpy(path, name);
		found = strstr(path, g_679010);
		if (found != 0) {
			*found = 0;
			strcat(path, ext);
			strcat(path, name + (found - path) + 5);
		}
		size = fcn_00423920(path);
		if (size == 0) {
			goto fail;
		}
		g_6b7d84 = m_alloc(size, "sbs_PlaySample");
		if (g_6b7d84 == 0) {
			goto fail;
		}
		file = fcn_0064e2f9(path, g_6750e8);
		if (file == 0) {
			goto free_failed;
		}
		if (fcn_0064ebe4(g_6b7d84, size, 1, file) != 1) {
			goto close_failed;
		}
		if (fcn_00423b80(name) == 1) {
			found = ".wav";
		} else {
			found = ".mp3";
		}
		if (fcn_0042a5d0((int) g_6b7d80, found, g_6b7d84, size) == 0) {
			fcn_0042a7f0((int) g_6b7d80);
			fcn_0064e1fd(file);
			return result;
		}
close_failed:
		m_FreeTracked(g_6b7d84);
		g_6b7d84 = 0;
		result = -1;
		fcn_0064e1fd(file);
		return result;
free_failed:
		m_FreeTracked(g_6b7d84);
		g_6b7d84 = 0;
fail:
		result = -1;
		return result;
	} else {
		size = fcn_00424700(name);
		index = fcn_0064d3f8() % size;
		data = fcn_00423ac0(name);
		if (data == 0) {
			goto fail;
		}
		found = *(char**) ((char*) data + 0x38);
		if (found == 0) {
			return result;
		}
		while (index-- != 0) {

			found = *(char**) (found + 0x104);
			if (found == 0) {
				return result;
			}
		}
		if (found == 0) {
			return result;
		}
		result = fcn_00425550(found, ext);
		return result;
	}
}
