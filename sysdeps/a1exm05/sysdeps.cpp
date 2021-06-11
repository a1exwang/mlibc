#include <errno.h>
#include <type_traits>

#include <bits/feature.h>
#include <bits/ensure.h>
//#include <mlibc/debug.hpp>
#include <mlibc/all-sysdeps.hpp>
#include <../../../../kernel-abi/include/kernel-abi/syscall_nr.h>
//#include <mlibc/thread-entry.hpp>
//#include "cxx-syscall.hpp"

[[noreturn]]
void int3() {
  asm volatile("int $0x3");
  __builtin_unreachable();
}

#define STUB_ONLY { \
__ensure(!"STUB_ONLY function was called"); \
int3();             \
}
//
//#define NR_read 0
//#define NR_write 1
//#define NR_open 2
//#define NR_close 3
//#define NR_stat 4
//#define NR_fstat 5
//#define NR_lseek 8
//#define NR_mmap 9
//#define NR_mprotect 10
//#define NR_sigaction 13
//#define NR_rt_sigprocmask 14
//#define NR_ioctl 16
//#define NR_pipe 22
//#define NR_select 23
//#define NR_nanosleep 35
//#define NR_getpid 39
//#define NR_socket 41
//#define NR_connect 42
//#define NR_sendmsg 46
//#define NR_recvmsg 47
//#define NR_clone 56
//#define NR_fork 57
//#define NR_execve 59
//#define NR_exit 60
//#define NR_wait4 61
//#define NR_fcntl 72
//#define NR_unlink 87
//#define NR_arch_prctl 158
//#define NR_sys_futex 202
//#define NR_clock_gettime 228
//#define NR_exit_group 231
//#define NR_tgkill 234
//#define NR_pselect6 270
//#define NR_pipe2 293
//
//#define ARCH_SET_FS	0x1002



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

  return -1;
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
