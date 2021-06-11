#include <errno.h>
#include <type_traits>

#include <bits/feature.h>
#include <bits/ensure.h>
//#include <mlibc/debug.hpp>
#include <mlibc/all-sysdeps.hpp>
#include <../../../../kernel-abi/include/kernel-abi/syscall_nr.h>
//#include <mlibc/thread-entry.hpp>
//#include "cxx-syscall.hpp"

#define SYSCALL2(name, nr, t1, t2) \
int _sys_##name(t1 p1, t2 p2) {                      \
  unsigned long retv;                          \
  asm volatile (                    \
    "movq %1, %%rax\n\t" \
    "movq %2, %%rdi\n\t" \
    "movq %3, %%rsi\n\t" \
    "int $42 \n\t" \
    "movq %%rax, %0\n\t" \
    :"=r"(retv) \
    :"r"((unsigned long)nr), "r"((unsigned long)p1), "r"((unsigned long)p2) \
    : "%rax", "%rdi", "%rsi" \
    );                             \
  return retv;                                    \
}

SYSCALL2(anon_allocate, SYSCALL_NR_ANON_ALLOCATE, size_t, void **);

[[noreturn]]
void int3() {
  asm volatile("int $0x3");
  __builtin_unreachable();
}

#define STUB_ONLY { \
__ensure(!"STUB_ONLY function was called"); \
int3();             \
}

namespace mlibc {

void sys_libc_log(const char *message) {
}

void sys_libc_panic() {
  int3();
  __builtin_trap();
}

int sys_tcb_set(void *pointer) {
  return -1;
}

int sys_anon_allocate(size_t size, void **pointer) {
  int ret = _sys_anon_allocate(size, pointer);
  return ret;
}
int sys_anon_free(void *pointer, size_t size) {
  return -1;
}

int sys_open(const char *path, int flags, int *fd) {
  return -1;
}

int sys_close(int fd) {
  return 0;
}

int sys_read(int fd, void *buffer, size_t size, ssize_t *bytes_read) {
  return 0;
}

int sys_write(int fd, const void *buffer, size_t size, ssize_t *bytes_written) {
  return 0;
}

int sys_seek(int fd, off_t offset, int whence, off_t *new_offset) {
  return 0;
}

int sys_vm_map(void *hint, size_t size, int prot, int flags,
               int fd, off_t offset, void **window) {
  return 0;
}
int sys_vm_unmap(void *pointer, size_t size) STUB_ONLY

// All remaining functions are disabled in ldso.
#ifndef MLIBC_BUILDING_RTDL

int sys_clock_get(int clock, time_t *secs, long *nanos) {
  return 0;
}

int sys_stat(fsfd_target fsfdt, int fd, const char *path, int flags, struct stat *statbuf) {
  return -1;
}

extern "C" void __mlibc_signal_restore(void);

int sys_sigaction(int signum, const struct sigaction *act,
                  struct sigaction *oldact) {
  return -1;
}

int sys_socket(int domain, int type, int protocol, int *fd) {
  return -1;
}

int sys_msg_send(int sockfd, const struct msghdr *msg, int flags, ssize_t *length) {
  return -1;
}

int sys_msg_recv(int sockfd, struct msghdr *msg, int flags, ssize_t *length) {
  return -1;
}

int sys_fcntl(int fd, int cmd, va_list args, int *result) {
  return -1;
}

int sys_unlink(const char *path) {
  return 0;
}

int sys_sleep(time_t *secs, long *nanos) {
  return 0;
}

#if __MLIBC_POSIX_OPTION

#include <sys/ioctl.h>
#include <sched.h>

int sys_isatty(int fd) {
        return 1;
}

int sys_connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
        return 0;
}

int sys_pselect(int nfds, fd_set *readfds, fd_set *writefds,
                fd_set *exceptfds, struct timeval *timeout, const sigset_t sigmask, int *num_events) {
        return 0;
}

int sys_pipe(int *fds, int flags) {
  return 0;
}

int sys_fork(pid_t *child) {
        return 0;
}

int sys_waitpid(pid_t pid, int *status, int flags, pid_t *ret_pid) {
        return 0;
}

int sys_execve(const char *path, char *const argv[], char *const envp[]) {
        return 0;
}

int sys_sigprocmask(int how, const sigset_t *set, sigset_t *old) {
	return 0;
}

int sys_clone(void *entry, void *user_arg, void *tcb, pid_t *pid_out) {
        return 0;
}

extern "C" const char __mlibc_syscall_begin[1];
extern "C" const char __mlibc_syscall_end[1];

int sys_before_cancellable_syscall(ucontext_t *uct) {
	return 1;
}

pid_t sys_getpid() {
  return 0;
}

int sys_tgkill(int tgid, int tid, int sig) {
	return 0;
}

#endif // __MLIBC_POSIX_OPTION

int sys_vm_protect(void *pointer, size_t size, int prot) {
  return -1;
}

void sys_thread_exit() {
  while (1);
  int3();
  __builtin_trap();
}

void sys_exit(int status) {
  while (1);

  __builtin_trap();
}

#endif // MLIBC_BUILDING_RTDL

#define FUTEX_WAIT 0
#define FUTEX_WAKE 1

int sys_futex_wait(int *pointer, int expected) {
  return -1;
}

int sys_futex_wake(int *pointer) {
  return -1;
}

} // namespace mlibc
