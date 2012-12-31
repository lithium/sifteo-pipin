#include "pipin.h"


PipinGame::PipinGame() : running(true)
{
    loader.init();
    config.append(MainSlot, GameAssets);
}

void PipinGame::title()
{
    const float titleTime = 4.0f;

    for (CubeID cid : CubeSet::connected()) 
    {
        cubes[cid].vbuf.initMode(BG0);
        cubes[cid].vbuf.attach(cid);
    }

    Random r;
    unsigned frame = 0;
    unsigned t_frame = 0;
    SystemTime titleDeadline = SystemTime::now() + titleTime;

    bool wait_elapsed = false;
    bool touched = false;
    while (!touched) {

        if (SystemTime::now() < titleDeadline) 
            wait_elapsed = true;

        switch (frame) {
        case 0:
            t_frame = 1;
            break;
        case 15:
            t_frame = 2;
            break;
        case 17:
            t_frame = 3;
            break;
        case 19:
            t_frame = 1;
            break;
        case 23:
            t_frame = 2;
            break;
        case 25:
            t_frame = 3;
            break;
        case 27:
            t_frame = 4;
            break;
        case 29:
            t_frame = 0;
            break;
        case 36:
            t_frame = 4;
            break;
        case 38:
            t_frame = 0;
            break;
        case 80:
            t_frame = 2;
            break;
        case 84:
            t_frame = 1;
            break;
        }

        for (CubeID cid : CubeSet::connected()) 
        {
            if (cid.isTouching()) {
                touched = true;
                break;
            }
            cubes[cid].vbuf.bg0.image(vec(0,0), Title, t_frame);
        }

        frame = (frame+1) % 100;

        // Frame rate division
        for (unsigned f = 0; !touched && f < 3; f++)
            System::paint();
    }
}

void PipinGame::init()
{
    cubes_new = CubeSet::connected();

    Events::cubeConnect.set(&PipinGame::onCubeConnect, this);
    Events::cubeDisconnect.set(&PipinGame::onCubeDisconnect, this);
    // Events::neighborAdd.set(&PipinGame::onNeighborAdd, this);
    // Events::neighborRemove.set(&PipinGame::onNeighborRemove, this);
    Events::gameMenu.set(&PipinGame::onRestart, this, "Restart");
}

void PipinGame::cleanup()
{
    AudioTracker::stop();

    Events::cubeConnect.unset();
    Events::cubeDisconnect.unset();
    Events::neighborAdd.unset();
    Events::neighborRemove.unset();
    Events::gameMenu.unset();
 
}

void PipinGame::paint()
{
    for (CubeID cid : cubes_active) {
        cubes[cid].paint();
    }
}

void PipinGame::tick(TimeDelta step)
{
    for (CubeID cid : cubes_active) {
        cubes[cid].tick(step);
    }
}

void PipinGame::run()
{
    AudioTracker::play(GameMusic);

    TimeStep ts;
    running = true;
    while (running) {

        if (!cubes_new.empty()) {
            AudioTracker::pause();
            loader.start(config);
            while (!loader.isComplete()) {
                for (CubeID cid : cubes_new) {
                    cubes[cid].loading(loader.cubeProgress(cid, 128));
                }
                System::paint();
            }
            loader.finish();
            for (CubeID cid : cubes_new) {
                cubes[cid].init(cid);
                cubes_active.mark(cid);
            }
            AudioTracker::resume();
            cubes_new.clear(); 
        }

        ts.next();
        tick(ts.delta());
        paint();
        System::paint();
    }

    AudioTracker::stop();
}



void PipinGame::onCubeConnect(unsigned cid)
{
    cubes_new.mark(cid);
    cubes[cid].loading(0);
 
}

void PipinGame::onCubeDisconnect(unsigned cid)
{
    cubes_active.clear(cid);
    cubes_new.clear(cid);
}

void PipinGame::onRestart()
{
    running = false;
}


