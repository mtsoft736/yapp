/*
 * yapp.h — Yet Another Print Protocol
 * Drop-in náhrada za printf jako Windows DLL
 */

#ifndef YAPP_H
#define YAPP_H

#include <stdarg.h>

#ifdef _WIN32
  #ifdef YAPP_EXPORTS
    #define YAPPAPI __declspec(dllexport)
  #else
    #define YAPPAPI __declspec(dllimport)
  #endif
#else
  #define YAPPAPI
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Hlavní funkce — stejná signatura jako printf.
 * Použití: yapp("Ahoj %s, máš %d let!\n", "Matej", 20);
 */
YAPPAPI int yapp(const char *fmt, ...);

/**
 * Výpis s automatickým '\n' na konci — nemusíš psát \n.
 * Použití: yappln("Ahoj %s!", "Matej");
 */
YAPPAPI int yappln(const char *fmt, ...);

/**
 * Výpis do libovolného FILE streamu (stdout, stderr, soubor...).
 * Použití: yapf(stderr, "Chyba: %s\n", msg);
 */
YAPPAPI int yapf(void *stream, const char *fmt, ...);

#ifdef __cplusplus
}
#endif

#endif /* YAPP_H */
