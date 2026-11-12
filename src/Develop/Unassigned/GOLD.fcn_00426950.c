#include <stdio.h>
#include <string.h>
char* __cdecl fcn_00422730(char*);
char* __cdecl fcn_00422aa0(void);
void* __cdecl m_alloc(unsigned int, char*);
void __cdecl m_FreeTracked(void*);
void __cdecl fcn_00426660(char*, char*);
/* DATA TODO: 0x633194..0x6331a8, bank state in .data; 0x14607c0 default bank and 0x1460920 log buffer, .data virtual tail. */
/* ADDRESS: GOLD 0x00426950 */
char* __cdecl fcn_00426950(char* name, int load)
{
    char path[0x100];
    char header[0x144];
    char error[0x200];
    char *bank, *tail;
    FILE* file;
    int i, count;
    char c;
    if (!*(int*) 0x63319c) return (char*) 0x14607c0;
    bank = fcn_00422730(name);
    if (bank) {
        ++*(int*) (bank + 0x140);
        return bank;
    }
    i = 0;
    do {
        c = ((char*) 0x6331a8)[i];
        path[i++] = c;
    } while (c);
    strcat(path, name);
    file = fopen(path, "rb");
    if (!file) {
        sprintf(error, "sb_LoadSampleBank: Samplebank %s konnte nicht geladen werden!", path);
        return 0;
    }
    bank = 0;
    if (fread(header, 0x144, 1, file) == 1) {
        count = *(int*) (header + 0x134);
        bank = m_alloc(count * 0x40 + 0x144, "sb_LoadSampleBank");
        if (bank) {
            strncpy(bank, header, 0x32);
            strncpy(bank + 0x32, path, 0x100);
            *(int*) (bank + 0x134) = count;
            *(int*) (bank + 0x13c) = 0;
            *(char**) (bank + 0x138) = bank + 0x144;
            if (fread(bank + 0x144, 0x40, *(unsigned int*) (bank + 0x134), file) != *(unsigned int*) (bank + 0x134)) {
                m_FreeTracked(bank);
                bank = 0;
            } else {
                tail = fcn_00422aa0();
                if (tail) *(char**) (tail + 0x13c) = bank;
                else *(char**) 0x633198 = bank;
                *(int*) 0x633194 += 0x144 + count * 0x40;
                sprintf((char*) 0x1460920, "Samplebank %s loaded. MemUsed is now %d bytes.", name, *(int*) 0x633194);
                *(int*) (bank + 0x140) = 1;
                if (load) {
                    for (i = 0; i < count; ++i)
                        fcn_00426660(bank, *(char**) (bank + 0x138) + i * 0x40);
                }
            }
        }
    }
    fclose(file);
    return bank;
}
