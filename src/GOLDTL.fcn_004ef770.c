int __cdecl ls_ReadVfsDataChecked(void* outBuffer, int elementSize, int elementCount, void* streamCtx);

/* ADDRESS: GOLDTL 0x004ef770 */
/* Load the eight 0x170-byte render-object records from a save stream.  Older
   versions (before 0x10055) carry no rotation block, so the two rotation
   floats are forced to 1.0f. */
unsigned int __cdecl fcn_004ef770(void* file, int version)
{
    unsigned int v2;
    unsigned int v3;

    if (!ls_ReadVfsDataChecked((void*) 0x772fe8, 4, 1, file)) {
        return 0;
    }
    if (!ls_ReadVfsDataChecked((void*) 0x772fec, 2, 1, file)) {
        return 0;
    }
    if (!ls_ReadVfsDataChecked((void*) 0x772fee, 4, 1, file)) {
        return 0;
    }
    if (!ls_ReadVfsDataChecked((void*) 0x772ff2, 4, 1, file)) {
        return 0;
    }
    if (!ls_ReadVfsDataChecked((void*) 0x9a9200, 4, 1, file)) {
        return 0;
    }
    if (!ls_ReadVfsDataChecked((void*) 0x9a9204, 4, 1, file)) {
        return 0;
    }
    if (!ls_ReadVfsDataChecked((void*) 0x9a9208, 0xc, 1, file)) {
        return 0;
    }
    if (!ls_ReadVfsDataChecked((void*) 0x9a9214, 4, 1, file)) {
        return 0;
    }
    if (!ls_ReadVfsDataChecked((void*) 0x9a9218, 4, 1, file)) {
        return 0;
    }
    if (ls_ReadVfsDataChecked((void*) 0x9a921c, 4, 1, file)) {
        v2 = 0x772ff8;
        v3 = 0x7731f0;
        while (ls_ReadVfsDataChecked((void*) (v3 - 0x38), 4, 1, file) &&
               ls_ReadVfsDataChecked((void*) (v3 - 0x30), 4, 1, file)) {
            if (0x10055 <= (unsigned int) version) {
                if (!ls_ReadVfsDataChecked((void*) (v3 - 0x2c), 4, 1, file)) {
                    return 0;
                }
                if (!ls_ReadVfsDataChecked((void*) (v3 - 0x28), 4, 1, file)) {
                    return 0;
                }
            } else {
                *(unsigned int*) (v3 - 0x2c) = 0x3f800000;
                *(unsigned int*) (v3 - 0x28) = 0x3f800000;
            }
            if (!ls_ReadVfsDataChecked((void*) (v3 - 0x24), 4, 1, file)) {
                return 0;
            }
            if (!ls_ReadVfsDataChecked((void*) (v3 - 0x20), 0x10, 1, file)) {
                return 0;
            }
            if (!ls_ReadVfsDataChecked((void*) (v3 - 0x10), 0x10, 1, file)) {
                return 0;
            }
            if (!ls_ReadVfsDataChecked((void*) v3, 0x10, 1, file)) {
                return 0;
            }
            if (!ls_ReadVfsDataChecked((void*) (v3 + 0x20), 0x10, 1, file)) {
                return 0;
            }
            if (!ls_ReadVfsDataChecked((void*) (v3 + 0x30), 4, 1, file)) {
                return 0;
            }
            if (!ls_ReadVfsDataChecked((void*) (v3 + 0x34), 4, 1, file)) {
                return 0;
            }
            if (!ls_ReadVfsDataChecked((void*) (v3 + 0x38), 4, 1, file)) {
                return 0;
            }
            if (!ls_ReadVfsDataChecked((void*) (v3 + 0x3c), 4, 1, file)) {
                return 0;
            }
            if (!ls_ReadVfsDataChecked((void*) (v3 + 0x44), 4, 1, file)) {
                return 0;
            }
            *(unsigned int*) (v3 + 0x40) = *(unsigned int*) 0x6b7fac;
            if (!ls_ReadVfsDataChecked((void*) (v3 + 0x48), 0x10, 1, file)) {
                return 0;
            }
            if (!ls_ReadVfsDataChecked((void*) (v3 + 0x58), 0x10, 1, file)) {
                return 0;
            }
            if (!ls_ReadVfsDataChecked((void*) (v3 + 0x68), 0x10, 1, file)) {
                return 0;
            }
            if (!ls_ReadVfsDataChecked((void*) (v3 + 0x88), 0x10, 1, file)) {
                return 0;
            }
            if (!ls_ReadVfsDataChecked((void*) (v3 + 0x98), 4, 1, file)) {
                return 0;
            }
            if (!ls_ReadVfsDataChecked((void*) (v3 + 0x9c), 4, 1, file)) {
                return 0;
            }
            if (!ls_ReadVfsDataChecked((void*) (v3 + 0xa0), 4, 1, file)) {
                return 0;
            }
            if (!ls_ReadVfsDataChecked((void*) (v3 + 0xa4), 4, 1, file)) {
                return 0;
            }
            if (!ls_ReadVfsDataChecked((void*) (v3 + 0xac), 4, 1, file)) {
                return 0;
            }
            *(unsigned int*) (v3 + 0xa8) = *(unsigned int*) 0x6b7fac;
            if (!ls_ReadVfsDataChecked((void*) (v3 + 0xb0), 0x10, 1, file)) {
                return 0;
            }
            if (!ls_ReadVfsDataChecked((void*) (v3 + 0xc0), 0x10, 1, file)) {
                return 0;
            }
            if (!ls_ReadVfsDataChecked((void*) (v3 + 0xd0), 0x10, 1, file)) {
                return 0;
            }
            if (!ls_ReadVfsDataChecked((void*) (v3 + 0xf0), 0x10, 1, file)) {
                return 0;
            }
            if (!ls_ReadVfsDataChecked((void*) (v3 + 0x100), 4, 1, file)) {
                return 0;
            }
            if (!ls_ReadVfsDataChecked((void*) (v3 + 0x104), 4, 1, file)) {
                return 0;
            }
            if (!ls_ReadVfsDataChecked((void*) (v3 + 0x108), 4, 1, file)) {
                return 0;
            }
            if (!ls_ReadVfsDataChecked((void*) (v3 + 0x10c), 4, 1, file)) {
                return 0;
            }
            if (!ls_ReadVfsDataChecked((void*) (v3 + 0x114), 4, 1, file)) {
                return 0;
            }
            *(unsigned int*) (v3 + 0x110) = *(unsigned int*) 0x6b7fac;
            if (!ls_ReadVfsDataChecked((void*) (v3 + 0x118), 0xc, 1, file)) {
                return 0;
            }
            *(int*) (v3 + 0x134) = (int) v2;
            *(unsigned int*) (v3 + 0x130) = 0x4ef250;
            v3 += 0x170;
            v2 += 0x38;
            if (0x773d70 <= v3) {
                return 1;
            }
        }
    }
    return 0;
}
