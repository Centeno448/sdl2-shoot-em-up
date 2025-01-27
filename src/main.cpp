#include "app.h"
#include "entities/entity.h"
#include "log.h"

#if _WIN32
#include <Windows.h>
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
                   _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
  App app;

  while (app.ShouldKeepRunning()) {
    app.Run();
  }

  if (App::unrecoverable_) {
    return -1;
  }

  return 0;
}
#else
#ifdef __cplusplus
extern "C"
#endif

    int
    main(int argc, char *argv[]) {
  App app;

  while (app.ShouldKeepRunning()) {
    app.Run();
  }

  if (App::unrecoverable_) {
    return -1;
  }

  return 0;
}
#endif
