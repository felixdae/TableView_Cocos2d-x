//
//  Model.cpp
//  TableView
//
//  Created by yzq on 15/7/23.
//
//

#include "Model.h"

Model::Model(const std::string& db)
:db_(db){
    this->pd_ = new Data(this->db_);
}

Model::~Model(){
    
}

int32_t Model::init(const std::string &date){
    this->date_ = date;
    this->tableData_ = this->pd_->queryOneday(date);
    this->calcCellValue();
    return 0;
}

std::map<std::string, std::vector<Model::cellValue>> Model::getAllCells(){
    return this->allCells_;
}

int32_t Model::update(const std::string &issue, int32_t num){
    tableData_[issue] = num;
    this->calcCellValue();
    this->pd_->updateRecord(issue, num);
    return 0;
}

void Model::calcCellValue(){
    for (int i = 0; i < 130; i++) {
//        char buf[10];
//        snprintf(buf, 10, "%003d", i);
        std::string issue = this->getIssue(i);
        if (this->tableData_.count(issue) != 1){
            Model::cellValue cv;
            cv.num = 0;
            cv.bgColor = 0;
            cv.fontColor = 0;
            this->allCells_[issue] = std::vector<Model::cellValue>(5, cv);
        } else {
            int num = this->tableData_[issue];
            for (int j = 0; j < 5;  ++j){
                Model::cellValue cv;
                int rem = num%10;
                num = num/10;
                cv.num = rem;
                if ((i%2 == 0 and j%2 == 0)
                    or (i%2 == 1 and j%2 == 1)){
                    if (num%2 == 1){
                        cv.fontColor = 1;
                    }else{
                        cv.fontColor = 2;
                    }
                }else{
                    if (num%2 == 1){
                        cv.fontColor = 2;
                    }else{
                        cv.fontColor = 1;
                    }
                }
            }
        }
    }
    for (int i = 0; i < 5; i++){
        int cc = 0;
        for (int j = 0; j < 130; j++) {
            if (this->allCells_[this->getIssue(j)][i].fontColor == 1){
                cc++;
                if (cc == 4){
                    this->allCells_[this->getIssue(j)][i].bgColor = 1;
                    this->allCells_[this->getIssue(j-1)][i].bgColor = 1;
                    this->allCells_[this->getIssue(j-2)][i].bgColor = 1;
                    this->allCells_[this->getIssue(j-3)][i].bgColor = 1;
                }else if(cc > 4){
                    this->allCells_[this->getIssue(j)][i].bgColor = 1;
                }
            }else{
                cc = 0;
            }
        }
    }
}

std::string Model::getIssue(int index){
    char buf[10];
    snprintf(buf, 10, "%003d", index);
    std::string issue = this->date_ + buf;
    return issue;
}