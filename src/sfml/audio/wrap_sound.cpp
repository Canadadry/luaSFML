#include "wrap_sound.h"


#include "../system/wrap_time.h"
#include "../audio/wrap_soundbuffer.h"

#include "../../bindingHelper/marco.hpp"
#include "../../bindingHelper/lua_template.hpp"
#include "../../bindingHelper/enum.hpp"


void register_SoundEnums(lua_State * l)
{
    add_enum_to_lua(l,"sfSoundStatus",
		    "Playing"        , sf::Sound::Status::Playing,
		    "Paused"         , sf::Sound::Status::Paused,
		    "Stopped"        , sf::Sound::Status::Stopped,
		    nullptr);

}



#define TYPE_TO_BIND sf::Sound
#define NAME_TO_BIND sfSound

IMPLEMENT_LUA_CLASS(sfSound,sf::Sound)

#define FUNCTION_TO_BIND \
    X1(setBuffer        , METHOD   , NO_RETURN , RET_NONE             , setBuffer     , sf::SoundBuffer , IS_POINTER )\
    X0(play             , METHOD   ,NO_RETURN  , RET_NONE             , play )\
    X0(pause            , METHOD   ,NO_RETURN  , RET_NONE             , pause)\
    X0(stop             , METHOD   ,NO_RETURN  , RET_NONE             , stop )\
    X0(getStatus        , METHOD   ,HAS_RETURN , RET_TYPE(int)        , getStatus )\
    X0(getVolume        , METHOD   ,HAS_RETURN , RET_TYPE(float)      , getVolume   )\
    X1(setVolume        , METHOD   , NO_RETURN , RET_NONE             , setVolume   , float , NO_POINTER )\
    X0(getLoop          , METHOD   ,HAS_RETURN , RET_TYPE(bool)       , getLoop   )\
    X1(setLoop          , METHOD   , NO_RETURN , RET_NONE             , setLoop     , bool  , NO_POINTER )\
    X0(getPlayingOffset , METHOD   ,HAS_RETURN , RET_TYPE(sf::Time)   , getPlayingOffset   )\
    X1(setPlayingOffset , METHOD   , NO_RETURN , RET_NONE             , setPlayingOffset   , sf::Time , IS_POINTER )\


#define __GO_FOR_IMPLEMENTATION__
#include "../../bindingHelper/macro2.hpp"

FUNCTION_TO_BIND

#undef __GO_FOR_IMPLEMENTATION__
#include "../../bindingHelper/macro2.hpp"

luaL_Reg sfSound_regs[] =
{
    LUA_DEFAULT_CLASS_FUNC(sfSound)
    FUNCTION_TO_BIND
    { NULL, NULL }
};

LUA_REGISTER_CLASS(sfSound)
