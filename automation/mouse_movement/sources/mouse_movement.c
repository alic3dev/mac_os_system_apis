#include <CoreGraphics/CoreGraphics.h>

#include <time.h>

int main() {
  unsigned int id_display_main = CGMainDisplayID();

  struct CGSize size_display = {
    .width = CGDisplayPixelsWide(
      id_display_main
    ),
    .height = CGDisplayPixelsHigh(
      id_display_main
    )
  };

  struct CGSize size_display_half = {
    .width = size_display.width / 2.0f,
    .height = size_display.height / 2.0f
  };

  struct CGPoint point_mouse;
  struct CGPoint point_mouse_current;
  struct CGSize size_step;

  struct timespec time_sleep = {
    .tv_nsec = 1000000
  };

  unsigned int frame = 0;
  unsigned short int steps_max = 1000;

  while (1) {
    point_mouse.x = sinf(frame * size_display.width) * size_display_half.width + size_display_half.width;
    point_mouse.y = sinf(frame * size_display.height) * size_display_half.height + size_display_half.height;

    size_step.width = (
      (point_mouse.x - point_mouse_current.x) / steps_max
    );

    size_step.height = (
      (point_mouse.y - point_mouse_current.y) / steps_max
    );

    for (
      unsigned short int step = 0;
      step < steps_max;
      ++step
    ) {
      point_mouse_current.x = (
        point_mouse_current.x +
        size_step.width
      );

      point_mouse_current.y = (
        point_mouse_current.y +
        size_step.height
      );

      CGWarpMouseCursorPosition(
        point_mouse_current
      );

      nanosleep(&time_sleep, (void*)0);
    }
    
    ++frame;

    if (frame + 1 >= UINT_MAX) {
      frame = 0;
    }
  }

  return 0;
}

