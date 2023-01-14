#include "5.0/redismodule.h"
#include "rmutil/alloc.h"
#include "rmutil/strings.h"
#include "rmutil/util.h"

/* EXAMPLE.PARSE [var]
*/
int ParseCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {

  // we must have at least 4 args
  if (argc < 2) {
    return RedisModule_WrongArity(ctx);
  }

  // init auto memory for created strings
  RedisModule_AutoMemory(ctx);
  
  double incrby = 0;
  if (RMUtil_ParseArgs(argv, argc, 1, "d", &incrby) == REDISMODULE_OK) {
    RedisModule_ReplyWithDouble(ctx, incrby);
    return REDISMODULE_OK;
  }

  // something is fishy...
  RedisModule_ReplyWithError(ctx, "Invalid arguments");

  return REDISMODULE_ERR;
}

int RedisModule_OnLoad(RedisModuleCtx *ctx) {

  // Register the module itself
  if (RedisModule_Init(ctx, "example", 1, REDISMODULE_APIVER_1) ==
      REDISMODULE_ERR) {
    return REDISMODULE_ERR;
  }

  // register example.parse - the default registration syntax
  if (RedisModule_CreateCommand(ctx, "example.parse", ParseCommand, "readonly",
                                1, 1, 1) == REDISMODULE_ERR) {
    return REDISMODULE_ERR;
  }

  return REDISMODULE_OK;
}