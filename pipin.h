#ifndef PIPIN_H
#define PIPIN_H 

#include <sifteo.h>
#include "assets.gen.h"
using namespace Sifteo;



class PipinCube {
public:
    VideoBuffer vbuf;

    PipinCube();

    void init(CubeID id);
    void loading(unsigned progress);
    void paint();
    void tick(TimeDelta step);
};


class PipinGame {
public:
    AssetLoader loader;
    AssetConfiguration<1> config;


    bool running;
    CubeSet cubes_new, cubes_active;

    PipinCube cubes[CUBE_ALLOCATION];

    PipinGame();

    void title();
    void init();
    void cleanup();
    void run();

    void paint();
    void tick(TimeDelta step);


    void onCubeConnect(unsigned cid);
    void onCubeDisconnect(unsigned cid);
    void onRestart();
    void onTouch(unsigned cid);


};

static AssetSlot MainSlot = AssetSlot::allocate().bootstrap(BootAssets);


#endif