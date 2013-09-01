#include <lua.hpp>
#include "audio/wrap_music.h"
#include "audio/wrap_sound.h"
#include "audio/wrap_soundbuffer.h"

void registerAudioModule(lua_State * l)
{
    register_MusicEnums(l);
    register_SoundEnums(l);

    register_sfMusic(l);
    register_sfSoundBuffer(l);
    register_sfSound(l);
}

