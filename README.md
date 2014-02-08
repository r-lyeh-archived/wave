wave
====

- Wave is a lightweight 3D sound wrapper for OpenAL. Written in C++11.
- All dependencies are included (both OpenAL and STB_Vorbis by Sean Barrett).
- Cross-platform. Builds on Windows/Linux. Compiles on g++/msvc.
- Tiny. One header and one source file.
- OGG decoding support.
- MIT licensed.

sample
------

```c++
#include <iostream>
#include "wave.hpp"

int main( int argc, char **argv ) {
    if( argc != 2 )
        return std::cerr << "Usage: " << argv[0] << " file.ogg" << std::endl, -1;

    // enumerate audio devices
    for( auto &it : wave::enumerate() )
        std::cout << "Audio device: " << it << std::endl;

    // create as many audio contexts as you want. use music one for now.
    wave::device sfx, music, voice, ambient, video, ui, &env = music;

    // our context uses system device #0
    if( !env.init(0) )
        return std::cerr << "Cant open audio device." << std::endl, -1;
    else
        std::cout << "Using audio device: " << env.devname << std::endl;

    // create sound and speaker on this context
    unsigned snd_idx = env.insert_sound( wave::sound() );
    unsigned spk_idx = env.insert_speaker( wave::speaker() );

    if( snd_idx == ~0 )
        return std::cerr << "Invalid sound index" << std::endl, -1;
    if( spk_idx == ~0 )
        return std::cerr << "Invalid speaker index" << std::endl, -1;

    wave::speaker &spk = env.speakers[ spk_idx ];
    wave::sound &snd = env.sounds[ snd_idx ];

    // load audio into buffer sound
    if( !snd.load( argv[1] ) )
        return std::cerr << "Cant open file: " << argv[1] << std::endl, -1;
    else
        std::cout << "Playing '" << snd.path << "' " << snd.seconds << " secs." << std::endl;

    // play sound until finish
    spk.play( snd );
    for( ;spk.is_playing(); );

    return 0;
}
```

note
----

[OGG sample from wikipedia](http://upload.wikimedia.org/wikipedia/en/4/45/ACDC_-_Back_In_Black-sample.ogg)
