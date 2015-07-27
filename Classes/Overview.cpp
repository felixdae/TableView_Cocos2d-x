//
//  Overview.cpp
//  TableView
//
//  Created by MAEDAHAJIME on 2015/02/10.
//
//
#include <time.h>
#include <stdlib.h>

#include "Overview.h"
#include "Helper.h"

Scene* Overview::createScene()
{
    auto scene = Scene::create();
    auto layer = Overview::create();
    scene->addChild(layer);
    
    
    return scene;
}

// on "init" you need to initialize your instance
bool Overview::init()
{
    //初期化
    if ( !Layer::init() ) return false;
    
    //画面サイズサイズを取得
    window_size = Director::getInstance()->getWinSize();
    
    // バックグランドカラー
    auto background = LayerColor::create(Color4B::WHITE,
                                         window_size.width,
                                         window_size.height);
    
    // バックグランドカラー 第2引数は表示順
    this->addChild(background, 0);
    
    std::string dt = Helper::StrFtime(time(NULL), "%Y%m%d");
    this->datetime_ = dt;
    this->db_path_ = FileUtils::getInstance()->getWritablePath()+"save.db";//2
    this->reloadData();
//    this->ds_ = new Model(this->db_path_);
//    if (0 == this->ds_->init(this->datetime_)){
//        this->allCells_ = this->ds_->getAllCells();
//        this->data_ok_ = true;
//    }

//    CCLOG("%d", this->allCells_.size());

//    // テーブル一覧ラベルを生成
//    auto label1 = Label::createWithSystemFont(dt/*"テーブル一覧"*/, "Arial", 60);
//    
//    label1->setColor(Color3B::BLACK);
//
//    // ラベルの設置
//    label1->setPosition(Vec2(window_size.width / 2 ,window_size.height - 80));
//    
//    // ラベルタイトルを追加
//    this->addChild(label1,1);
    
    
    auto editBoxSize = Size(window_size.width/2.5, 80);
    
    // top
    cocos2d::ui::EditBox* _editName;
//    std::string pNormalSprite = "green_edit.png";
    ui::Scale9Sprite* s9s = ui::Scale9Sprite::create();
//    s9s->setColor(Color3B::RED);
    
    _editName = ui::EditBox::create(editBoxSize, s9s/*ui::Scale9Sprite::create(pNormalSprite)*/);
    _editName->setPosition(Vec2(window_size.width / 2 ,window_size.height - 80));
    _editName->setFontName("Arial");
    _editName->setFontSize(40);
    _editName->setPlaceholderFontSize(40);
    _editName->setFontColor(Color3B::BLACK);
    _editName->setPlaceHolder(dt.c_str());
    _editName->setPlaceholderFontColor(Color3B::BLACK);
    _editName->setMaxLength(8);
    _editName->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
    _editName->setDelegate(this);
    _editName->setTag(9999);
    this->addChild(_editName);
    
    // テーブルのヘッダー空間
    TableView* tableView = TableView::create(this,Size(window_size.width,window_size.height*9/10));
    // テーブル全体表示
    //TableView* tableView = TableView::create(this, window_size);
    
    //展開方向
    tableView->setDirection(TableView::Direction::VERTICAL);
    //表示順序上からしたへ
    tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    
    //追加
    tableView->setDelegate(this);
    this->tv_ = tableView;
    this->addChild(tableView,2);
    tableView->reloadData();
    
    return true;
}

// セルの大きさを設定する
Size Overview::cellSizeForTable(TableView *table){
    return Size(window_size.width, 40);
}

