/* Find sum of an array using forked child processes.
   $ gcc -std=gnu99 -Wall -Werror -pedantic parallel-sum-fork.c -lrt && /usr/bin/time ./a.out
http://stackoverflow.com/questions/19934294/how-to-calculate-the-sum-of-the-elements-of-an-array-of-integers-using-p-process
*/
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include <errno.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define PROCNAME "parallel-sum-fork"

typedef intmax_t sum_t;
#define PRI_sum_t PRIiMAX

double perf_counter() {
  struct timespec tp;
  if (clock_gettime(CLOCK_MONOTONIC_RAW, &tp) < 0) {
    perror("clock_gettime");
    abort();
  }
  return tp.tv_sec + tp.tv_nsec * 1e-9;
}

sum_t getsum(sum_t *restrict a, size_t n) {
  sum_t sum = 0;
  for (size_t i = 0; i < n; ++i)
    sum += a[i];
  return sum;
}

int main() {
   sum_t a[] = {
     1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,
     1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,
     1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,
     1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,
     1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,
     1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,
     1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,
     1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,
     1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17
   };

   double start = perf_counter();
   int fd[2];

   if (pipe(fd) < 0) {
     perror("pipe");
     exit(EXIT_FAILURE);
   }
   const int nchildren = 8;
   pid_t pid[nchildren];
   for (size_t child = 0; child < nchildren; ++child)  {
     if ((pid[child] = fork()) < 0) {
         perror("fork");
         exit(EXIT_FAILURE);
       }
       else if (pid[child] == 0) { // child
         intmax_t sum = 0;
         close(fd[0]); // close the unused read end of the pipe

         for (size_t n = 0; n < 1000000; n+=nchildren)
           sum += getsum(a, sizeof(a) / sizeof(*a));

        // until sum is written to the parent
         for (ssize_t nwritten = 0; nwritten != sizeof(sum); ) {
           ssize_t m = write(fd[1], &sum + nwritten, sizeof(sum) - nwritten);
           if (m != -1)
             nwritten += m;
           else if (errno != EINTR) { // error
             perror("write");
             _exit(EXIT_FAILURE);
           }
         }
         close(fd[1]); // no more results for the parent
         _exit(EXIT_SUCCESS); // the child is done
       }
   }
   close(fd[1]); // close the unused write end of the pipe

   // parent
   int exit_status = EXIT_SUCCESS;
   { // read partial sums
     FILE *fp = fdopen(fd[0], "rb");
     sum_t psums[nchildren];
     if (fp && fread(psums, sizeof(*psums), nchildren, fp) == nchildren) {
       printf("got sum: %" PRIiMAX " in %.2f seconds\n",
              getsum(psums, nchildren), perf_counter() - start);
     }
     else {
       fputs(PROCNAME ": failed to read partial sums from children\n",
             stderr);
       exit_status = EXIT_FAILURE;
     }
     if (fp)
       fclose(fp);

     // get children statuses
     for (size_t child = 0; child < nchildren; ) {
       int status = 0;
       if (waitpid(pid[child], &status, 0) == -1) {
         if (errno != EINTR) {
           perror("waitpid");
           exit_status = EXIT_FAILURE;
         }
         else // try again with the same child
           continue;
       }
       else if (WIFEXITED(status)) {
         int returncode = WEXITSTATUS(status);
         if (returncode != 0)
           fprintf(stderr, PROCNAME ": %d child returned non-zero status %d\n",
                   pid[child], returncode);
       }
       else if (WIFSIGNALED(status)) {
         fprintf(stderr, PROCNAME ": %d child killed by signal %d\n",
                 pid[child], WTERMSIG(status));
       }
       else {
         fprintf(stderr, PROCNAME ": %d child returned unexpected status %d\n",
                 pid[child], status);
       }
       ++child; // next child
     }
   }
   exit(exit_status);
}