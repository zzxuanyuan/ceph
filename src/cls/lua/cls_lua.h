#ifndef CEPH_CLS_LUA_H
#define CEPH_CLS_LUA_H

#include <lua.hpp>
#include "include/types.h"

#define LOG_LEVEL_DEFAULT 10

extern "C" {
  int luaopen_cmsgpack(lua_State *L);
}

int luaopen_bufferlist(lua_State *L);

bufferlist *clslua_checkbufferlist(lua_State *L, int pos = 1);
bufferlist *clslua_pushbufferlist(lua_State *L, bufferlist *set);

struct clslua_cmd {
  string script;
  string funcname;
  bufferlist input;

  void encode(bufferlist& bl) const {
    ENCODE_START(1, 1, bl);
    ::encode(script, bl);
    ::encode(funcname, bl);
    ::encode(input, bl);
    ENCODE_FINISH(bl);
  }

  void decode(bufferlist::iterator& bl) {
    DECODE_START(1, bl);
    ::decode(script, bl);
    ::decode(funcname, bl);
    ::decode(input, bl);
    DECODE_FINISH(bl);
  }
};
WRITE_CLASS_ENCODER(clslua_cmd);

struct clslua_reply {
  vector<string> log;
  bufferlist output;

  void encode(bufferlist& bl) const {
    ENCODE_START(1, 1, bl);
    ::encode(log, bl);
    ::encode(output, bl);
    ENCODE_FINISH(bl);
  }

  void decode(bufferlist::iterator& bl) {
    DECODE_START(1, bl);
    ::decode(log, bl);
    ::decode(output, bl);
    DECODE_FINISH(bl);
  }
};
WRITE_CLASS_ENCODER(clslua_reply);

#endif
