/* ADDRESS: GOLD 0x00493a30 */
void __cdecl fcn_00493a30(unsigned char* game)
{
    int state;
    int left;
    int right;
    int i;
    int triples_left;
    int triples_right;

    state = *(int*) (game + 8);
    left = 0;
    right = 0;
    triples_left = 0;
    triples_right = 0;
    if (state == 1) {
        *(int*) (game + 8) = 2;
        return;
    }
    if (state == 2) {
        if (game[0x18] == game[0x19] && game[0x18] == game[0x1a])
            triples_left = game[0x18] + game[0x19] + game[0x1a];
        if (game[0x3c] == game[0x3d] && game[0x3c] == game[0x3e])
            triples_right = game[0x3c] + game[0x3d] + game[0x3e];
        if (triples_left > triples_right) {
            *(int*) (game + 8) = 5;
            return;
        }
        if (triples_right > 0) {
            *(int*) (game + 8) = 6;
            return;
        }
        if (*(int*) (game + 0x28) == 4) {
            *(int*) (game + 8) = 6;
            return;
        }
        *(int*) (game + 8) = 3 + (*(int*) (game + 0x4c) == 4) * 2;
        return;
    }
    for (i = 0; i < game[0x10]; i++)
        left += game[0x18 + i];
    for (i = 0; i < game[0x34]; i++)
        right += game[0x3c + i];
    if (state == 3) {
        if (left > 17 || *(int*) (game + 0x28) == 4)
            *(int*) (game + 8) = 6;
        else if (*(int*) (game + 0x28) == 3 && *(int*) (game + 0x4c) == 3)
            *(int*) (game + 8) = 5 + (left <= right);
        else
            *(int*) (game + 8) = 4;
    } else if (state == 4) {
        if (right > 17 || *(int*) (game + 0x4c) == 4)
            *(int*) (game + 8) = 5;
        else if (*(int*) (game + 0x28) == 3 && *(int*) (game + 0x4c) == 3)
            *(int*) (game + 8) = 5 + (left <= right);
        else
            *(int*) (game + 8) = 3;
    }
}
