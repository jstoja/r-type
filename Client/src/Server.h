//
//  Server.h
//  R-Type
//
//  Created by Gael du Plessix on 18/01/13.
//
//

#ifndef __R_Type__Server__
# define __R_Type__Server__

# include "Game.h"
# include <vector>
# include <string>
# include <Network/TcpPacket.h>

class Server {
public:
    
    static Server* newServer(Network::TcpPacket& packet);
    
    Server(void);
    ~Server(void);
    
    void clearGames(void);
    void readGameList(Network::TcpPacket& packet);

private:
    std::string         _name;
    std::vector<Game*>  _games;
};

#endif /* defined(__R_Type__Server__) */
