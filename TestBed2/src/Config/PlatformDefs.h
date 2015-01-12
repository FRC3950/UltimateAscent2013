#if !defined(__PLATFORMDEFS_H__)

#define __PLATFORMDEFS_H__

#if defined(_MAC)

#define NOEXCEPT noexcept
#define DIRSEP '/'

#elif defined(_MSC_VER)

#define NOEXCEPT throw()
#define DIRSEP '\\'

#else

#define NOEXCEPT throw()
#define DIRSEP '//'

#endif

#endif
