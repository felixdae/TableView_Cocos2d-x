//
//  Data.h
//  TableView
//
//  Created by yzq on 15/7/21.
//
//

#ifndef __TableView__Data__
#define __TableView__Data__

#include <map>
#include "sqlite3.h"

class Data
{
public:
    Data(const std::string &path);
    virtual ~Data();
    
    //db operation
    int32_t querySingle(const std::string& issue);
    std::map<std::string, int32_t> queryOneday(const std::string& date);
    int32_t updateRecord(const std::string& issue, int32_t num);
private:
    int32_t openDb();
    int32_t closeDb();
    int32_t addSingle(const std::string& issue, int32_t num);
    int32_t deleteSinge(const std::string& issue);
private:
    sqlite3 *pdb_;
    std::string path_;
    std::string tableName_;
    
};
#endif /* defined(__TableView__Data__) */
