#include "app.h"
#include "defs.h"
#include "entity.h"
#include "string_utils.h"

#if _WIN32
#include <Windows.h>
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
                   _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
  App app;

  Entity player(100, 100, app, PLAYER_TEXTURE);

  while (app.ShouldKeepRunning()) {
    app.PrepareScene();

    app.HandleInput();

    player.DrawTexture();

    app.PresentScene();

    SDL_Delay(16);
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
  app.Init();
  return 0;
}
#endif
