//
// Frame.h for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  dim. janv. 13 17:50:25 2013 Samuel Olivier
//

#ifndef _FRAME_H_
# define _FRAME_H_

# include <Vec2.h>
# include <Network/APacket.h>

class Frame {
public:
	Frame(Vec2 const& p1, Vec2 const& p2);

	Vec2    p1;
	Vec2    p2;
};

Network::APacket&		operator<<(Network::APacket & packet, Frame const& element);

#endif