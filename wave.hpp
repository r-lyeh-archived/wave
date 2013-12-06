// Simple OpenAL wrapper. Based on code by Emil Persson.
// - rlyeh, 2013. MIT licensed.
// @todo: doppler: alDopplerFactor, alSpeedOfSound
// @todo: playonce( int src );

#pragma once

#include <AL/al.h>
#include <AL/alc.h>

#include <string>
#include <vector>
#include <map>

namespace wave {

struct sound
{
    ALenum format;
    ALuint buffer;
//    bool ok;

    short *samples;
    int sampleRate;
    int size;

    bool load( const std::string &pathfile );
    bool load( const std::string &type, const void *data, size_t size );
    void unload();

    double seconds() const;
};

struct speaker
{
    ALuint source;
    ALuint buffer;
//    bool ok;

    bool create();
    bool bind( int buffer );
    void unbind();
    void purge();

    void loop( const bool on );
    void gain( const float gain );
    void pitch( const float pitch );
    void position( const float *position3, bool relative = false );
    void velocity( const float *velocity3 );
    void direction( const float *direction3 );

    void attenuation( const float rollOff, const float refDistance );
//    void distance( const float mind, const float maxd );

    void play();
    void stop();
    void pause();
    bool is_playing() const;
};

struct listener
{
    void gain( const float gain );
    void position( const float *position3 );
    void velocity( const float *velocity3 );
    void direction( const float *direction3 );
};

struct device
{
    ALCdevice *dev;
    ALCcontext *ctx;
//    bool ok;

    wave::listener listener;
    std::vector<sound> sounds;
    std::vector<speaker> speakers;

    std::string devname;
    bool has_efx;

    bool init( int devnum );
    void quit();

    void enable();
    void disable();

    void clear();
    void reset();

     int insert_sound( sound &source );
    void erase_sound( int sound );

     int insert_speaker( speaker &source );
    void erase_speaker( int source );

     int playonce( const std::string &pathfile, void (*efxpre)(int) = 0, void (*efxpost)(int) = 0 );
};

std::vector< std::string > enumerate();

}

#if 0

// proposal

audio.devices[N].context[M].listener
                            channel[O].sounds[P]
                                      .sources[Q]

// proposal

struct listener
{
    int id;

    float gain;
    float position[3];
    float velocity[3];
    float orientation[3];
};

void init( listener &ltn );
void update( listener &ltn );

struct speaker
{
    int id;
    int source;

    float gain;
    float position[3];
    float velocity[3];
    float orientation[3];

    //cone

    float reference_distance;   // the distance under which the volume for the source would normally drop by half (before being influenced by rolloff factor or AL_MAX_DISTANCE)
    float rolloff;              // the rolloff rate for the source

    bool  playing;
    bool  paused;
    bool  looping;
    bool  relative_position;    // determines if the positions are relative to the listener
};

 int load( const std::string &resource );
void unload( int source );
void init( speaker &spk );
void submit( speaker &spk );

struct context
{
    context();

    int id;
    int device;

    listener ltn;
    std::vector< speaker > ui;
    std::vector< speaker > sfx;
    std::vector< speaker > bgm;
    std::vector< speaker > amb;
    std::vector< speaker > vox;
};

void update( context &ctx );

#endif
