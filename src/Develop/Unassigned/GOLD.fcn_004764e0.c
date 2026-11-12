void __cdecl fcn_00476210(int, int, int, int, int);

/* ADDRESS: GOLD 0x004764e0 */
void __cdecl fcn_004764e0(int x, int y, int x1, int y1, int a4, int a5, int a6)
{
    int dx;
    int dy;
    int sx;
    int sy;
    int error;
    int straight;
    int diagonal;
    int t;

    if (y == y1) {
        if (x > x1) { t = x; x = x1; x1 = t; }
        while (x < x1)
            fcn_00476210(x++, y, a4, a5, a6);
        return;
    }
    if (x == x1) {
        if (y > y1) { t = y; y = y1; y1 = t; }
        while (y < y1)
            fcn_00476210(x, y++, a4, a5, a6);
        return;
    }
    if (x < x1) { dx = x1 - x; sx = 1; }
    else { dx = x - x1; sx = -1; }
    if (y < y1) { dy = y1 - y; sy = 1; }
    else { dy = y - y1; sy = -1; }
    fcn_00476210(x, y, a4, a5, a6);
    if (dx > dy) {
        error = 2 * dy - dx;
        straight = 2 * dy;
        diagonal = 2 * (dy - dx);
        do {
            x += sx;
            if (error >= 0) { y += sy; error += diagonal; }
            else error += straight;
            fcn_00476210(x, y, a4, a5, a6);
        } while (x != x1);
    } else {
        error = 2 * dx - dy;
        straight = 2 * dx;
        diagonal = 2 * (dx - dy);
        do {
            y += sy;
            if (error >= 0) { x += sx; error += diagonal; }
            else error += straight;
            fcn_00476210(x, y, a4, a5, a6);
        } while (y != y1);
    }
}
