#include "duktape/duktape.h"
#include "jslib.h"
#include "files.h"
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <libndls.h>

static void handle_fatal(void *udata, const char *msg)
{
  (void)udata;

  show_msgbox("Fatal Error", msg);
}

int main(int argc, char **argv)
{
  if (argc == 1)
  {
    cfg_register_fileext("js", "nspire_js");
    show_msgbox("Info", "File extension has been registered.\n"
                        "Please execute a .js file, executing this file will"
                        "do nothing.");
    return 0;
  }

  duk_context *ctx = duk_create_heap(NULL, NULL, NULL, NULL, handle_fatal);

  init_lib(ctx);

  file_read file = read_file(argv[1]);

  duk_push_lstring(ctx, file.buf, file.size);
  duk_push_string(ctx, argv[1]);
  if (duk_pcompile(ctx, 0) != 0)
  {
    show_msgbox("compile failed", duk_safe_to_string(ctx, -1));
  }
  else
  {
    duk_pcall(ctx, 0);
    duk_pop(ctx);
  }

  duk_destroy_heap(ctx);

  return 0;
}