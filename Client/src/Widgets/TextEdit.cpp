//
//  TextEdit.cpp
//  R-Type
//
//  Created by Franck Lavisse on 26/12/12.
//
//
#include <SFML/Graphics.hpp>
#include "../../../Commons/src/Event/Listener.h"
#include "../Graphic/Element.h"
#include "Widget.h"
#include "../Graphic/Font.h"
#include "Label.h"
#include "TextEdit.h"

Widget::TextEdit::TextEdit() :
    Widget(), _event(NULL), _label() {
}

Widget::TextEdit::TextEdit(std::string const& text) :
    Widget(), _event(NULL), _label() {
}

Widget::TextEdit::~TextEdit() {    
}

std::string const&  Widget::TextEdit::getText() const {
    return _label.getText();
}

void    Widget::TextEdit::setText(std::string const& text) {
    _label.setText(text);
}