int __cdecl ls_ReadVfsDataChecked(void* outBuffer, int elementSize, int elementCount, void* streamCtx);
extern volatile int gm_GameTicks;
/* Load the eight 0x170-byte render-object records from a save stream.  Older
   versions (before 0x10055) carry no rotation block, so the two rotation
   floats are forced to 1.0f. */
/* ADDRESS: GOLDTL 0x004ef770 */
unsigned int __cdecl ls_LoadRenderSlots(void* file, int version)
{
    int i;

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
    if (!ls_ReadVfsDataChecked((void*) 0x9a921c, 4, 1, file)) {
        return 0;
    }
    for (i = 0; i < 8; i++) {
        char* p = (char*) 0x7731b8 + i * 0x170;
        char* q = (char*) 0x772ff8 + i * 0x38;

        if (!ls_ReadVfsDataChecked((void*) p, 4, 1, file)) {
            return 0;
        }
        if (!ls_ReadVfsDataChecked((void*) (p + 8), 4, 1, file)) {
            return 0;
        }
        if (version >= 0x10055) {
            if (!ls_ReadVfsDataChecked((void*) (p + 0xc), 4, 1, file)) {
                return 0;
            }
            if (!ls_ReadVfsDataChecked((void*) (p + 0x10), 4, 1, file)) {
                return 0;
            }
        } else {
            *(unsigned int*) (p + 0xc) = 0x3f800000;
            *(unsigned int*) (p + 0x10) = 0x3f800000;
        }
        if (!ls_ReadVfsDataChecked((void*) (p + 0x14), 4, 1, file)) {
            return 0;
        }
        if (!ls_ReadVfsDataChecked((void*) (p + 0x18), 0x10, 1, file)) {
            return 0;
        }
        if (!ls_ReadVfsDataChecked((void*) (p + 0x28), 0x10, 1, file)) {
            return 0;
        }
        if (!ls_ReadVfsDataChecked((void*) (p + 0x38), 0x10, 1, file)) {
            return 0;
        }
        if (!ls_ReadVfsDataChecked((void*) (p + 0x58), 0x10, 1, file)) {
            return 0;
        }
        if (!ls_ReadVfsDataChecked((void*) (p + 0x68), 4, 1, file)) {
            return 0;
        }
        if (!ls_ReadVfsDataChecked((void*) (p + 0x6c), 4, 1, file)) {
            return 0;
        }
        if (!ls_ReadVfsDataChecked((void*) (p + 0x70), 4, 1, file)) {
            return 0;
        }
        if (!ls_ReadVfsDataChecked((void*) (p + 0x74), 4, 1, file)) {
            return 0;
        }
        if (!ls_ReadVfsDataChecked((void*) (p + 0x7c), 4, 1, file)) {
            return 0;
        }
        *(unsigned int*) (p + 0x78) = (unsigned int) gm_GameTicks;
        if (!ls_ReadVfsDataChecked((void*) (p + 0x80), 0x10, 1, file)) {
            return 0;
        }
        if (!ls_ReadVfsDataChecked((void*) (p + 0x90), 0x10, 1, file)) {
            return 0;
        }
        if (!ls_ReadVfsDataChecked((void*) (p + 0xa0), 0x10, 1, file)) {
            return 0;
        }
        if (!ls_ReadVfsDataChecked((void*) (p + 0xc0), 0x10, 1, file)) {
            return 0;
        }
        if (!ls_ReadVfsDataChecked((void*) (p + 0xd0), 4, 1, file)) {
            return 0;
        }
        if (!ls_ReadVfsDataChecked((void*) (p + 0xd4), 4, 1, file)) {
            return 0;
        }
        if (!ls_ReadVfsDataChecked((void*) (p + 0xd8), 4, 1, file)) {
            return 0;
        }
        if (!ls_ReadVfsDataChecked((void*) (p + 0xdc), 4, 1, file)) {
            return 0;
        }
        if (!ls_ReadVfsDataChecked((void*) (p + 0xe4), 4, 1, file)) {
            return 0;
        }
        *(unsigned int*) (p + 0xe0) = (unsigned int) gm_GameTicks;
        if (!ls_ReadVfsDataChecked((void*) (p + 0xe8), 0x10, 1, file)) {
            return 0;
        }
        if (!ls_ReadVfsDataChecked((void*) (p + 0xf8), 0x10, 1, file)) {
            return 0;
        }
        if (!ls_ReadVfsDataChecked((void*) (p + 0x108), 0x10, 1, file)) {
            return 0;
        }
        if (!ls_ReadVfsDataChecked((void*) (p + 0x128), 0x10, 1, file)) {
            return 0;
        }
        if (!ls_ReadVfsDataChecked((void*) (p + 0x138), 4, 1, file)) {
            return 0;
        }
        if (!ls_ReadVfsDataChecked((void*) (p + 0x13c), 4, 1, file)) {
            return 0;
        }
        if (!ls_ReadVfsDataChecked((void*) (p + 0x140), 4, 1, file)) {
            return 0;
        }
        if (!ls_ReadVfsDataChecked((void*) (p + 0x144), 4, 1, file)) {
            return 0;
        }
        if (!ls_ReadVfsDataChecked((void*) (p + 0x14c), 4, 1, file)) {
            return 0;
        }
        *(unsigned int*) (p + 0x148) = (unsigned int) gm_GameTicks;
        if (!ls_ReadVfsDataChecked((void*) (p + 0x150), 0xc, 1, file)) {
            return 0;
        }
        *(int*) (p + 0x16c) = (int) q;
        *(unsigned int*) (p + 0x168) = 0x4ef250;
    }
    return 1;
}
