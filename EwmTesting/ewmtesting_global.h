#ifndef EWM_TESTING_GLOBAL_H
#define EWM_TESTING_GLOBAL_H

#include "allmemory.h"
#include "testsetparser.h"
#include "progaramm.h"
#include <QtCore/qglobal.h>
#include<QString>

#include <QElapsedTimer>




#if defined(EWM_TESTING_LIBRARY)


#  define EWM_TEST Q_DECL_EXPORT
#else
#  define EWM_TEST Q_DECL_IMPORT
#endif


#endif // EWM_TESTING_GLOBAL_H
