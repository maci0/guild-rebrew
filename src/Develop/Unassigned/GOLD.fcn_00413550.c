void __cdecl fcn_00453270(void*);

/* ADDRESS: GOLD 0x00413550 */
void __cdecl fcn_00413550(char* obj, char r, char g, char b)
{
    char* mesh;
    char** faces;
    int i;
    int j;

    if (obj == 0)
        return;
    mesh = *(char**) (obj + 0x1cc);
    if (mesh == 0)
        return;
    if (r == 0 && g == 0 && b == 0) {
        obj[0x212] &= 0xfd;
        fcn_00453270(obj);
        obj[0x210] |= 4;
        return;
    }
    faces = *(char***) (mesh + 4);
    for (i = 0; i < *(int*) (mesh + 0xc); i++) {
        for (j = 0; j < 3; j++) {
            faces[j][0x46] = r;
            faces[j][0x45] = g;
            faces[j][0x44] = b;
        }
        faces = (char**) ((char*) faces + 0x28);
        mesh = *(char**) (obj + 0x1cc);
    }
    obj[0x212] |= 2;
    obj[0x210] |= 4;
}
