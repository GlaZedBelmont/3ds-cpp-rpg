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

class Stats {
    public:
        int ATK = 0;
        int DEF = 0;
        int MAG = 0;
        int SPE = 0;
    // ATK
        void setAtk(int atk) {
            ATK = atk;
        }
/*        int getAtk() {
            return ATK;
        } */
    // DEF
        void setDef(int def) {
            DEF = def;
        }
/*        int getDef() {
            return DEF;
        }*/
    // MAG
        void setMag(int mag) {
            MAG = mag;
        }
/*        int getMag() {
            return MAG;
        }*/
    // SPE
        void setSpe(int spe) {
            SPE = spe;
        }
/*        int getSpe() {
            return SPE;
        }*/
};
class Player {
    std::string NAME;
    int HP = 0;

    public:
    // NAME
        void setName(std::string name) {
            this->NAME = name;
        };
        std::string getName() {
            return this->NAME;
        };
    // HP
        void setHP(int hp) {
            this->HP = hp;
        };
        int getHP() {
            return this->HP;
        };
        Stats stats;
};

struct tileData {
    int type;
    float posX;
    float posY;
    float width;
    float height;
//    tileData specificTileData;
};

std::vector<tileData> getMap() {
    std::string data;
    tileData testTile;
    std::vector<tileData> tiles{};
    
    std::ifstream mapFile("romfs:/test.map");

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

    std::vector<tileData> map{};
    map = getMap();
  //  vector<tileData>::iterator tile;
    //int index = 0;

//    bool DEBUG = false;

    std::vector<Player> Players(4);
    std::vector<Player>::iterator Player_Cur;
    Player_Cur = Players.begin();

    

    while(aptMainLoop()) {

        hidScanInput();
        u32 kDown = hidKeysDown();

        if (kDown & KEY_START) {
            break;
        }
        if (kDown & KEY_X) {
            Player_Cur->setName(Keyboard_GetText("Enter name"));
            
        }
        if (kDown & KEY_Y) {
            Player_Cur->setHP(atoi(Keyboard_GetNumber("Enter HP")));
            
        }
        if (kDown & KEY_UP && Player_Cur != Players.end()-1) {
            Player_Cur++;
        }
        if (kDown & KEY_DOWN && Player_Cur != Players.begin()) {
            Player_Cur--;
        }

        
        std::vector<tileData>::iterator tile;

        C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
        C2D_TargetClear(top, C2D_Color32(128, 128, 128, 255));
        C2D_SceneBegin(top);

       // index = 0;
        for (tile = map.begin(); tile != map.end(); ++tile) {
            C2D_DrawImageAt(getTile(tile->type), tile->posX, tile->posY, 0.0f, NULL, 1.0f, 1.0f);
        }
        //consoleClear();
        printf("\x1b[2;1HCPU: %6.2f%%\x1b[K", C3D_GetProcessingTime()*6.0f);
		printf("\x1b[3;1HGPU: %6.2f%%\x1b[K", C3D_GetDrawingTime()*6.0f);
		printf("\x1b[4;1HCmdBuf: %6.2f%%\x1b[K", C3D_GetCmdBufUsage()*100.0f);
        printf("\x1b[6;1HPlayer_Cur: %i\x1b[K", Player_Cur - Players.begin());
        printf("\x1b[7;1HName: %s\x1b[K", Player_Cur->getName().c_str());
        printf("\x1b[8;1HHP: %i\x1b[K", Player_Cur->getHP());
        printf("\x1b[9;1HATK: %i\x1b[K", Player_Cur->stats.ATK);
        printf("\x1b[10;1HDEF: %i\x1b[K", Player_Cur->stats.DEF);
        printf("\x1b[11;1HMAG: %i\x1b[K", Player_Cur->stats.MAG);
        printf("\x1b[12;1HSPE: %i\x1b[K", Player_Cur->stats.SPE);
        //printf("Player_Cur: %i\nName: %s\nHP: %i\nATK: %i\nDEF: %i\nMAG: %i\nSPE: %i\n\n", Player_Cur - Players.begin(), Player_Cur->getName().c_str(), Player_Cur->getHP(), Player_Cur->stats.ATK, Player_Cur->stats.DEF, Player_Cur->stats.MAG, Player_Cur->stats.SPE);
        printf("\x1b[14;1HPress X to set name\nPress Y to set HP\x1b[K");
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
