#ifndef SVGPAINTER_CONFIG_H_
#define SVGPAINTER_CONFIG_H_

  #if defined(_DEBUG) || defined(DEBUG)
    #define SVGPAINTER_DEBUG
  #endif

  #ifdef SVGPAINTER_DEBUG
    #define _CRTDBG_MAP_ALLOC
    #include <stdlib.h>
    #include <crtdbg.h>
    #define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
    // Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
    // allocations to be of _CLIENT_BLOCK type
  #endif

#endif // SVGPAINTER_CONFIG_H_