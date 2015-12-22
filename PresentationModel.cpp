//
// Created by VodalokLab on 2015/12/4.
//

#include "PresentationModel.h"

PresentationModel::PresentationModel() {
    this->SetUndoEnabled(false);
    this->SetRedoEnabled(false);
    this->SetDeleteGraphicEnabled(false);
    this->SetUngroupEnabled(false);
    this->SetGroupEnabled(false);
    this->SetMoveDownEnabled(false);
    this->SetMoveUpEnabled(false);
}

void PresentationModel::checkMoveUpDownButtonEnable(vector<Graphics *> *content, Graphics *graphicsToLocate) {
    if(!content || !graphicsToLocate){
        this->SetMoveDownEnabled(false);
        this->SetMoveUpEnabled(false);
        return;
    }
    int layerSize = content->size();
    int position  = find(content->begin(),content->end(),graphicsToLocate) - content->begin();
    if(layerSize<=1){
        this->SetMoveDownEnabled(false);
        this->SetMoveUpEnabled(false);
        return;
    }
    if(position==0) {
        this->SetMoveDownEnabled(true);
        this->SetMoveUpEnabled(false);
        return;
    }
    if(position==layerSize-1){
        this->SetMoveDownEnabled(false);
        this->SetMoveUpEnabled(true);
        return;
    }
    this->SetMoveDownEnabled(true);
    this->SetMoveUpEnabled(true);
}
