extern char g_631090[];
void __cdecl fcn_00401230(int, char*);
void __cdecl fcn_00401320(int, unsigned int);
int __cdecl fcn_00401430(int, int, int, int);
void __cdecl fcn_004011f0(int, unsigned char);
void __cdecl fcn_004012e0(int, int*);
void __cdecl fcn_004012f0(int, int*);

/* ADDRESS: GOLD 0x0044a770 */
void __cdecl fcn_0044a770(int stream, char* model)
{
    char* name;
    char* row;
    char* object;
    int index;
    int offset;
    int count;

    name = model + 0x19e4;
    fcn_00401230(stream, name);
    if (*name) {
        count = *(int*) model;
        fcn_00401320(stream, count);
        count = *(int*) model;
        fcn_00401430(stream, count, count, *(int*) (model + 0x10));
        count = *(int*) model;
        fcn_00401430(stream, count * 4, count, *(int*) (model + 0x20));
        fcn_004011f0(stream, *(int*) (model + 0x18) != 0);
        if (*(int*) (model + 0x18)) {
            fcn_00401320(stream, *(unsigned char*) (model + 0x1c6d));
            if (0 < *(unsigned char*) (model + 0x1c6d)) {
                count = *(int*) model;
                fcn_00401430(stream, count, count, *(int*) (model + 0x18));
            }
            index = 0;
            while (index < *(unsigned char*) (model + 0x1c6d)) {
                offset = index * 0x158;
                row = *(char**) (model + 0x19e0) + offset;
                object = *(char**) row;
                if (object) {
                    fcn_00401230(stream, object);
                    fcn_004011f0(stream, 0);
                    row = *(char**) (model + 0x19e0) + offset;
                    object = *(char**) row;
                    fcn_004011f0(stream, object[0x72] & 0xf);
                    row = *(char**) (model + 0x19e0) + offset;
                    object = *(char**) row;
                    fcn_004011f0(stream, object[0x68] & 1);
                } else {
                    fcn_00401230(stream, g_631090);
                    fcn_004011f0(stream, 0);
                    fcn_004011f0(stream, 0);
                    fcn_004011f0(stream, 0);
                }
                row = *(char**) (model + 0x19e0) + offset;
                fcn_004011f0(stream, row[8]);
                row = *(char**) (model + 0x19e0) + offset;
                fcn_004011f0(stream, row[9]);
                row = *(char**) (model + 0x19e0) + offset;
                fcn_004011f0(stream, row[0xa] & 1);
                row = *(char**) (model + 0x19e0) + offset;
                fcn_004011f0(stream, ((unsigned char) row[0xa] >> 1) & 1);
                row = *(char**) (model + 0x19e0) + offset;
                fcn_00401320(stream, *(unsigned int*) (row + 0x14));
                row = *(char**) (model + 0x19e0) + offset;
                fcn_00401320(stream, *(unsigned int*) (row + 0xc));
                row = *(char**) (model + 0x19e0) + offset;
                fcn_00401320(stream, *(unsigned int*) (row + 0x10));
                row = *(char**) (model + 0x19e0) + offset;
                fcn_004012e0(stream, (int*) (row + 0x18));
                row = *(char**) (model + 0x19e0) + offset;
                fcn_004012e0(stream, (int*) (row + 0x28));
                row = *(char**) (model + 0x19e0) + offset;
                fcn_00401320(stream, *(unsigned int*) (row + 0x154));
                index++;
            }
        }
    } else {
        fcn_004011f0(stream, 0);
    }
    fcn_00401230(stream, model + 0x1a24);
    if (model[0x1a24]) {
        count = *(int*) model;
        fcn_00401430(stream, count, count, *(int*) (model + 0x14));
    }
    name = model + 0x1a64;
    count = 8;
    do {
        fcn_00401230(stream, name);
        name += 0x40;
    } while (--count);
    fcn_00401320(stream, *(unsigned int*) (model + 0xa0));
    fcn_00401320(stream, *(unsigned int*) (model + 0xc4));
    fcn_004012f0(stream, (int*) (model + 0x90));
}
