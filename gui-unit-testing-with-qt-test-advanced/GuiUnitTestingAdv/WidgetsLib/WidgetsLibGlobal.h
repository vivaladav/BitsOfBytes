#pragma once

#include <QtCore/qglobal.h>

#if defined(WIDGETSLIB_LIBRARY)
	#define WIDGETSLIBSHARED_EXPORT Q_DECL_EXPORT
#else
	#define WIDGETSLIBSHARED_EXPORT Q_DECL_IMPORT
#endif

#define MAKE_TESTABLE(className) friend class Test##className
