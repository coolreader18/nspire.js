#include "jslib.h"
#include "duktape/duktape.h"
#include <libndls.h>

#define push_function(ctx, func, nargs, name) \
  duk_push_c_function(ctx, func, nargs),      \
      duk_put_global_string(ctx, name)

static duk_ret_t js_msgbox(duk_context *ctx)
{
  int n = duk_get_top(ctx);

  const char *msg, *title;

  msg =
      n >= 1 ? duk_require_string(ctx, 0) : "";
  title =
      n >= 2 ? duk_require_string(ctx, 1) : "";

  show_msgbox(title, msg);

  return 0;
}

static duk_ret_t js_userinput(duk_context *ctx)
{
  int n = duk_get_top(ctx);

  const char *msg, *default_val, *title;

  msg =
      n >= 1 ? duk_require_string(ctx, 0) : "";
  default_val =
      n >= 2 ? duk_require_string(ctx, 1) : "";
  title =
      n >= 3 ? duk_require_string(ctx, 2) : "";

  const char *value;
  int l;
  l = show_msg_user_input(title, msg, default_val, &value);

  if (l != -1)
  {
    duk_push_lstring(ctx, value, l);
    free(value);
  }
  else
    duk_push_string(ctx, "");

  return 1;
}

void init_lib(duk_context *ctx)
{
  push_function(ctx, js_msgbox, DUK_VARARGS, "msgbox");
  push_function(ctx, js_msgbox, DUK_VARARGS, "alert");
  push_function(ctx, js_userinput, DUK_VARARGS, "userInput");
  push_function(ctx, js_userinput, DUK_VARARGS, "prompt");
}