

#include <sifteo.h>
#include "assets.gen.h"
using namespace Sifteo;


#include "pipin.h"


// METADATA

static Metadata M = Metadata()
    .title("Pipin'")
    .package("com.hlidskialf.sifteo.pipin", "0.1")
    .icon(Icon)
    .cubeRange(1, CUBE_ALLOCATION);




void main()
{
    static PipinGame game;
    for (;;) {
        game.title();
        game.init();
        game.run();
        game.cleanup();
    }
}
