/*
 * yapp.c — Yet Another Print Protocol
 * Automatická podpora UTF-8 na Windows přes DllMain + SetConsoleOutputCP
 */

#define YAPP_EXPORTS
#include "yapp.h"

#include <stdio.h>
#include <stdarg.h>

#ifdef _WIN32
  #include <windows.h>

  /* DllMain se zavolá automaticky při načtení DLL do procesu.
   * Není třeba volat nic ručně — Windows to udělají za tebe. */
  BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
  {
      (void)hinstDLL;
      (void)lpvReserved;

      if (fdwReason == DLL_PROCESS_ATTACH) {
          SetConsoleOutputCP(CP_UTF8);   /* stdout/stderr -> UTF-8 */
          SetConsoleCP(CP_UTF8);         /* stdin         -> UTF-8 */
      }
      return TRUE;
  }
#endif

int yapp(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    int ret = vprintf(fmt, args);
    va_end(args);
    return ret;
}

int yappln(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    int ret = vprintf(fmt, args);
    va_end(args);
    putchar('\n');
    return ret + 1;
}

int yapf(void *stream, const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    int ret = vfprintf((FILE *)stream, fmt, args);
    va_end(args);
    return ret;
}
