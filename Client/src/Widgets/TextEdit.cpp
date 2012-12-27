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
#include "TextEdit.h"

Widget::TextEdit::TextEdit() :
    Widget(), _event(NULL) {
}

Widget::TextEdit::TextEdit(std::string const& text) :
    Widget(), _event(NULL), _text(text) {
}

Widget::TextEdit::~TextEdit() {    
}

std::string const&  Widget::TextEdit::getText() const {
    return _text;
}

void    Widget::TextEdit::setText(std::string const& text) {
    _text = text;
}

void    Widget::TextEdit::setText(const char* text) {
    _text = text;
}