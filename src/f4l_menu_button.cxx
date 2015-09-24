#include "fltk4lua.hxx"
#include "f4l_menu.hxx"
#include "f4l_widget.hxx"
#include "f4l_enums.hxx"
#include <FL/Fl_Menu_Button.H>

namespace {

#define TYPE_LIST( _ ) \
  _( "NOPOPUP", 0 ) \
  _( "POPUP1", Fl_Menu_Button::POPUP1 ) \
  _( "POPUP2", Fl_Menu_Button::POPUP2 ) \
  _( "POPUP12", Fl_Menu_Button::POPUP12 ) \
  _( "POPUP3", Fl_Menu_Button::POPUP3 ) \
  _( "POPUP13", Fl_Menu_Button::POPUP13 ) \
  _( "POPUP23", Fl_Menu_Button::POPUP23 ) \
  _( "POPUP123", Fl_Menu_Button::POPUP123 )

  F4L_GEN_TYPE_ENUM( TYPE_LIST, popup )


  inline Fl_Menu_Button* check_menu_button( lua_State* L, int idx ) {
    void* p = moon_checkobject( L, idx, F4L_MENU_BUTTON_NAME );
    return static_cast< Fl_Menu_Button* >( p );
  }

  int menu_button_index_( lua_State* L, Fl_Menu_Button* mb,
                          char const* key, size_t n ) {
    using namespace std;
    if( n == 4 && F4L_MEMCMP( key, "type", 4 ) == 0 ) {
      f4l_push_type_popup( L, mb->type() );
      return 1;
    }
    return 0;
  }

  int menu_button_newindex_( lua_State* L, Fl_Menu_Button* mb,
                             char const* key, size_t n ) {
    using namespace std;
    if( n == 4 && F4L_MEMCMP( key, "type", 4 ) == 0 ) {
      mb->type( f4l_check_type_popup( L, 3 ) );
      return 1;
    }
    return 0;
  }

  int menu_button_index( lua_State* L ) {
    Fl_Menu_Button* mb = check_menu_button( L, 1 );
    size_t n = 0;
    char const* key = luaL_checklstring( L, 2, &n );
    F4L_TRY {
      if( !menu_button_index_( L, mb, key, n ) &&
          !f4l_menu_index_( L, mb, key, n ) &&
          !f4l_widget_index_( L, mb, key, n ) &&
          !f4l_bad_property( L, F4L_MENU_BUTTON_NAME, key ) )
        lua_pushnil( L );
    } F4L_CATCH( L );
    return 1;
  }

  int menu_button_newindex( lua_State* L ) {
    Fl_Menu_Button* mb = check_menu_button( L, 1 );
    size_t n = 0;
    char const* key = luaL_checklstring( L, 2, &n );
    F4L_TRY {
      (void)(menu_button_newindex_( L, mb, key, n ) ||
             f4l_menu_newindex_( L, mb, key, n ) ||
             f4l_widget_newindex_( L, mb, key, n ) ||
             f4l_bad_property( L, F4L_MENU_BUTTON_NAME, key ));
    } F4L_CATCH( L );
    return 0;
  }

  int new_menu_button( lua_State* L ) {
    F4L_TRY {
      f4l_new_widget< Fl_Menu_Button >( L, F4L_MENU_BUTTON_NAME );
    } F4L_CATCH( L );
    return 1;
  }

} // anonymous namespace


MOON_LOCAL void f4l_menu_button_setup( lua_State* L ) {
  luaL_Reg const methods[] = {
    F4L_WIDGET_METHODS,
    F4L_MENU_METHODS,
    { "__index", menu_button_index },
    { "__newindex", menu_button_newindex },
    { NULL, NULL }
  };
  moon_defobject( L, F4L_MENU_BUTTON_NAME, 0, methods, 0 );
  moon_defcast( L, F4L_MENU_BUTTON_NAME, F4L_MENU_NAME,
                f4l_cast< Fl_Menu_Button, Fl_Menu_ > );
  moon_defcast( L, F4L_MENU_BUTTON_NAME, F4L_WIDGET_NAME,
                f4l_cast< Fl_Menu_Button, Fl_Widget > );
  f4l_new_class_table( L, "Menu_Button", new_menu_button );
}
