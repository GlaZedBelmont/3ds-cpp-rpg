#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>

#include <3ds.h>
#include <citro2d.h>
#include <citro3d.h>

#include "textures.hpp"


using namespace std;

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
    gfxSetDoubleBuffering(GFX_BOTTOM, false);
    romfsInit();
    aptInit();
    
    consoleInit(GFX_BOTTOM, NULL);

    C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
    C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
    
    C2D_Prepare();
    C3D_RenderTarget *top, *bottom;
    top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
    bottom = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);

    texload();

    vector<tileData> map{};
  //  vector<tileData>::iterator tile;
    int index = 0;

    bool DEBUG = false;

    

    while(aptMainLoop()) {
        C3D_FrameRate(60);
        C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
        C2D_TargetClear(top, C2D_Color32(128, 128, 128, 255));
        C2D_SceneBegin(top);

		hidScanInput();
		u32 kDown = hidKeysDown();
		if (kDown & KEY_START) {
			break;
		}
        map = getMap();
        vector<tileData>::iterator tile;
        

        consoleClear();
        if (DEBUG) {
            cout << "Tiles in map: " << map.size() << endl;
            cout << "Expected size: " << sizeof(std::vector<tileData>) + (sizeof(tileData) * map.size()) << endl << endl;
        }

        index = 0;
        for (tile = map.begin(); tile != map.end(); ++tile, ++index) {

            C2D_DrawImageAt(getTile(tile->type), tile->posX, tile->posY, 0.0f, NULL, 1.0f, 1.0f);
        
            // Printing values
            if (DEBUG) {
                cout << "PRINTING TILE N." << index << endl;
                cout << "Type: " << tile->type << endl;
                cout << "PosX: " << tile->posX<< endl;
                cout << "PosY: " << tile->posY << endl;
                cout << "Width: " << tile->width << endl;
                cout << "Height: " << tile->height << endl;
                cout << endl;
            }
        }
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
