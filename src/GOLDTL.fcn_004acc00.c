// FUNCTION: GOLDTL 0x004acc00

#include <string.h>

// SIZE 0x2c
typedef struct Rec {
	int id;
	int x4;
	int x8;
	char name[0x10];
	char text[0x10];
} Rec;

// SIZE 0x10
typedef struct Table {
	int n_first;
	int n_second;
	Rec* first;
	Rec* second;
} Table;

extern int g_6b7fdc;
extern char g_67fbe8[];

int __cdecl fcn_0042ff50(const char* name, const char* mode, int ctx);
unsigned int __cdecl vfs_ReadData(void* buf, int size, int count, int stream);
int __cdecl CloseVfsStream(int stream);
void* __cdecl m_AllocTracked(int size, char* tag);
void __cdecl m_FreeTracked(void* p);

#define HISTORICAL_MAGIC 0x68466153

/* Loads /gamedata/ai/historical.dfn into the two record tables; on any
 * failure both tables are freed and emptied and -1 is returned. */
int __cdecl fcn_004acc00(Table* t)
{
	int magic;
	int f;
	int i;

	magic = HISTORICAL_MAGIC;
	f = fcn_0042ff50("/gamedata/ai/historical.dfn", "rb", g_6b7fdc);
	if (f == 0) {
		goto fail;
	}
	if (vfs_ReadData(&magic, 4, 1, f) <= 0 || magic != HISTORICAL_MAGIC) {
		goto fail_close;
	}
	if (vfs_ReadData(&t->n_first, 4, 1, f) <= 0) {
		goto fail_close;
	}
	if (vfs_ReadData(&t->n_second, 4, 1, f) <= 0) {
		goto fail_close;
	}
	if (t->n_first <= 0 || t->n_second <= 0) {
		goto fail_close;
	}
	if (t->second != 0) {
		m_FreeTracked(t->second);
		t->second = 0;
	}
	if (t->first != 0) {
		m_FreeTracked(t->first);
		t->first = 0;
	}
	t->second = (Rec*) m_AllocTracked(t->n_second * sizeof(Rec), g_67fbe8);
	if (t->second == 0) {
		goto fail_close;
	}
	t->first = (Rec*) m_AllocTracked(t->n_first * sizeof(Rec), g_67fbe8);
	if (t->first == 0) {
		goto fail_close;
	}
	memset(t->second, 0, t->n_second * sizeof(Rec));
	memset(t->first, 0, t->n_first * sizeof(Rec));
	for (i = 0; i < t->n_first; i++) {
		if (vfs_ReadData(&t->first[i].id, 4, 1, f) <= 0
			|| vfs_ReadData(&t->first[i].x4, 4, 1, f) <= 0
			|| vfs_ReadData(&t->first[i].x8, 4, 1, f) <= 0
			|| vfs_ReadData(t->first[i].name, 0x10, 1, f) <= 0
			|| vfs_ReadData(t->first[i].text, 0x10, 1, f) <= 0) {
			goto fail_close;
		}
	}
	for (i = 0; i < t->n_second; i++) {
		if (vfs_ReadData(&t->second[i].id, 4, 1, f) <= 0
			|| vfs_ReadData(&t->second[i].x4, 4, 1, f) <= 0
			|| vfs_ReadData(&t->second[i].x8, 4, 1, f) <= 0
			|| vfs_ReadData(t->second[i].name, 0x10, 1, f) <= 0
			|| vfs_ReadData(t->second[i].text, 0x10, 1, f) <= 0) {
			goto fail_close;
		}
	}
	CloseVfsStream(f);
	return 0;
fail_close:
	CloseVfsStream(f);
fail:
	if (t->second != 0) {
		m_FreeTracked(t->second);
		t->second = 0;
	}
	if (t->first != 0) {
		m_FreeTracked(t->first);
		t->first = 0;
	}
	t->n_first = 0;
	t->n_second = 0;
	return -1;
}
