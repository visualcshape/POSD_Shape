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
}
