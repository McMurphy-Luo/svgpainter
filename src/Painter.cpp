#include "./Painter.h"
#include <cassert>
#include <d2d1.h>
#include <dxgi.h>
#include "./MainWindow.h"


Painter::Painter(MainWindow* the_window)
  : the_window_(the_window)
  , dxgi_factory_()
  , dxgi_adapter_()
  , dxgi_output_()
  , swap_chain_()
  , d3d_device_()
  , render_target_()
{
  assert(the_window);
  HRESULT result = CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&dxgi_factory_));
  assert(SUCCEEDED(result));
  result = dxgi_factory_->EnumAdapters(0, &dxgi_adapter_);
  assert(SUCCEEDED(result));
  result = dxgi_adapter_->EnumOutputs(0, &dxgi_output_);
  DXGI_SWAP_CHAIN_DESC swap_chain_description;

  result = D3D11CreateDeviceAndSwapChain(
    dxgi_adapter_,
    D3D_DRIVER_TYPE_HARDWARE, // enforce gpu render
    NULL,
    D3D11_CREATE_DEVICE_BGRA_SUPPORT, // for support d2d interoperability 
    NULL, // default feature level set
    D3D11_SDK_VERSION,

  );
  assert(SUCCEEDED(result));
}

void Painter::Paint(const tinysvg::DomString& the_svg_doc_string)
{
  


}