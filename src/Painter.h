#ifndef SVGPAINTER_PAINTER_H_
#define SVGPAINTER_PAINTER_H_

#include "./Config.h"
#include <atlbase.h>
#include <d2d1.h>
#include <dxgi.h>
#include <d3d11.h>
#include "common/DomString.h"

class MainWindow;

class Painter
{
public:
  Painter(MainWindow* the_window);

  void Paint(const tinysvg::DomString& the_svg_doc_string);

private:
  MainWindow* the_window_;
  CComPtr<IDXGIFactory> dxgi_factory_;
  CComPtr<IDXGIAdapter> dxgi_adapter_;
  CComPtr<IDXGIOutput> dxgi_output_;
  CComPtr<IDXGISwapChain> swap_chain_;
  CComPtr<ID3D11Device> d3d_device_;
  CComPtr<ID2D1RenderTarget> render_target_;
};


#endif //SVGPAINTER_PAINTER_H_