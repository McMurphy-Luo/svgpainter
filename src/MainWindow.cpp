#include "./MainWindow.h"

#include <cassert>
#include <tchar.h>
#include <iostream>

using std::wstring;
using std::function;
using std::unordered_map;
using boost::optional;
using boost::signals2::signal;
using boost::signals2::connection;
using tinysvg::DomString;
using tinysvg::Utf8StringToWideString;

namespace
{
  LRESULT CALLBACK WindowProc(HWND window_handler, UINT msg, WPARAM w_param, LPARAM l_param)
  {
    switch (msg) {
    case WM_CREATE:
    {
      CREATESTRUCT* p_create_struct = reinterpret_cast<CREATESTRUCT*>(l_param);
      MainWindow* p_created_wnd = reinterpret_cast<MainWindow*>(p_create_struct->lpCreateParams);
      SetWindowLongPtr(window_handler, GWLP_USERDATA, (LONG_PTR)p_created_wnd);
      return 0;
    }
    case WM_DESTROY:
    {
      PostQuitMessage(0);
      return 0;
    }
    }
    MainWindow* theWindow = reinterpret_cast<MainWindow*>(GetWindowLongPtrW(window_handler, GWLP_USERDATA));
    if (theWindow)
      return theWindow->Trigger(msg, w_param, l_param);
    return DefWindowProc(window_handler, msg, w_param, l_param);
  }

  WNDCLASSEX MainWindowClass(HINSTANCE instance)
  {
    static WNDCLASSEX the_window_class;
    the_window_class.cbSize = sizeof(the_window_class);
    the_window_class.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
    the_window_class.lpfnWndProc = WindowProc;
    the_window_class.cbClsExtra = 0;
    the_window_class.cbWndExtra = 0;
    the_window_class.hInstance = instance;
    the_window_class.hIcon = nullptr;
    the_window_class.hCursor = LoadCursor(nullptr, MAKEINTRESOURCEW(32512));
    the_window_class.hbrBackground = nullptr;
    the_window_class.lpszMenuName = nullptr;
    the_window_class.hIconSm = nullptr;
    return the_window_class;
  }

  ATOM RegisterMainWindow(HINSTANCE module_handle) {
    static bool is_class_registered = false;
    static ATOM register_result;
    if (!is_class_registered) {
      WNDCLASSEX main_window_class = MainWindowClass(module_handle);
      wstring class_name = Utf8StringToWideString(kMainWindowClass);
      main_window_class.lpszClassName = class_name.c_str();
      register_result = RegisterClassEx(&main_window_class);
      assert(register_result);
      is_class_registered = true;
    }
    return register_result;
  }
}

MainWindow::MainWindow(const DomString& window_name)
  : window_handler_(0)
  , last_message_()
{
  wstring window_name_wide_string_version = window_name;
  RegisterMainWindow(GetModuleHandle(NULL));
  wstring class_name = Utf8StringToWideString(kMainWindowClass);
  window_handler_ = CreateWindowEx(
    WS_EX_OVERLAPPEDWINDOW,
    class_name.c_str(),
    window_name_wide_string_version.c_str(),
    WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
    CW_USEDEFAULT,
    CW_USEDEFAULT,
    CW_USEDEFAULT,
    CW_USEDEFAULT,
    nullptr,
    nullptr,
    GetModuleHandle(NULL),
    this
  );
  int error_code = GetLastError();
  TCHAR buffer[1024];
  _itot_s(error_code, buffer, 1024, 10);
  OutputDebugString(buffer);
  assert(IsWindow(window_handler_));
}

MainWindow::~MainWindow() {
  if (IsWindow(window_handler_)) {
    DestroyWindow(window_handler_);
  }
}

void MainWindow::Show(int show_flags)
{
  assert(IsWindow(window_handler_));
  ShowWindow(window_handler_, show_flags);
}

LRESULT MainWindow::Trigger(UINT msg, WPARAM w_param, LPARAM l_param)
{
  
  return DefWindowProc(window_handler_, msg, w_param, l_param);
}

RECT MainWindow::ClientRectangle() const
{
  RECT result;
  BOOL succeeded = GetClientRect(window_handler_, &result);
  assert(succeeded);
  return result;
}

connection MainWindow::Connect(UINT msg, std::function<LRESULT(LPARAM, WPARAM)> handler)
{
  unordered_map<UINT, boost::signals2::signal<LRESULT(LPARAM, WPARAM)>>::iterator result = handlers_.find(msg);
  if (result == handlers_.end()) {
    result = handlers_.emplace().first;
  }
  return result->second.connect(handler);
}