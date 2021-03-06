/* -*- Mode: C; tab-width: 8; c-basic-offset: 2; indent-tabs-mode: nil; -*- */

#include "rrutil.h"

static void fault_handler(int sig, siginfo_t* si, void* context) {
  atomic_puts("FAILED: handler should not have been called for blocked signal");
}

static void* start_thread(void* p) {
  sigset_t s;

  syscall(SYS_write, STDOUT_FILENO, "EXIT-", 5);

  sigemptyset(&s);
  sigaddset(&s, SIGSEGV);
  sigprocmask(SIG_BLOCK, &s, NULL);

  syscall(SYS_write, STDOUT_FILENO, "SUCCESS\n", 8, 9, 10, 11);

  __asm__ __volatile__("jmp 0x42");

  return NULL;
}

int main(int argc, char* argv[]) {
  struct sigaction act;
  pthread_t thread;

  act.sa_sigaction = fault_handler;
  act.sa_flags = SA_SIGINFO | SA_NODEFER;
  sigemptyset(&act.sa_mask);
  sigaction(SIGSEGV, &act, NULL);

  pthread_create(&thread, NULL, start_thread, NULL);
  pthread_join(thread, NULL);

  return 0;
}
