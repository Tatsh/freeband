#ifndef NONSTD_H
#define NONSTD_H

void fb_chdir_to_data(void);

#ifndef _WIN32
void strrev(char s[]);
void itoa(int n, char s[]);
#endif

#endif
