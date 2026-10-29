#include <math.h>

/* ADDRESS: GOLDTL 0x004be000 */
void __cdecl rd_FillSupermapQuad(char** context, float* points, unsigned char byte_value, int record_value)
{
    float x0;
    float y0;
    float x1;
    float y1;
    float dx0;
    float dy0;
    float dx1;
    float dy1;
    float length0;
    float length1;
    float scale;
    float inner_scale;
    float x;
    float y;
    float dx;
    float dy;
    int count;
    int across;
    int i;
    int j;

    x0 = points[0];
    y0 = points[1];
    dx0 = points[2] - points[0];
    dy0 = points[3] - points[1];
    length0 = dx0 * dx0 + dy0 * dy0;
    x1 = points[6];
    y1 = points[7];
    dx1 = points[4] - points[6];
    dy1 = points[5] - points[7];
    length1 = dx1 * dx1 + dy1 * dy1;
    count = (int) (sqrt(length0 > length1 ? length0 : length1) + 0.9) * 2;
    if (count < 1)
        count = 1;
    scale = 1.0f / count;
    dx0 *= scale;
    dy0 *= scale;
    dx1 *= scale;
    dy1 *= scale;
    for (i = 0; i < count; i++) {
        x = x0;
        y = y0;
        dx = x1 - x0;
        dy = y1 - y0;
        across = (int) (sqrt(dx * dx + dy * dy) + 0.9) * 2;
        if (across < 1)
            across = 1;
        inner_scale = 1.0f / across;
        dx *= inner_scale;
        dy *= inner_scale;
        for (j = 0; j < across; j++) {
            if (byte_value != 0xff)
                (*(unsigned char**) (context[0] + 0x14))[(int) y * *(int*) context[0] + (int) x] = byte_value;
            if (record_value != 0xff)
                *(int*) (*(char**) (context[1] + 0x24) + ((int) y * *(int*) context[0] + (int) x) * 0x1c) = record_value;
            x += dx;
            y += dy;
        }
        x0 += dx0;
        y0 += dy0;
        x1 += dx1;
        y1 += dy1;
    }
}
