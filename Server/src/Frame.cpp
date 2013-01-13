//
// Frame.cpp for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  dim. janv. 13 17:56:03 2013 Samuel Olivier
//

#include "Frame.h"

Frame::Frame(Vec2 const& p1, Vec2 const& p2)
: p1(p1), p2(p2) {
}

Network::APacket&		operator<<(Network::APacket & packet, Frame const& element) {
	return packet << element.p1 << element.p2;
}
