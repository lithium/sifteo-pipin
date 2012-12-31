#include "pipin.h"


PipinCube::PipinCube()
{
}

void PipinCube::init(CubeID id)
{
    vbuf.attach(id);

    vbuf.initMode(BG0_SPR_BG1);
}

void PipinCube::loading(unsigned progress)
{
    vbuf.initMode(BG0_ROM);
    vbuf.bg0rom.hBargraph(vec(0,16), progress, BG0ROMDrawable::BLUE);
}

void PipinCube::paint()
{
    vbuf.bg0.image(vec(0,0), Background);
}

void PipinCube::tick(TimeDelta step)
{

}
