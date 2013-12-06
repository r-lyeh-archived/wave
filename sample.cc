#include <iostream>
#include "wave.hpp"

int main( int argc, char **argv ) {
    using namespace wave;

    if( argc != 2 )
        return std::cerr << "Usage: " << argv[0] << " file.ogg" << std::endl, -1;

    // enumerate audio devices
    for( auto &it : enumerate() )
        std::cout << "Audio device: " << it << std::endl;

    // create as many audio contexts as you want
    device sfx, music, voice, ambient, video, ui;

    // sfx context uses system device #0
    if( !sfx.init(0) )
        return std::cerr << "Cant open audio device." << std::endl, -1;

    // print device name
    std::cout << "Using audio device: " << sfx.devname << std::endl;

    // @todo: purge @playonce
    int source = sfx.playonce( argv[1] );

    // check source validity and wait for source to finish
    while( source >= 0 && sfx.speakers[ source ].is_playing() )
    {}
}
