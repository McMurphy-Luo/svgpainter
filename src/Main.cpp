#include "./Config.h"
#include <Windows.h>
#include <tchar.h>
#include "./MainWindow.h"

int APIENTRY _tWinMain(HINSTANCE this_instance, HINSTANCE previous_instance, LPTSTR cmd_line, int cmd_show) {
  MainWindow* the_main_window = new MainWindow("svgpainter");
  the_main_window->Show(cmd_show);
  MSG message;
  while (GetMessage(&message, nullptr, 0, 0)) {
    TranslateMessage(&message);
    DispatchMessage(&message);
  }
  delete the_main_window;
#ifdef _CRTDBG_MAP_ALLOC
  _CrtDumpMemoryLeaks();
#endif
  return 0;
}