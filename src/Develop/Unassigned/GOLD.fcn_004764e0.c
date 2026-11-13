void __cdecl fcn_00476210(int, int, int, int, int);

/* ADDRESS: GOLD 0x004764e0 */
void __cdecl fcn_004764e0(int x, int y, int x1, int y1, int a4, int a5, int a6)
{
    int dx, dy;
    int sx, sy;
    int error, straight;
    int diagonal, t;

    if (y == y1) {
        if (x1 < x) { t = x - x1;
            if (t > 0) do { fcn_00476210(x1++, y, a4, a5, a6); } while (--t);
        } else { t = x1 - x;
            if (t > 0) do { fcn_00476210(x++, y, a4, a5, a6); } while (--t);
        }
        return;
    }
    if (x == x1) {
        if (y1 < y) { t = y - y1;
            if (t > 0) do { fcn_00476210(x, y1++, a4, a5, a6); } while (--t);
        } else { t = y1 - y;
            if (t > 0) do { fcn_00476210(x, y++, a4, a5, a6); } while (--t);
        }
        return;
    }
    if (x < x1) { dx = x1 - x; sx = 1; }
    else { dx = x - x1; sx = -1; }
    if (y < y1) { dy = y1 - y; sy = 1; }
    else { dy = y - y1; sy = -1; }
    fcn_00476210(x, y, a4, a5, a6);
    if (dx > dy) {
        diagonal = dy - dx;
        straight = dy + dy;
        diagonal += diagonal; error = straight - dx;
        do {
            x += sx;
            if (error >= 0) { y += sy; error += diagonal; }
            else error += straight;
            fcn_00476210(x, y, a4, a5, a6);
        } while (x != x1);
    } else {
        diagonal = dx - dy;
        straight = dx + dx;
        diagonal += diagonal; error = straight - dy;
        do {
            y += sy;
            if (error >= 0) { x += sx; error += diagonal; }
            else error += straight;
            fcn_00476210(x, y, a4, a5, a6);
        } while (y != y1);
    }
}