// 1セルに表示させるValueをセット
TableViewCell* Overview::tableCellAtIndex(TableView *table, ssize_t idx){
    
    // 行番号
    std::string id = StringUtils::format("%s%003zd", this->datetime_.c_str(), idx + 1);
    // 行テキスト
    std::string text = StringUtils::format("行目");
    // セル
    TableViewCell *cell = table->dequeueCell();
    
    cell = new TableViewCell();
    cell->autorelease();
    
    // セルの背景は交互に色を変更する
    auto background_color = Color3B(185,220,255);//Color3B::GREEN;
    if (idx%2) {
        background_color = Color3B::WHITE;
    }
    
    // Background
    Sprite* bg = Sprite::create();
    bg->setAnchorPoint(Point(0, 0));
    bg->setTextureRect(Rect(0, 0, window_size.width, 40));
    bg->setColor(background_color);
    bg->setTag(100);
    cell->addChild(bg);
    
    // ボーダーライン
    Sprite* line = Sprite::create();
    line->setAnchorPoint(Point(0, 0));
    line->setTextureRect(Rect(0, 0, window_size.width, 1));
    line->setColor(Color3B::BLACK);
    cell->addChild(line);
    
//    // 画像
//    Sprite* imge_1 = Sprite::create("imge80.png");
//    imge_1->setAnchorPoint(Point(0, 0));
//    imge_1->setPosition(Point(10, 0));
//    cell->addChild(imge_1);
    
    // IDテキスト部分
    auto *label_1 = LabelTTF::create(id.c_str(), "Arial", 40);
    label_1->setAnchorPoint(Point(0, 0));
    label_1->setPosition(Point(10, 0));
    label_1->setColor(Color3B::BLACK);
    cell->addChild(label_1);
    
    if (not this->data_ok_){
        return cell;
    }
    // テキスト部分
//    if (this->allCells_.count(id) == 0){
//        CCLOG("no data for %s", id.c_str());
//    }
    std::vector<Model::cellValue> cv = this->allCells_[id];
    float orix = 280;
    for (int i = 0; i < 5; i++) {
        if (idx%2 == 0){
            if (i%2 == 0){
                text = "单";
            }
            else{
                text = "双";
            }
        }else{
            if (i%2 == 0){
                text = "双";
            }
            else{
                text = "单";
            }
        }
        auto *label_2 = LabelTTF::create(text.c_str(), "Arial", 35);
        label_2->setAnchorPoint(Point(0, 0));
        label_2->setPosition(Point(orix, 0));
        label_2->setColor(Color3B::BLACK);
        cell->addChild(label_2);
        
        cocos2d::ui::EditBox* editName;
        ui::Scale9Sprite* s9s = ui::Scale9Sprite::create();
        s9s->setColor(Color3B::RED);
        s9s->setContentSize(Size(60, 40));
        editName = ui::EditBox::create(Size(60, 40), s9s/*ui::Scale9Sprite::create(pNormalSprite)*/);
        //editName->setPosition(Vec2(window_size.width / 2 ,window_size.height - 80));
        editName->setFontName("Arial");
        editName->setFontSize(40);
        editName->setPlaceholderFontSize(60);
        auto font_color = Color3B::BLACK;
        if (cv[i].fontColor == 1){
            font_color = Color3B::RED;
        }else if(cv[i].fontColor == 2){
            font_color = Color3B::GREEN;
        }
        editName->setPlaceholderFontColor(font_color);
        editName->setFontColor(font_color);
        
//        int ball = rand()%10;

        
        editName->setMaxLength(1);
        editName->setPlaceHolder(StringUtils::format("%d", cv[i].num).c_str());
        editName->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
        editName->setAnchorPoint(Point(0, 0));
        editName->setDelegate(this);
        editName->setTag(idx * 10 + i);
//        cell->addChild(editName);
        
        // Background
        Sprite* bg2 = Sprite::create();
        bg2->setAnchorPoint(Point(0, 0));
        bg2->setTextureRect(Rect(0, 0, 40, 40));
        auto bg_color = Color3B::WHITE;
        if (cv[i].bgColor == 1){
            bg_color = Color3B::RED;
        }else if (cv[i].bgColor == 2){
            bg_color = Color3B::GREEN;
        }
        bg2->setColor(bg_color);

//        if ((odd and ball%2) or (!odd and !(ball%2)))
//        {
//            bg2->setColor(Color3B::RED);
//        }else{
//            bg2->setColor(Color3B::GREEN);
//        }
//        bg2->setTag(100);
        bg2->setPosition(Point(orix + 40, 0));

        cell->addChild(bg2);
        bg2->addChild(editName);
        
        orix += 90;
    }
    
    return cell;
}

// セル数
ssize_t Overview::numberOfCellsInTableView(TableView *table){
    return 130;
}

// セルがタッチされた時のcallback
void Overview::tableCellTouched(TableView* table, TableViewCell* cell){
//    CCLOG("%ziのセルがタッチされました", cell->getIdx());
}



void Overview::editBoxEditingDidBegin(cocos2d::ui::EditBox *editBox){
    CCLOG("editBoxEditingDidBegin: %d", editBox->getTag());
}

void Overview::editBoxEditingDidEnd(cocos2d::ui::EditBox *editBox){
    CCLOG("editBoxEditingDidEnd: %d", editBox->getTag());
}

void Overview::editBoxReturn(cocos2d::ui::EditBox *editBox){
    CCLOG("editBoxReturn: %s, %d", editBox->getText(), editBox->getTag());
    if (editBox->getTag() == 9999){
        this->datetime_ = editBox->getText();//合法性检查
        this->reloadData();
        for (int i = 0; i < 130; ++i) {
            this->tableCellAtIndex(this->tv_, i);
            this->tv_->updateCellAtIndex(i);
        }
    }else{
        int idx = editBox->getTag()/10;
        int col = editBox->getTag()%10;
        std::string id = StringUtils::format("%s%003zd", this->datetime_.c_str(), idx + 1);
        
//        this->allCells_[id][col]. = atoi(editBox->getText());
        this->tableCellAtIndex(this->tv_, idx);
        this->tv_->updateCellAtIndex(idx);

    }
//    this->tv_->updateCellAtIndex();
}

void Overview::editBoxTextChanged(cocos2d::ui::EditBox *editBox, const std::string &text){
    CCLOG("editBoxTextChanged: %s, %d", text.c_str(), editBox->getTag());
    //    if (editBox->getTag() == 9999){
    char c = *text.rbegin();
    if (not(c >= '0' and c <= '9')){
        editBox->setText(text.substr(0, text.length() - 1).c_str());
    }
    //    }
}

void Overview::reloadData(){
    if (!this->ds_){
        delete this->ds_;
        this->ds_ = nullptr;
    }
    this->data_ok_ = false;
    this->allCells_.clear();
    this->ds_ = new Model(this->db_path_);
    if (0 == this->ds_->init(this->datetime_)){
        this->allCells_ = this->ds_->getAllCells();
        this->data_ok_ = true;
    }
}