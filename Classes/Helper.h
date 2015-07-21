//
//  Helper.h
//  TableView
//
//  Created by yzq on 15/7/21.
//
//

#ifndef __TableView__Helper__
#define __TableView__Helper__

#include <time.h>

class Helper
{
public:
    static std::string StrFtime(time_t ts, const std::string& format);
};

#endif /* defined(__TableView__Helper__) */
