#include "./Painter.h"
#include <cassert>
#include <sstream>
#include "./MainWindow.h"

using std::endl;
using std::basic_ostringstream;

namespace
{
  /*
  typedef struct DXGI_OUTPUT_DESC
    {
    WCHAR DeviceName[ 32 ];
    RECT DesktopCoordinates;
    BOOL AttachedToDesktop;
    DXGI_MODE_ROTATION Rotation;
    HMONITOR Monitor;
    } 	DXGI_OUTPUT_DESC;
  */
  void OutputOutput(CComPtr<IDXGIOutput> output) {
    DXGI_OUTPUT_DESC output_description;
    output->GetDesc(&output_description);
    basic_ostringstream<TCHAR> debug_string;
    debug_string << TEXT("Outputing a output:") << endl;
    debug_string << TEXT("  DeviceName: ") << output_description.DeviceName << endl;
    debug_string << TEXT("  DesktopCoordinates: left ") << output_description.DesktopCoordinates.left
      << TEXT(" top: ") << output_description.DesktopCoordinates.top
      << TEXT(" right: ") << output_description.DesktopCoordinates.right
      << TEXT(" bottom:  ") << output_description.DesktopCoordinates.bottom
      << endl;
    debug_string << TEXT("  AttatchToDesktop: ") << (output_description.AttachedToDesktop ? TEXT("true") : TEXT("false")) << endl;
    LPCTSTR rotation = nullptr;
    switch (output_description.Rotation) {
      case DXGI_MODE_ROTATION_UNSPECIFIED:
        rotation = TEXT("DXGI_MODE_ROTATION_UNSPECIFIED");
        break;
      case DXGI_MODE_ROTATION_IDENTITY:
        rotation = TEXT("DXGI_MODE_ROTATION_IDENTITY");
        break;
      case DXGI_MODE_ROTATION_ROTATE90:
        rotation = TEXT("DXGI_MODE_ROTATION_ROTATE90");
        break;
      case DXGI_MODE_ROTATION_ROTATE180:
        rotation = TEXT("DXGI_MODE_ROTATION_ROTATE180");
        break;
      case DXGI_MODE_ROTATION_ROTATE270:
        rotation = TEXT("DXGI_MODE_ROTATION_ROTATE270");
        break;
    }
    debug_string << TEXT("  Rotation: ") << rotation << endl;
    debug_string << TEXT("  HMONITOR: ") << output_description.Monitor << endl;
    debug_string << TEXT("End output a output------------") << endl;
    OutputDebugString(debug_string.str().c_str());
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
      << TEXT(" AdapterLuid.LowPart: ") << description.AdapterLuid.LowPart << endl;
    debug_string << TEXT("End print adapter------------") << endl;
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

  /*
  typedef struct DXGI_MODE_DESC
  {
    UINT Width;
    UINT Height;
    DXGI_RATIONAL RefreshRate;
    DXGI_FORMAT Format;
    DXGI_MODE_SCANLINE_ORDER ScanlineOrdering;
    DXGI_MODE_SCALING Scaling;
  } DXGI_MODE_DESC;
  */
  void OutputDXGIMode(DXGI_MODE_DESC dxgi_mode) {
    basic_ostringstream<TCHAR> debug_string;
    debug_string << TEXT("Output DXGI_MODE_DESC: ") << endl;
    debug_string << TEXT("  Height: ") << dxgi_mode.Height << endl;
    debug_string << TEXT("  Width: ") << dxgi_mode.Width << endl;
    debug_string << TEXT("  RefreshRate.Denominator: ") << dxgi_mode.RefreshRate.Denominator
      << TEXT("  RefreshRate.Numerator: ") << dxgi_mode.RefreshRate.Numerator << endl;
    debug_string << TEXT("  Format: ") << dxgi_mode.Format << endl;
    LPCTSTR scanline_ordering = NULL;
    switch (dxgi_mode.ScanlineOrdering) {
      case DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED:
        scanline_ordering = TEXT("DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED");
        break;
      case DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE:
        scanline_ordering = TEXT("DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE");
        break;
      case DXGI_MODE_SCANLINE_ORDER_UPPER_FIELD_FIRST:
        scanline_ordering = TEXT("DXGI_MODE_SCANLINE_ORDER_UPPER_FIELD_FIRST");
        break;
      case DXGI_MODE_SCANLINE_ORDER_LOWER_FIELD_FIRST:
        scanline_ordering = TEXT("DXGI_MODE_SCANLINE_ORDER_LOWER_FIELD_FIRST");
        break;
    }
    debug_string << TEXT(" ScanlineOrdering: ") << scanline_ordering << endl;
    LPCTSTR scaling = NULL;
    switch (dxgi_mode.Scaling) {
    case DXGI_MODE_SCALING_UNSPECIFIED:
      scaling = TEXT("DXGI_MODE_SCALING_UNSPECIFIED");
      break;
    case DXGI_MODE_SCALING_CENTERED:
      scaling = TEXT("DXGI_MODE_SCALING_CENTERED");
      break;
    case DXGI_MODE_SCALING_STRETCHED:
      scaling = TEXT("DXGI_MODE_SCALING_STRETCHED");
      break;
    }
    debug_string << TEXT(" Scaling: ") << scaling << endl;
    OutputDebugString(debug_string.str().c_str());
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
  assert(IsWindow(the_window->WindowHandle()));
  HRESULT result = CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&dxgi_factory_));
  assert(SUCCEEDED(result));
  result = dxgi_factory_->EnumAdapters(0, &dxgi_adapter_);
  assert(SUCCEEDED(result));
  result = dxgi_adapter_->EnumOutputs(0, &dxgi_output_);
  assert(SUCCEEDED(result));
  InspectDXAdapters(dxgi_factory_);
  result = D3D11CreateDevice(
    dxgi_adapter_,
    D3D_DRIVER_TYPE_UNKNOWN,
    NULL,
    D3D11_CREATE_DEVICE_BGRA_SUPPORT,
    NULL,
    0,
    D3D11_SDK_VERSION,
    &d3d_device_,
    NULL,
    &d3d_device_context_
  );
  assert(SUCCEEDED(result));
  DXGI_MODE_DESC interested_mode_to_match;
  interested_mode_to_match.Width = 0; // auto
  interested_mode_to_match.Height = 0; // auto
  interested_mode_to_match.RefreshRate.Denominator = 0;
  interested_mode_to_match.RefreshRate.Numerator = 0;
  interested_mode_to_match.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
  interested_mode_to_match.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
  /*
  @Todo
  I don't know how to choose the DXGI_FORMAT.
  So use the simplest format now.
  If in the future I have additional knowledge about the color format.
  Maybe I shall change it.
  */
  interested_mode_to_match.Format = DXGI_FORMAT_UNKNOWN;
  DXGI_MODE_DESC the_best_mode;
  result = dxgi_output_->FindClosestMatchingMode(&interested_mode_to_match, &the_best_mode, d3d_device_);
  assert(SUCCEEDED(result));
  OutputDXGIMode(the_best_mode);
  DXGI_SWAP_CHAIN_DESC swap_chain_description;
  swap_chain_description.BufferDesc = the_best_mode;
  swap_chain_description.OutputWindow = the_window->WindowHandle();
  swap_chain_description.BufferCount = 1;
  swap_chain_description.SampleDesc.Count = 1;
  swap_chain_description.SampleDesc.Quality = 0;
  swap_chain_description.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
  swap_chain_description.Windowed = TRUE;
  swap_chain_description.SwapEffect = DXGI_SWAP_EFFECT_SEQUENTIAL;
  swap_chain_description.Flags = 0;
  result = dxgi_factory_->CreateSwapChain(
    d3d_device_,
    &swap_chain_description,
    &swap_chain_
  );
  assert(SUCCEEDED(result));

  swap_chain_->GetBuffer(0, )
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
  
}

void Painter::Paint(const tinysvg::DomString& the_svg_doc_string)
{
  


}