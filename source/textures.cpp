#include "textures.hpp"
#include <stdio.h>
#include <3ds.h>
#include <citro3d.h>
#include <citro2d.h>
#include <unistd.h>

#include "tiles.h"

static C2D_SpriteSheet tiles;

C2D_Image one, two, three, four, five, six;

C2D_Image temp;

void texload(){
    tiles = C2D_SpriteSheetLoad("romfs:/gfx/tiles.t3x");

    one = C2D_SpriteSheetGetImage(tiles, tiles_one_idx);
    two = C2D_SpriteSheetGetImage(tiles, tiles_two_idx);
    three = C2D_SpriteSheetGetImage(tiles, tiles_three_idx);
    four = C2D_SpriteSheetGetImage(tiles, tiles_four_idx);
    five = C2D_SpriteSheetGetImage(tiles, tiles_five_idx);
    six = C2D_SpriteSheetGetImage(tiles, tiles_six_idx);
}


C2D_Image getTile(int type) {
    switch(type) {
        case 1:
        return one;

        case 2:
        return two;

        case 3:
        return three;

        case 4:
        return four;

        case 5:
        return five;

        case 6:
        return six;

        default:
        return one;
    }
}
void Textures_Free() {
    C2D_SpriteSheetFree(tiles);
}
