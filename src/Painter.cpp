#include "./Painter.h"
#include <d2d1.h>

namespace // unamed namespace for this file static staff
{


}// end unamed namespace

Painter::Painter(MainWindow* the_window)
  : the_window_(the_window)
  , render_target_()
{

}

void Painter::Paint(const tinysvg::NodeDelegate<tinysvg::SvgSvg> target)
{
  


}