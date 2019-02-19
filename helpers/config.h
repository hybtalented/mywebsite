#ifndef CONFIG_H
#define CONFIG_H

#include <TGlobal>
#include "applicationhelper.h"
#include<qvariant.h>
#define CONFIG_TABLE_NAME "config"
class T_HELPER_EXPORT Config : public ApplicationHelper
{
public:
	static QString getConfig(const QString & name);
};

#endif // CONFIG_H
