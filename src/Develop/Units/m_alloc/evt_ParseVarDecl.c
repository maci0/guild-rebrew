#include <string.h>

extern char* evt_CurrentScript;
extern void __cdecl evt_ReadToken(int stream, void *out);
extern int __cdecl evt_FindSymbol(int a0, char *text);
extern int __cdecl evt_AllocVariable(int a0, unsigned int a1, int a2);
extern void __cdecl evt_LogScriptError(int a0, int a1, char *text);
extern int __cdecl evt_ParseFunctionArgs(int a0, void *rec);
extern int __cdecl fcn_0064e790(int a0, int a1);

/* ADDRESS: GOLDTL 0x00427830 */
unsigned int __cdecl evt_ParseVarDecl(int script, unsigned int kind)
{
    char name[32];
    struct {
        int status;
        int data[24];
    } tok;
    int v2;
    int v3;
    unsigned int v4;
    unsigned int v5;
    char *nameDest;
    char *nameCursor;
    char copiedChar;
    char *q; int record;

    evt_ReadToken(*(unsigned int *)(evt_CurrentScript + 0x118), &tok.status);
    if (tok.status)
        return 1;
    v2 = 0;
    do
    {
        copiedChar = ((char *) tok.data)[v2];
        name[v2] = copiedChar;
        v2++;
    } while (copiedChar);
    evt_ReadToken(*(unsigned int *)(evt_CurrentScript + 0x118), &tok.status);
    v2 = script;
    if (tok.status != 1)
        return 1;
    if (tok.data[0] == 10)
    {
        v3 = evt_FindSymbol(script, name);
        if (v3)
            return 1;
        q = (char *)(evt_AllocVariable(v2, kind, 1) + 4);
        strcpy(q, name);
        return 1;
    }
    if (tok.data[0] == 2)
    {
        v3 = evt_FindSymbol(script, name);
        if (!v3)
        {
            record = evt_AllocVariable(v2, kind, 1);
            q = (char *)(record + 4); strcpy(q, name);
        } else {
            __asm { int 3 }
        }
        evt_ReadToken(*(unsigned int *)(evt_CurrentScript + 0x118), &tok.status);
        if (tok.status != 5)
            return 1;
        **(int **)(record + 0x2c) = tok.data[0];
        return 1;
    }
    if (tok.data[0] == 0xc)
    {
        v4 = *(unsigned int *)(evt_CurrentScript + 0x118);
        v3 = evt_ParseFunctionArgs(script, tok.data);
        if (!v3)
            return 0;
        v5 = fcn_0064e790(v4, 0x7b);
        *(unsigned int *)(*(int *)(v2 + 0x10c) - 300 + *(int *)(v2 + 0x110) * 0x14c) = v5;
        nameCursor = name;
        nameDest = (char *)(*(int *)(v2 + 0x10c) - 0x14c + *(int *)(v2 + 0x110) * 0x14c);
        do
        {
            copiedChar = *nameCursor;
            nameCursor++;
            *nameDest = copiedChar;
            nameDest++;
        } while (copiedChar);
        *(unsigned int *)(evt_CurrentScript + 0x118) = v4;
        return 1;
    }
    if (tok.data[0] != 0x1b)
        return 1;
    evt_ReadToken(*(unsigned int *)(evt_CurrentScript + 0x118), &tok.status);
    v2 = script;
    if (tok.status == 5)
        v3 = tok.data[0];
    else
    {
        v3 = 1;
        evt_LogScriptError(script, *(unsigned int *)(script + 0x118), (char *)0x6794a0);
    }
    if (!evt_FindSymbol(v2, name))
    {
        v3 = evt_AllocVariable(v2, kind, v3);
        q = (char *)(v3 + 4);
        strcpy(q, name);
    }
    evt_ReadToken(*(unsigned int *)(evt_CurrentScript + 0x118), &tok.status);
    if (tok.data[0] != 0x1c)
        evt_LogScriptError(v2, *(unsigned int *)(v2 + 0x118), (char *)0x679490);
    evt_ReadToken(*(unsigned int *)(evt_CurrentScript + 0x118), &tok.status);
    if (tok.data[0] == 10)
        return 1;
    evt_LogScriptError(v2, *(unsigned int *)(v2 + 0x118), (char *)0x679480);
    return 1;
}
