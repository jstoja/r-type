//
//  iOSTextEdit.mm
//  R-Type
//
//  Created by Gael du Plessix on 15/01/13.
//  Copyright (c) 2013 EPITECH. All rights reserved.
//

#include "OS.h"

#ifdef OS_IOS

# include "Widget/TextEdit.h"
# include "iOSMainViewController.h"

void Widget::TextEdit::setFocus(bool focus) {
    Widget::setFocus(focus);
    if (focus) {
        getElement()->setCurrentFrame(1);
        iOSMainViewController::getInstance().openTextInput(this);
    } else {
        getElement()->setCurrentFrame(0);
    }
}

#endif