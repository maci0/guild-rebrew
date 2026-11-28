#include <string.h>
extern void* g_6b7d80;
extern void* g_6b7d84;
extern int sb_WaveDriver;
extern char g_679010[];
#include "Develop/DieGildeAddOn/game/game_data.h"

char* __cdecl fcn_0064e2f9(char* path, char* mode);
int __cdecl fcn_0064ebe4(void* buffer, int size, int count, char* file);
int __cdecl fcn_0064e1fd(char* file);
int __cdecl fcn_0064d3f8(void);
int __cdecl msx_AllocateSampleHandle(int handle, void* out);
void __cdecl msx_InitSample(int handle);
void __cdecl msx_StartSample(int handle);
int __cdecl msx_SetSampleData(int handle, char* flag, void* data, int size);
int __cdecl sbs_GetFileSize(char* path);
int __cdecl sbs_GetAudioFormat(char* name);
int __cdecl sbs_CountSetEntries(char* name);
void* __cdecl sbs_FindSet(char* name);
void* __cdecl m_alloc(int size, char* tag);
void __cdecl m_FreeTracked(void* pointer);

/* ADDRESS: GOLDTL 0x00425550 */
int __cdecl sbs_PlaySample(char* name, char* ext)
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
			if (msx_AllocateSampleHandle(sb_WaveDriver, &g_6b7d80) == -1) {
				goto fail;
			}
		}
		msx_InitSample((int) g_6b7d80);
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
		size = sbs_GetFileSize(path);
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
		if (sbs_GetAudioFormat(name) == 1) {
			found = ".wav";
		} else {
			found = ".mp3";
		}
		result = msx_SetSampleData((int) g_6b7d80, found, g_6b7d84, size);
		if (result == 0) {
			msx_StartSample((int) g_6b7d80);
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
		size = sbs_CountSetEntries(name);
		index = fcn_0064d3f8() % size;
		data = sbs_FindSet(name);
		if (data == 0) {
			goto fail;
		}
		found = *(char**) ((char*) data + 0x38);
		while (found != 0 && index-- != 0) {
			found = *(char**) (found + 0x104);
		}
		if (found != 0) {
			result = sbs_PlaySample(found, ext);
		}
		return result;
	}
}
