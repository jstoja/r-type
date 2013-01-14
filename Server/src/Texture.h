//
// Texture.h for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  sam. janv. 12 17:27:36 2013 Samuel Olivier
//

#ifndef _TEXTURE_H_
# define _TEXTURE_H_

# include <string>

# include <ITexture.h>
# include <Object.h>
# include <Resource.h>
# include <Network/TcpPacket.h>

class Texture : public ITexture, public Object {
public:
	Texture(std::string const& filepath);
	virtual ~Texture();

	Resource*	getImg() const;

private:
	Resource*	_img;
};

Network::APacket&		operator<<(Network::APacket& packet, Texture const& texture);

#endif