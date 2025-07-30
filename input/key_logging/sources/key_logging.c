#include <key_logging.h>

#include <pthread.h>
#include <signal.h>
#include <stdio.h>

#include <CoreFoundation/CoreFoundation.h>
#include <CoreGraphics/CoreGraphics.h>

pthread_mutex_t mutex_lock;
CFRunLoopRef run_loop_reference;

void handler_interrupt() {
  CFRunLoopStop(run_loop_reference);
  pthread_mutex_unlock(&mutex_lock);
}

struct __CGEvent* tap_event(
  struct __CGEventTapProxy * proxy_tap_event,
  CGEventType type_event,
  struct __CGEvent *event,
  void* data_user
) {
  if (type_event == kCGEventKeyDown) {
    fprintf(
      data_user,
      "key_down: "
    );
  } else if (type_event == kCGEventKeyUp) {
    fprintf(
      data_user,
      "key_up: "
    );
  }

  long long int code_key = CGEventGetIntegerValueField(
    event,
    kCGKeyboardEventKeycode
  );

  fprintf(
    data_user,
    "%lli\n",
    code_key
  );

  return event;
}

int main() {
  CGEventMask mask_event = CGEventMaskBit(kCGEventKeyDown) | CGEventMaskBit(kCGEventKeyUp);

  CFMachPortRef mach_port_reference = CGEventTapCreate(
    kCGAnnotatedSessionEventTap,
    kCGHeadInsertEventTap,
    kCGEventTapOptionListenOnly,
    mask_event,
    tap_event,
    stdout
  );

  if (mach_port_reference == (void*)0) {
    fprintf(
      stderr,
      "failed_to_create_tap\n"
    );

    return 1;
  }

  CFRunLoopSourceRef run_loop_source_reference = CFMachPortCreateRunLoopSource(
    kCFAllocatorDefault,
    mach_port_reference,
    0
  );

  run_loop_reference = CFRunLoopGetCurrent();

  CFRunLoopAddSource(
    run_loop_reference,
    run_loop_source_reference,
    kCFRunLoopCommonModes
  );

  pthread_mutex_init(
    &mutex_lock,
    (void*)0
  );

  struct sigaction signal_action;
  signal_action.sa_handler = handler_interrupt;
  sigaction(SIGINT, &signal_action, (void*)0);

  pthread_mutex_lock(&mutex_lock);

  CFRunLoopRun();

  pthread_mutex_lock(&mutex_lock);

  pthread_mutex_destroy(&mutex_lock);

  CFRelease(mach_port_reference);

  return 0;
}
