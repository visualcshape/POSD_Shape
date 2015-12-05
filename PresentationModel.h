//
// Created by VodalokLab on 2015/12/4.
//

#ifndef HW2_PRESENATAIONMODEL_H
#define HW2_PRESENATAIONMODEL_H
#include "Subject.h"

class PresentationModel : public Subject{
public:
    PresentationModel();

    inline bool IsUndoEnabled() const{ return _undoEnabled;}
    inline void SetUndoEnabled(bool isEnabled){
        _undoEnabled = isEnabled;
        Notify();
    }

    inline bool IsRedoEnabled() const{ return _redoEnabled;}
    inline void SetRedoEnabled(bool isEnabled){
        _redoEnabled = isEnabled;
        Notify();
    }

    inline bool IsUngroupEnabled() const {return _ungroupEnabled;}
    inline void SetUngroupEnabled(bool isEnabled) {
        _ungroupEnabled = isEnabled;
        Notify();
    }

    inline bool IsDeleteGraphicEnabled() const { return  _deleteGraphicEnabled;}
    inline void SetDeleteGraphicEnabled(bool isEnabled){
        _deleteGraphicEnabled = isEnabled;
        Notify();
    }

    inline bool IsGroupEnabled() const {return _groupEnabled;}
    inline void SetGroupEnabled(bool isEnabled){
        _groupEnabled = isEnabled;
        Notify();
    }

    //Force UI update button's Enable state
    inline void Refresh(){Notify();}
private:
    bool _undoEnabled;
    bool _redoEnabled;
    bool _groupEnabled;
    bool _ungroupEnabled;
    bool _deleteGraphicEnabled;
};


#endif //HW2_PRESENATAIONMODEL_H
