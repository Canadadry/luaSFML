#include "wrap_sgitem.h"
#include "../../sfml/graphics/wrap_render_window.h"

#include <lua.hpp>

#include "../../bindingHelper/marco.hpp"
#include "../../bindingHelper/lua_template.hpp"

#include "../../sfml/system/wrap_vector2f.h"

#define TYPE_TO_BIND SGItem
#define NAME_TO_BIND sfeSGItem



template<>
SGItem* newDefault(lua_State * L)
{
    if(lua_gettop(L) >1)
    {
	return new SGItem(lua_get<SGItem*>(L,1)) ;
    }
    return new SGItem() ;

}

IMPLEMENT_LUA_CLASS(sfeSGItem,SGItem)

#define FUNCTION_TO_BIND \
    X0(parentItem , METHOD   ,HAS_RETURN , RET_CTOR                , parentItem   )\
    X0(width      , METHOD   ,HAS_RETURN , RET_TYPE(       float)  , width   )\
    X0(height     , METHOD   ,HAS_RETURN , RET_TYPE(       float)  , height   )\
    X1(setWidth   , METHOD   , NO_RETURN , RET_NONE                , setWidth         , float        , NO_POINTER )\
    X1(setHeight  , METHOD   , NO_RETURN , RET_NONE                , setHeight        , float        , NO_POINTER )\
    \
    \
    X0(getPosition , METHOD   ,HAS_RETURN , RET_TYPE(sf::Vector2f)  , getPosition   )\
    X0(getRotation , METHOD   ,HAS_RETURN , RET_TYPE(       float)  , getRotation   )\
    X0(getScale    , METHOD   ,HAS_RETURN , RET_TYPE(sf::Vector2f)  , getScale      )\
    X0(getOrigin   , METHOD   ,HAS_RETURN , RET_TYPE(sf::Vector2f)  , getOrigin     )\
    X1(setPosition , METHOD   , NO_RETURN , RET_NONE                , setPosition   , sf::Vector2f , IS_POINTER )\
    X1(setRotation , METHOD   , NO_RETURN , RET_NONE                , setRotation   , float        , NO_POINTER )\
    X1(setScale    , METHOD   , NO_RETURN , RET_NONE                , setScale      , sf::Vector2f , IS_POINTER )\
    X1(setOrigin   , METHOD   , NO_RETURN , RET_NONE                , setOrigin     , sf::Vector2f , IS_POINTER )\
    X1(move        , METHOD   , NO_RETURN , RET_NONE                , move          , sf::Vector2f , IS_POINTER )\
    X1(scale       , METHOD   , NO_RETURN , RET_NONE                , scale         , sf::Vector2f , IS_POINTER )\
    X1(rotate      , METHOD   , NO_RETURN , RET_NONE                , rotate        , float        , NO_POINTER )\


#define __GO_FOR_IMPLEMENTATION__
#include "../../bindingHelper/macro2.hpp"

FUNCTION_TO_BIND

#undef __GO_FOR_IMPLEMENTATION__
#include "../../bindingHelper/macro2.hpp"

luaL_Reg sfeSGItem_regs[] =
{
    LUA_DEFAULT_CLASS_FUNC(sfeSGItem)
    FUNCTION_TO_BIND
    { NULL, NULL }
};

LUA_BEGIN_REGISTER_CLASS(sfeSGItem)
register_drawableType(metaTableName<SGItem>());
LUA_END_REGISTER_CLASS
