#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>

#include <3ds.h>
#include <citro2d.h>
#include <citro3d.h>

#include "textures.hpp"

#include "keyboard.hpp"


using namespace std;

class Player {
    string NAME;
    int HP=0;

    public:
    // NAME
        void setName(string name);
        string getName();
    // HP
        void setHP(int hp);
        int getHP();
};

// NAME
void Player::setName(string name) {
   NAME = name;
}
string Player::getName() {
    return NAME;
}

// HP
void Player::setHP(int hp) {
    HP = hp;
}
int Player::getHP() {
    return HP;
}

struct tileData {
    int type;
    float posX;
    float posY;
    float width;
    float height;
//    tileData specificTileData;
};

vector<tileData> getMap() {
    string data;
    tileData testTile;
    vector<tileData> tiles{};
    
    ifstream mapFile("romfs:/test.map");

   // cout << "The map file has been open\n" << endl;

    while(getline(mapFile, data, '\n')) {
        sscanf(data.c_str(), "%d %f %f %f %f", &testTile.type, &testTile.posX, &testTile.posY, &testTile.width, &testTile.height);
        tiles.emplace_back(testTile);
    }
    mapFile.close();
    return tiles;
}

int main(int argc, char **argv) {

    gfxInitDefault();
    gfxSetDoubleBuffering(GFX_TOP, false);
    gfxSetDoubleBuffering(GFX_BOTTOM, true);
    romfsInit();
    aptInit();
    PrintConsole bottomScreen;
    
    consoleInit(GFX_BOTTOM, &bottomScreen);
    consoleSelect(&bottomScreen);

    C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
    C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
    
    C2D_Prepare();
    C3D_RenderTarget *top, *bottom;
    top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
    bottom = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);

    texload();

    vector<tileData> map{};
    map = getMap();
  //  vector<tileData>::iterator tile;
    int index = 0;

//    bool DEBUG = false;

    Player player;

    

    while(aptMainLoop()) {

        hidScanInput();
        u32 kDown = hidKeysDown();

        if (kDown & KEY_START) {
            break;
        }
        if (kDown & KEY_X) {
            player.setName(Keyboard_GetText("Enter name"));
            
        }
        if (kDown & KEY_Y) {
            player.setHP(atoi(Keyboard_GetNumber()));
            
        }

        
        vector<tileData>::iterator tile;

        C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
        C2D_TargetClear(top, C2D_Color32(128, 128, 128, 255));
        C2D_SceneBegin(top);

        index = 0;
        for (tile = map.begin(); tile != map.end(); ++tile, ++index) {
            C2D_DrawImageAt(getTile(tile->type), tile->posX, tile->posY, 0.0f, NULL, 1.0f, 1.0f);
        }
        consoleClear();
        printf("\x1b[1;0HName: %s\nHP: %i\nCPU: %6.2f%%\nGPU: %6.2f%%\nCmdBuf: %6.2f%%\n", player.getName().c_str(), player.getHP(), C3D_GetProcessingTime()*6.0f, C3D_GetDrawingTime()*6.0f, C3D_GetCmdBufUsage()*100.0f);
        C3D_FrameEnd(0);


        gfxFlushBuffers();
        gfxSwapBuffers();
        gspWaitForVBlank();
    }
    Textures_Free();
    C2D_Fini();
    C3D_Fini();
    aptExit();
    romfsExit(); 
    gfxExit();
    return 0;
}
