#include "midhelp.h"


bool MidHelp::isOnlyNumber(QString &qstrSrc)
{

	    QByteArray ba = qstrSrc.toLatin1();
	    const char *s = ba.data();
	    bool bret = true;
	    while(*s)
	    {
		   if(*s>='0' && *s<='9')
		   {
	
		   }
		   else
		   {
			  bret = false;
			  break;
		   }
		   s++;
	    }
	    return bret;
}
