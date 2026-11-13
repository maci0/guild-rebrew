void __cdecl fcn_00435740(char* sounds, char* name);
/* Inferred views, also evidenced by Gold0x52f740. */
typedef struct GOLD_REFRESH_PAGE { char unknown00[0x68]; char* name; char unknown6c[0x10]; } GOLD_REFRESH_PAGE;
typedef struct GOLD_REFRESH_PAGES { char unknown00[0xf4]; char sounds[0x1c]; GOLD_REFRESH_PAGE pages[3]; } GOLD_REFRESH_PAGES;

/* ADDRESS: GOLD 0x00411b70 */
int __cdecl fcn_00411b70(char* model)
{
    GOLD_REFRESH_PAGES* pages;
    char* name;
    int i;
    for (i = 0; i < 3; i++) {
        pages = *(GOLD_REFRESH_PAGES**) (model + 0x1ec);
        if (pages != 0) {
            name = pages->pages[i].name;
            if (name != 0) fcn_00435740(pages->sounds, name);
        }
    }
    return 1;
}
