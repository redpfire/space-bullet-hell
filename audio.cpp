
#include <mpg123.h>
#include <string>
#include <string.h>
#include <ao/ao.h>

#include "sound.hpp"

#define BITS 8

using namespace std;

static mpg123_handle *handle;
static unsigned char *buffer;
static size_t buffer_size;
static int driver;
static bool song_reset = false;

void reset_song()
{
    song_reset = true;
}

void init_sound()
{
    ao_initialize();
    driver = ao_default_driver_id();
    mpg123_init();
    int err = 0;
    handle = mpg123_new(NULL, &err);
    buffer_size = mpg123_outblock(handle);
    buffer = (unsigned char*) malloc(buffer_size * sizeof(unsigned char));
}

void play_song(const char *path)
{
    song_reset = false;
    int h = mpg123_open(handle, path);
    int channels,encoding;
    long rate;
    mpg123_getformat(handle, &rate, &channels, &encoding);

    ao_sample_format format;
    format.bits = mpg123_encsize(encoding) * BITS;
    format.rate = rate;
    format.channels = channels;
    format.byte_format = AO_FMT_NATIVE;
    format.matrix = 0;
    ao_device *dev = ao_open_live(driver, &format, NULL);
    size_t done;
    while(mpg123_read(handle, buffer, buffer_size, &done) == MPG123_OK && !song_reset)
        ao_play(dev, (char*)buffer, done);

    free(buffer);
    ao_close(dev);
}

void sound_cleanup()
{
    mpg123_close(handle);
    mpg123_delete(handle);
    mpg123_exit();
    ao_shutdown();
}


