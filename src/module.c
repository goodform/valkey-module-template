#include "redismodule.h"

/* EXAMPLE.PARSE [var] */
int ParseCommand(ValkeyModuleCtx *ctx, ValkeyModuleString **argv, int argc) {

  // we must have at least 4 args
  if (argc < 2) {
    return ValkeyModule_WrongArity(ctx);
  }

  // init auto memory for created strings
  ValkeyModule_AutoMemory(ctx);
  
  double incrby = 0;
  ValkeyModule_ReplyWithDouble(ctx, incrby);
  return VALKEYMODULE_OK;
}

int ValkeyModule_OnLoad(ValkeyModuleCtx *ctx) {

  // Register the module itself
  if (ValkeyModule_Init(ctx, "example", 1, VALKEYMODULE_APIVER_1) ==
      VALKEYMODULE_ERR) {
    return VALKEYMODULE_ERR;
  }

  // register example.parse - the default registration syntax
  if (ValkeyModule_CreateCommand(ctx, "example.parse", ParseCommand, "readonly",
                                1, 1, 1) == VALKEYMODULE_ERR) {
    return VALKEYMODULE_ERR;
  }

  return VALKEYMODULE_OK;
}