/* ADDRESS: GOLD 0x0045f160 */
char __cdecl fcn_0045f160(char* terrain, float* point, int* outx, int* outz, float* height)
{
    int x;
    int z;
    int width;
    int next_height;
    int right_height;
    unsigned char* cells;
    float base;
    float z_fraction;

    if (terrain == 0)
        return 0;
    x = (int) ((point[0] - *(float*) terrain) / *(float*) (terrain + 0x10));
    z = (int) ((point[2] - *(float*) (terrain + 8)) / *(float*) (terrain + 0x18));
    if (x < 0)
        return 0;
    width = *(int*) (terrain + 0x20);
    if (x >= width || z < 0 || z >= width || outx == 0 || outz == 0)
        return 0;
    *outx = x;
    *outz = z;
    if (height != 0) {
        width = *(int*) (terrain + 0x20);
        cells = *(unsigned char**) (terrain + 0x28);
        base = (cells[z * width + x] + 0.5f) * *(float*) (terrain + 0x14) + *(float*) (terrain + 4);
        z_fraction = (point[2] - (z * *(float*) (terrain + 0x18) + *(float*) (terrain + 8))) / *(float*) (terrain + 0x18);
        next_height = cells[((z + 1) & (width - 1)) * width + x];
        right_height = cells[z * width + ((x + 1) & (width - 1))];
        *height = z_fraction * ((next_height + 0.5f) * *(float*) (terrain + 0x14) + *(float*) (terrain + 4) - base)
            + ((point[0] - (x * *(float*) (terrain + 0x10) + *(float*) terrain)) / *(float*) (terrain + 0x10))
            * ((right_height + 0.5f) * *(float*) (terrain + 0x14) + *(float*) (terrain + 4) - base) + base;
    }
    return 1;
}
