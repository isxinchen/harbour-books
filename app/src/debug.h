#ifndef DEBUG_H
#define DEBUG_H

#ifndef SYBEROS_DEBUG
#  define SYBEROS_DEBUG 1
#endif // SYBEROS_DEBUG

#include <QDebug>

#if SYBEROS_DEBUG
#if QT_VERSION >= 0x050000
#  define DEBUG(x) qDebug() << Q_FUNC_INFO << x
#else
#  define DEBUG(x) qDebug() << Q_FUNC_INFO << x
#endif
#  define ASSERT(x) ((x) ? ((void)0) : qt_assert(#x,__FILE__,__LINE__))
#  define VERIFY(x) ASSERT(x)
#else
#  define DEBUG(expr) ((void)0)
#  define ASSERT(expr) ((void)0)
#  define VERIFY(x) (x)
#endif // SYBEROS_DEBUG

#if QT_VERSION >= 0x050000
# define WARN(x) qWarning() << x
#else
# define WARN(x) qWarning() << Q_FUNC_INFO << x
#endif

#define VERBOSE(expr) ((void)0)

#endif // DEBUG_H
