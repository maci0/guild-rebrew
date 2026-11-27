extern int g_0063319c;
extern int* g_6b7d78;
extern char g_14cb980[];
#include <stdio.h>
#include <string.h>
char* __cdecl sb_FindBankByPath(char*);
char* __cdecl sb_GetLastBank(void);
void* __cdecl m_alloc(unsigned int, char*);
void __cdecl m_FreeTracked(void*);
void __cdecl sb_LoadEntry(char*, char*);
/* DATA TODO: 0x633194, 0x6331a8, bank state in .data; 0x1460920 log buffer, .data virtual tail. */
/* ADDRESS: GOLD 0x00426950 */
char* __cdecl sb_LoadSampleBankFromFile(char* name, int load)
{
    char error[0x200];
    char path[0x100];
    char *bank, *tail;
    FILE* file;
    int i;
    char c;
    if (!g_0063319c) return g_14cb980;
    bank = sb_FindBankByPath(name);
    if (bank == 0) {
        i = 0;
        do {
            c = ((char*) 0x6331a8)[i];
            path[i++] = c;
        } while (c);
        strcat(path, name);
        file = fopen(path, "rb");
        if (file != 0) {
            char header[0x144];
            if (fread(header, 0x144, 1, file) == 1) {
                bank = m_alloc(*(int*) (header + 0x134) * 0x40 + 0x144, "sb_LoadSampleBank");
                if (bank) {
                    strncpy(bank, header, 0x32);
                    strncpy(bank + 0x32, path, 0x100);
                    *(int*) (bank + 0x134) = *(int*) (header + 0x134);
                    *(int*) (bank + 0x13c) = 0;
                    *(char**) (bank + 0x138) = bank + 0x144;
                    if (fread(bank + 0x144, 0x40, *(unsigned int*) (bank + 0x134), file) != *(unsigned int*) (bank + 0x134)) {
                        m_FreeTracked(bank);
                        bank = 0;
                    } else {
                        tail = sb_GetLastBank();
                        if (tail) *(char**) (tail + 0x13c) = bank;
                        else g_6b7d78 = (int*) bank;
                        *(int*) 0x633194 += 0x144 + *(int*) (header + 0x134) * 0x40;
                        sprintf((char*) 0x1460920, "Samplebank %s loaded. MemUsed is now %d bytes.", name, *(int*) 0x633194);
                        *(int*) (bank + 0x140) = 1;
                        if (load) {
                            for (i = 0; i < *(int*) (header + 0x134); ++i)
                                sb_LoadEntry(bank, *(char**) (bank + 0x138) + i * 0x40);
                        }
                        fclose(file);
                        return bank;
                    }
                }
            }
            fclose(file);
            return bank;
        }
        sprintf(error, "sb_LoadSampleBank: Samplebank %s konnte nicht geladen werden!", path);
    } else {
        ++*(int*) (bank + 0x140);
    }
    return bank;
}
