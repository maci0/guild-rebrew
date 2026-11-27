#include <string.h>

void* __cdecl m_alloc(unsigned int size, const char* tag);
void __cdecl m_FreeTracked(void*);
void __cdecl shp_WriteFrameOffsets(const void* src, char* hdr);
int __cdecl d2_CompareRgb(char*, char*);
void __cdecl d2_WritePixelRgb(char*, char, char, char);

/* Lay out one wide-glyph text block: scan the three-byte glyph cells for the
/* Lay out one wide-glyph text block: scan the three-byte glyph cells for the
   used bounds, blank the two row markers, pack each glyph run into the block
   and return a right-sized copy. */
/* ADDRESS: GOLDTL 0x00477590 */
unsigned int* __cdecl shp_GrabBit24(int originX, int originY, unsigned int width,
                                   unsigned int height, int pixels, char a5, int rowStride)
{
    unsigned int minx;
    unsigned int maxy;
    unsigned int maxx;
    unsigned int miny;
    char ref[3];
    int stride;
    int total;
    int tbl[864];
    unsigned int* buf;
    unsigned int* out;
    unsigned int* rowhdr;
    unsigned int* run;
    int x;
    int y;
    int r;
    int runs;

    minx = width;
    ref[0] = 0;
    ref[1] = 0;
    ref[2] = 0;
    maxx = 0;
    maxy = 0;
    miny = height;
    total = 0;
    buf = (unsigned int*) m_alloc((width * 0xc + 4) * height + 0x32, (char*) 0x67d984);
    for (y = 0; y < (int) height; y++) {
        stride = pixels + ((originY + y) * rowStride + originX) * 3;
        for (x = 0; x < (int) width; x++, stride += 3) {
            if (d2_CompareRgb((char*) stride, (char*) 0x100f1a0) && x > (int) (unsigned short) maxx) {
                maxx = x;
            }
            if (d2_CompareRgb((char*) stride, (char*) 0x100f1a0) && x < (int) (unsigned short) minx) {
                minx = x;
            }
            if (d2_CompareRgb((char*) stride, (char*) 0x100f1a0) && y > (int) (unsigned short) maxy) {
                maxy = y;
            }
            if (d2_CompareRgb((char*) stride, (char*) 0x100f1a0) && y < (int) (unsigned short) miny) {
                miny = y;
            }
        }
    }
    if ((unsigned short) maxx < (unsigned short) minx || (unsigned short) maxy < (unsigned short) miny) {
        maxx = 0;
        minx = 0;
        maxy = 0;
        miny = 0;
    }
    *(unsigned short*) ((char*) buf + 4) = (unsigned short) minx;
    *(unsigned short*) ((char*) buf + 0xe) = (unsigned short) minx;
    *(unsigned short*) ((char*) buf + 6) = (unsigned short) (maxx + 1);
    *(unsigned short*) ((char*) buf + 8) = (unsigned short) miny;
    *(unsigned short*) ((char*) buf + 0xa) = (unsigned short) (maxy + 1);
    *(unsigned short*) ((char*) buf + 0x10) = (unsigned short) miny;
    *(unsigned short*) ((char*) buf + 0x12) = (unsigned short) (maxx + 1);
    *(unsigned short*) ((char*) buf + 0x14) = (unsigned short) (maxy + 1);
    if (d2_CompareRgb((char*) 0x67d95c, ref)) {
        for (y = 0; y < (int) height; y++) {
            for (x = 0; x < (int) width; x++) {
                stride = pixels + (((originY + y) * rowStride + originX) + x) * 3;
                if (d2_CompareRgb((char*) 0x67d960, ref) && !d2_CompareRgb((char*) stride, (char*) 0x67d960)) {
                    d2_WritePixelRgb((char*) stride, *(char*) 0x100f1a0, *(char*) 0x100f1a1, *(char*) 0x100f1a2);
                    minx = x;
                    miny = y;
                }
                if (!d2_CompareRgb((char*) stride, (char*) 0x67d95c)) {
                    d2_WritePixelRgb((char*) stride, *(char*) 0x100f1a0, *(char*) 0x100f1a1, *(char*) 0x100f1a2);
                    maxx = x;
                    maxy = y;
                }
            }
        }
    }
    *(unsigned short*) ((char*) buf + 0x16) = (unsigned short) minx;
    *(unsigned short*) ((char*) buf + 0x18) = (unsigned short) miny;
    *(unsigned short*) ((char*) buf + 0x1a) = (unsigned short) maxx;
    *(unsigned short*) ((char*) buf + 0x1c) = (unsigned short) maxy;
    buf[0] = 0x32;
    for (r = 0; r < (int) *(unsigned short*) ((char*) buf + 0xa); r++) {
        rowhdr = (unsigned int*) ((char*) buf + buf[0]);
        buf[0] += 4;
        tbl[r] = (char*) rowhdr - (char*) buf;
        runs = 0;
        for (x = 0; x < (int) *(unsigned short*) ((char*) buf + 6); x++) {
            run = (unsigned int*) ((char*) buf + buf[0]);
            run[0] = 0;
            run[1] = 0;
            for (; x < (int) *(unsigned short*) ((char*) buf + 6); x++) {
                if (d2_CompareRgb((char*) (pixels + (x + (originY + r) * rowStride + originX) * 3), (char*) 0x100f1a0)) {
                    break;
                }
                run[0]++;
            }
            run[0] *= 3;
            for (; run[1] + x < *(unsigned short*) ((char*) buf + 6); run[1]++) {
                if (!d2_CompareRgb((char*) (pixels + (run[1] + (originY + r) * rowStride + x + originX) * 3), (char*) 0x100f1a0)) {
                    break;
                }
            }
            memcpy(run + 2, (char*) (pixels + ((originY + r) * rowStride + originX + x) * 3), run[1] * 3);
            *(unsigned int*) ((char*) buf + 0x2e) += run[1];
            x += run[1] - 1;
            buf[0] += run[1] * 3 + 8;
            total++;
            runs++;
        }
        *rowhdr = runs;
    }
    *(unsigned int*) ((char*) buf + 0x2a) = buf[0];
    buf[0] += *(unsigned short*) ((char*) buf + 0xa) * 4;
    shp_WriteFrameOffsets(tbl, (char*) buf);
    *((char*) buf + 0xd) = a5;
    *(int*) ((char*) buf + 0x26) = total;
    out = (unsigned int*) m_alloc(buf[0], (char*) 0x67d970);
    memcpy(out, buf, buf[0]);
    m_FreeTracked(buf);
    return out;
}
