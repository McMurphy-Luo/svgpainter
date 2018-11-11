#ifndef SVGPAINTER_MAINWINDOW_H_
#define SVGPAINTER_MAINWINDOW_H_

#include "./Config.h"
#include <unordered_map>
#include <Windows.h>
#include "boost/signals2.hpp"
#include "common/DomString.h"

const char* const kMainWindowClass = u8"MainWindow.svgpainter";

class MainWindow
{
public:
  MainWindow(const tinysvg::DomString& window_name);

  MainWindow(const MainWindow&) = delete;

  MainWindow& operator=(const MainWindow&) = delete;

  ~MainWindow();

  HWND WindowHandle() const { return window_handler_; }

  void Show(int show_parameter);

  MSG LastMessage() const { return last_message_; }

  MSG PreviousMessage() const { return previous_message_; }

  RECT ClientRectangle() const;

  LRESULT Trigger(UINT msg, WPARAM w_param, LPARAM l_param);

  boost::signals2::connection Connect(UINT msg, std::function<LRESULT(LPARAM, WPARAM)> handler);

private:
  std::unordered_map<UINT, boost::signals2::signal<LRESULT(LPARAM, WPARAM)>> handlers_;
  HWND window_handler_;
  MSG last_message_;
  MSG previous_message_;
};

#endif // SVGPAINTER_MAINWINDOW_H_