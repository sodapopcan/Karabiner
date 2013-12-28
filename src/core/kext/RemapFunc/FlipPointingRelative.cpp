#include <IOKit/IOLib.h>

#include "EventOutputQueue.hpp"
#include "FlipPointingRelative.hpp"
#include "IOLogWrapper.hpp"

namespace org_pqrs_KeyRemap4MacBook {
  namespace RemapFunc {
    FlipPointingRelative::FlipPointingRelative(void) : flipHorizontal_(false), flipVertical_(false)
    {}

    FlipPointingRelative::~FlipPointingRelative(void)
    {}

    void
    FlipPointingRelative::add(unsigned int datatype, unsigned int newval)
    {
      switch (datatype) {
        case BRIDGE_DATATYPE_OPTION:
        {
          Option option(newval);
          /*  */ if (Option::FLIPPOINTINGRELATIVE_HORIZONTAL == option) {
            flipHorizontal_ = true;
          } else if (Option::FLIPPOINTINGRELATIVE_VERTICAL == option) {
            flipVertical_ = true;
          } else {
            IOLOG_ERROR("FlipPointingRelative::add unknown option:%d\n", newval);
          }
          break;
        }

        default:
          IOLOG_ERROR("FlipPointingRelative::add invalid datatype:%d\n", datatype);
          break;
      }
    }

    bool
    FlipPointingRelative::remap(RemapPointingParams_relative& remapParams)
    {
      if (remapParams.isremapped) return false;
      if (remapParams.params.dx == 0 && remapParams.params.dy == 0) return false;
      remapParams.isremapped = true;

      int dx = remapParams.params.dx;
      int dy = remapParams.params.dy;

      if (flipHorizontal_) {
        dx = -dx;
      }
      if (flipVertical_) {
        dy = -dy;
      }

      EventOutputQueue::FireRelativePointer::fire(ButtonStatus::makeButtons(), dx, dy);

      return true;
    }
  }
}
