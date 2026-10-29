#include <stdio.h>
#include <string.h>

typedef struct Bank Bank;

typedef struct {
	int id;
	char name[0x3c];
} Sample;

/* SIZE 0x144 */
struct Bank {
	char title[0x32];
	char file[0x100];
	int count;
	Sample* samples;
	Bank* next;
	int loaded;
};

/* on-disk header of a sample bank file, SIZE 0x144 */
typedef struct {
	char title[0x32];
	char file[0x100];
	short pad132;
	int count;
	char pad138[8];
	int total164;
} BankHeader;

extern int g_6b7d7c;
extern int g_6b7d74;
extern Bank* g_6b7d78;
extern char g_6b7d88[];
extern char g_14cb980[];
extern char g_14cbae0[];

Bank* __cdecl fcn_00422730(const char* name);
char* __cdecl fcn_00422aa0(void);
void __cdecl sb_LoadEntry(Bank* bank, Sample* sample);
void* __cdecl m_alloc(int size, char* tag);
void __cdecl m_FreeTracked(void* p);

/* ADDRESS: GOLDTL 0x00422dc0 */
Bank* __cdecl sb_LoadSampleBank(char* name, int init)
{
	Bank* bank;
	Bank* tail;
	FILE* fp;
	BankHeader hdr;
	char path[0x100];
	char msg[0x200];
	int i;
	int size;

	if (g_6b7d7c == 0) {
		return (Bank*) g_14cb980;
	}
	bank = fcn_00422730(name);
	if (bank != 0) {
		bank->loaded++;
		return bank;
	}
	strcpy(path, g_6b7d88);
	strcat(path, name);
	fp = fopen(path, "rb");
	if (fp == 0) {
		sprintf(msg, "sb_LoadSampleBank: Samplebank %s konnte nicht geladen werden!", path);
		return bank;
	}
	if (fread(&hdr, 0x144, 1, fp) != 1) {
		fclose(fp);
		return bank;
	}
	size = hdr.count * 0x40 + 0x144;
	bank = m_alloc(size, "sb_LoadSampleBank");
	if (bank == 0) {
		fclose(fp);
		return bank;
	}
	strncpy(bank->title, hdr.title, 0x32);
	strncpy(bank->file, path, 0x100);
	bank->count = hdr.total164;
	bank->next = 0;
	bank->samples = (Sample*) (bank + 1);
	if (fread(bank->samples, 0x40, bank->count, fp) != bank->count) {
		m_FreeTracked(bank);
		bank = 0;
		fclose(fp);
		return bank;
	}
	tail = (Bank*) fcn_00422aa0();
	if (tail != 0) {
		tail->next = bank;
	} else {
		g_6b7d78 = bank;
	}
	g_6b7d74 = g_6b7d74 + hdr.count * 0x40 + 0x144;
	sprintf(g_14cbae0, "Samplebank %s loaded. MemUsed is now %d bytes.", name, g_6b7d74);
	bank->loaded = 1;
	if (init == 0) {
		fclose(fp);
		return bank;
	}
	for (i = 0; i < hdr.count; i++) {
		sb_LoadEntry(bank, &bank->samples[i]);
	}
	fclose(fp);
	return bank;
}
