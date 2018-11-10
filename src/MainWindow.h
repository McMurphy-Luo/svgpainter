#ifndef SVGPAINTER_MAINWINDOW_H_
#define SVGPAINTER_MAINWINDOW_H_

#include <Windows.h>
#include "boost/signals2/signal.hpp"

class MainWindow
{
public:
  MainWindow()
  {

  }

  MainWindow(const MainWindow&) = delete;

  MainWindow& operator=(const MainWindow&) = delete;

  HWND WindowHandle() const { return window_handle_; }

  void Show(int show_parameter) { ShowWindow(window_handle_, show_parameter); }



private:
  boost::signals2::signal<LRESULT(MainWindow*, UINT, LPARAM, WPARAM)> event_bus_;
  HWND window_handle_;
};

#endif // SVGPAINTER_MAINWINDOW_H_