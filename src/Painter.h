#ifndef SVGPAINTER_PAINTER_H_
#define SVGPAINTER_PAINTER_H_

#include "./Config.h"
#include <atlbase.h>
#include <d2d1.h>
#include "./MainWindow.h"
#include "svg/SvgBase.h"
#include "svg/SvgSvg.h"

class Painter
{
public:
  Painter(MainWindow* the_window);

  void Paint(const tinysvg::NodeDelegate<tinysvg::SvgSvg> target);

private:
  MainWindow* the_window_;
  CComPtr<ID2D1RenderTarget> render_target_;
};


#endif //SVGPAINTER_PAINTER_H_