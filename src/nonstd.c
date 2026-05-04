#include "nonstd.h"
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#if defined(_WIN32)
#include <direct.h>
#include <windows.h>
#elif defined(__APPLE__)
#include <mach-o/dyld.h>
#include <stdint.h>
#include <unistd.h>
#else
#include <limits.h>
#include <unistd.h>
#endif

#ifndef PATH_MAX
#define PATH_MAX 4096
#endif

#ifndef S_ISDIR
#define S_ISDIR(m) (((m) & S_IFMT) == S_IFDIR)
#endif

static int fb_dir_exists(const char *path) {
    struct stat st;
    return stat(path, &st) == 0 && S_ISDIR(st.st_mode);
}

/* Locate the directory containing the running executable, then change the
   working directory to the bundled data tree. The macOS application bundle
   layout is tried first; the FHS layout (binary in bin/, data in
   share/freeband/) covers Linux and Windows installs. If no candidate
   directory exists the working directory is left unchanged so development
   builds run from a checkout continue to work. */
void fb_chdir_to_data(void) {
    char exepath[PATH_MAX];

#if defined(__APPLE__)
    uint32_t size = (uint32_t)sizeof(exepath);
    if (_NSGetExecutablePath(exepath, &size) != 0)
        return;
#elif defined(_WIN32)
    DWORD n = GetModuleFileNameA(NULL, exepath, (DWORD)sizeof(exepath));
    if (n == 0 || n >= sizeof(exepath))
        return;
#else
    ssize_t n = readlink("/proc/self/exe", exepath, sizeof(exepath) - 1);
    if (n < 0)
        return;
    exepath[n] = '\0';
#endif

    size_t len = strlen(exepath);
    while (len > 0 && exepath[len - 1] != '/' && exepath[len - 1] != '\\')
        len--;
    if (len == 0)
        return;
    exepath[len - 1] = '\0';

    static const char *candidates[] = {"/../Resources", "/../share/freeband", NULL};
    char data[PATH_MAX * 2];
    for (const char **c = candidates; *c; c++) {
        snprintf(data, sizeof(data), "%s%s", exepath, *c);
        if (fb_dir_exists(data)) {
            chdir(data);
            return;
        }
    }
}

#ifndef _WIN32

/* From http://en.wikipedia.org/wiki/Itoa#K.26R_implementation */
void strrev(char s[]) {
    int c, i, j;

    for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

void itoa(int n, char s[]) {
    int i, sign;

    if ((sign = n) < 0) /* record sign */
        n = -n;         /* make n positive */
    i = 0;
    do {                       /* generate digits in reverse order */
        s[i++] = n % 10 + '0'; /* get next digit */
    } while ((n /= 10) > 0); /* delete it */
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    strrev(s);
}
#endif
