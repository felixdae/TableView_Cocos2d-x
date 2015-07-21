//
//  Helper.cpp
//  TableView
//
//  Created by yzq on 15/7/21.
//
//

#include "Helper.h"

std::string Helper::StrFtime(time_t its, const std::string& format)
{
    const char* pf = format.c_str();
    struct tm dt;
    time_t ts = its;
    localtime_r(&ts, &dt);
    
    char out[128];
    int32_t rc = strftime(out, sizeof(out), pf, &dt);
    if (rc <= 0)
    {
        return "";
    }
    return std::string(out);
}
