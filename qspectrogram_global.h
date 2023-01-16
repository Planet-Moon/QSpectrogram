#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(QSPECTROGRAM_LIB)
#  define QSPECTROGRAM_EXPORT Q_DECL_EXPORT
# else
#  define QSPECTROGRAM_EXPORT Q_DECL_IMPORT
# endif
#else
# define TTPLOT_EXPORT
#endif
