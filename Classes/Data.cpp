//
//  Data.cpp
//  TableView
//
//  Created by yzq on 15/7/21.
//
//

#include "Data.h"
#include "cocos2d.h"

Data::Data(const std::string &path)
:pdb_(nullptr), path_(path), tableName_("wk"){
    
}

Data::~Data(){
    
}

int32_t Data::openDb(){
    std::string path = this->path_;//2
    
    std::string sql;
    int result;
    result = sqlite3_open(path.c_str(), &this->pdb_);//3
    if(result != SQLITE_OK)
    {
        return -1;
    }
    return 0;
}

int32_t Data::closeDb(){
    return sqlite3_close(this->pdb_);
}

int32_t Data::querySingle(const std::string &issue){
    char **re;//查询结果
    int r,c;//行、列
    std::string sql = "select num from " + this->tableName_ + " where issue = '" + issue + "' limit 1";
    sqlite3_get_table(this->pdb_, sql.c_str(), &re,&r,&c,NULL);//1
//    log("row is %d,column is %d",r,c);
    if (r < 1){
        sqlite3_free_table(re);
        return -1;
    }
    
    assert(c==1 and r==1);
    int res = atoi(re[1]);
//    for(int i=1;i<=r;i++)//2
//    {
//        for(int j=0;j<c;j++)
//        {
//            log("%s",re[i*c+j]);
//        }
//    }
    sqlite3_free_table(re);
    return res;
}

std::map<std::string, int32_t> Data::queryOneday(const std::string &date){
    char **re;//查询结果
    int r,c;//行、列
    std::string sql = "select num from " + this->tableName_ + " where issue like " + date + "%";
    sqlite3_get_table(this->pdb_, sql.c_str(), &re,&r,&c,NULL);//1
    //    log("row is %d,column is %d",r,c);
    if (r < 1){
        sqlite3_free_table(re);
        return {};
    }
    
    assert(c==2);
    std::map<std::string, int32_t> res;
    for(int i=1;i<=r;i++)//2
    {
        res[re[i*c+0]] = atoi(re[i*c+1]);
    }
    sqlite3_free_table(re);
    return res;
}

int32_t Data::deleteSinge(const std::string &issue){
    std::string sql;
    sql = "delete from "+this->tableName_+" where issue='" + issue + "'";
    
    int res = sqlite3_exec(this->pdb_, sql.c_str(), NULL, NULL, NULL);
    if (res != SQLITE_OK){
        return -1;
    }
    return 0;
}

int32_t Data::addSingle(const std::string &issue, int32_t num){
    std::string sql;
    sql = "insert into " + this->tableName_ + " values ('" + issue + "', '" + std::to_string(num) + "')";
    int res=sqlite3_exec(this->pdb_, sql.c_str(), NULL, NULL, NULL);

    if (res != SQLITE_OK){
        return -1;
    }
    return 0;
}

