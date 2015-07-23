//
//  Model.h
//  TableView
//
//  Created by yzq on 15/7/23.
//
//

#ifndef __TableView__Model__
#define __TableView__Model__

#include <vector>
#include <map>
#include "data.h"

class Model{
public:
    struct cellValue{
        int num;
        int bgColor;//0white, 1red, 2green
        int fontColor;//0black, 1red, 2green
    };
    Model(const std::string& db);
    int32_t init(const std::string& date);
    virtual ~Model();
    
    int32_t update(const std::string& issue, int32_t num);
    std::map<std::string, std::vector<cellValue>> getAllCells();
private:
    std::string db_;
    Data* pd_;
    std::string date_;
    std::map<std::string, int32_t> tableData_;
    std::map<std::string, std::vector<cellValue>> allCells_;
    void calcCellValue();
    std::string getIssue(int index);
};

#endif /* defined(__TableView__Model__) */
