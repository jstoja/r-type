//
//  Sprite.cpp
//  R-Type
//
//  Created by Gael du Plessix on 20/12/12.
//
//

#include "Sprite.h"

#include "Debug.h"
#include "GraphicException.h"

Graphic::Sprite::Frame::Frame(Vec2 const& p1, Vec2 const& p2)
: p1(p1), p2(p2) {
}

Graphic::Sprite::Sprite() :
Object(), _texture(NULL), _frames(),
_textureCoords(NULL), _needRebuildTextureCoords(true) {
}

Graphic::Sprite::Sprite(uint32 id) :
Object(id), _texture(NULL), _frames(),
_textureCoords(NULL), _needRebuildTextureCoords(true) {
}


Graphic::Sprite::~Sprite() {
}

Graphic::Texture* Graphic::Sprite::getTexture() const {
    return _texture;
}

void Graphic::Sprite::setTexture(Texture* texture) {
    _texture = texture;
}

void Graphic::Sprite::addFrame(Frame const& frame) {
    _frames.push_back(frame);
}

Graphic::Sprite::Frame const& Graphic::Sprite::getFrame(uint32 index) {
    return _frames[index];
}

Graphic::Bufferf* Graphic::Sprite::getTexuteCoordsBuffer(void) {
    if (_textureCoords == NULL || _needRebuildTextureCoords) {
        if (_frames.size() == 0)
            throw new Graphic::Exception("Sprite has no frame");
        
        // Build texture coords based on the frames
        std::vector<float32> textureCoords;
        textureCoords.reserve(_frames.size() * 12);
        for (std::vector<Frame>::const_iterator it = _frames.begin(),
             end = _frames.end(); it != end; ++it) {
            Frame const& frame = *it;
            
            // Triangle 1
            textureCoords.push_back(frame.p1.x);  textureCoords.push_back(frame.p1.y);
            textureCoords.push_back(frame.p2.x);  textureCoords.push_back(frame.p1.y);
            textureCoords.push_back(frame.p1.x);  textureCoords.push_back(frame.p2.y);
            
            // Triangle 2
            textureCoords.push_back(frame.p1.x);  textureCoords.push_back(frame.p2.y);
            textureCoords.push_back(frame.p2.x);  textureCoords.push_back(frame.p1.y);
            textureCoords.push_back(frame.p2.x);  textureCoords.push_back(frame.p2.y);
        }
        
        if (_textureCoords == NULL)
            _textureCoords = new Bufferf(Bufferf::VertexArray);
        _textureCoords->setData(&textureCoords[0], textureCoords.size());
    }
    _needRebuildTextureCoords = false;
    return _textureCoords;
}