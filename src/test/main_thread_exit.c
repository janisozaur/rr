/* -*- Mode: C; tab-width: 8; c-basic-offset: 2; indent-tabs-mode: nil; -*- */

#include "rrutil.h"

static pthread_t main_thread;

static void breakpoint(void) {}

static void* start_thread(void* p) {
  test_assert(0 == pthread_join(main_thread, NULL));
  breakpoint();
  atomic_puts("EXIT-SUCCESS");
  return NULL;
}

int main(int argc, char** argv) {
  pthread_t thread;

  main_thread = pthread_self();
  test_assert(0 == pthread_create(&thread, NULL, start_thread, NULL));
  pthread_exit(NULL);
  test_assert(0);
  return 0;
}
