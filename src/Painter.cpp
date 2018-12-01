#include "./Painter.h"
#include <cassert>
#include <d2d1.h>
#include <dxgi.h>
#include <sstream>
#include "./MainWindow.h"

using std::endl;
using std::basic_ostringstream;

namespace
{
  void OutputOutput(CComPtr<IDXGIOutput> output) {
    basic_ostringstream<TCHAR> debug_string;
    DXGI_OUTPUT_DESC output_description;
    output->GetDesc(&output_description);


  }

  void InspectDXOutputs(CComPtr<IDXGIAdapter> adapter) {
    UINT output_id = 0;
    do {
      CComPtr<IDXGIOutput> output;
      HRESULT result = adapter->EnumOutputs(output_id, &output);
      if (result == DXGI_ERROR_NOT_FOUND) {
        break;
      }
      assert(SUCCEEDED(result));
      OutputOutput(output);
      ++output_id;
    } while (true);
  }

  /*
   typedef struct DXGI_ADAPTER_DESC
   {
     WCHAR Description[ 128 ];
     UINT VendorId;
     UINT DeviceId;
     UINT SubSysId;
     UINT Revision;
     SIZE_T DedicatedVideoMemory;
     SIZE_T DedicatedSystemMemory;
     SIZE_T SharedSystemMemory;
     LUID AdapterLuid;
   } DXGI_ADAPTER_DESC;
  */

  void OutputAdapterDescription(DXGI_ADAPTER_DESC description) {
    basic_ostringstream<TCHAR> debug_string;
    debug_string << TEXT("Print a adapter------------") << endl;
    debug_string << TEXT("  Description: ") << description.Description << endl;
    debug_string << TEXT("  VendorId: ") << description.VendorId << endl;
    debug_string << TEXT("  DeviceId: ") << description.DeviceId << endl;
    debug_string << TEXT("  SubSysId: ") << description.SubSysId << endl;
    debug_string << TEXT("  Revision: ") << description.Revision << endl;
    debug_string << TEXT("  DedicatedVideoMemory: ") << description.DedicatedVideoMemory << endl;
    debug_string << TEXT("  DedicatedSystemMemory: ") << description.DedicatedSystemMemory << endl;
    debug_string << TEXT("  SharedSystemMemory: ") << description.SharedSystemMemory << endl;
    debug_string << TEXT("  AdapterLuid.HighPart: ") << description.AdapterLuid.HighPart
      << TEXT("AdapterLuid.LowPart: ") << description.AdapterLuid.LowPart << endl;
    debug_string << TEXT("End------------") << endl;
    OutputDebugString(debug_string.str().c_str());
  }

  void InspectDXAdapters(CComPtr<IDXGIFactory> factory) {
    UINT adapter_id = 0;
    do {
      CComPtr<IDXGIAdapter> adapter;
      DXGI_ADAPTER_DESC adapter_description;
      HRESULT result = factory->EnumAdapters(adapter_id, &adapter);
      if (result == DXGI_ERROR_NOT_FOUND) {
        break;
      }
      assert(SUCCEEDED(result));
      result = adapter->GetDesc(&adapter_description);
      OutputAdapterDescription(adapter_description);
      InspectDXOutputs(adapter);
      assert(SUCCEEDED(result));
      ++adapter_id;
    } while (true);
  }
}

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
  InspectDXAdapters(dxgi_factory_);

  /*
  result = D3D11CreateDeviceAndSwapChain(
    dxgi_adapter_,
    D3D_DRIVER_TYPE_HARDWARE, // enforce gpu render
    NULL,
    D3D11_CREATE_DEVICE_BGRA_SUPPORT, // for support d2d interoperability 
    NULL, // default feature level set
    D3D11_SDK_VERSION,

  );
  */
  assert(SUCCEEDED(result));
}

void Painter::Paint(const tinysvg::DomString& the_svg_doc_string)
{
  


}