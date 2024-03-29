//
// Proxy.hpp for r-type in /home/michar_l//r-type/Commons/src/Network
//
// Made by loick michard
// Login   <michar_l@epitech.net>
//
// Started on  Sun Dec 23 09:17:14 2012 loick michard
//

#ifndef _PROXY_HPP_
# define _PROXY_HPP_

# include <list>
# include <vector>
# include <map>
# include "APacket.h"
# include "IProxyDelegate.h"
# include "Threading/Mutex.h"
# include "HostAddress.h"
# include "TcpPacket.h"
# include "UdpPacket.h"
# include "Debug.h"
# include "CriticalPacket.h"

namespace Network {

    template <typename T>
    class COMMON_EXPORT_IMPORT_REMOVED Proxy : public ISocketDelegate {
    public:

        enum TcpActions {
            // Client - Server
            AuthenficitationConnection  = 0x00000000,
            InformationsGeneral         = 0x00010000,
            InformationsGameList        = 0x00010100,
            GameJoin                    = 0x00020000,
            GameQuit                    = 0x00020100,
            GameCreate                  = 0x00020200,
            PlayerReady                 = 0x00020300,
            PlayerList                  = 0x00020600,

            // Server - client
            AuthenficitationConnectionSuccess           = 0x01000000,
            AuthenficitationConnectionIncorrectLogin    = 0x01000001,
            InformationsGameGeneralResponse             = 0x01010000,
            InformationsGameListResponse                = 0x01010100,
            GameJoinSuccess                             = 0x01020000,
            GameJoinIsFull                              = 0x01020001,
            GameJoinInvalid                             = 0x01020002,
			GameStart                                   = 0x01020100,
            GameResources                               = 0x01020200,
            GameCreatedSuccess                          = 0x01020300,
            GameCreatedBadName                          = 0x01020301,
			GameNewPlayer                               = 0x01020400,
			GamePlayerReady                             = 0x01020500,
			GamePlayerList                              = 0x01020600,
        };

        enum UdpActions {
	  // SERVER - CLIENT
            GRAPHIC_ELEMENTS,
            PHYSIC_ELEMENTS,
            PLAY_SOUND,
            STOP_SOUND,
            TIME,
            UPDATE_LIFE,
            UPDATE_SCORE,
            GAME_FINISHED,

	    // CLIENT - SERVER
	    PLAYER_DIRECTION,
	    PLAYER_SHOOT,
	    PHYSIC_COLLISION
        };

        struct		ToSend {
            ToSend(T const* packet, const HostAddress& hostAddress, uint16 port)
                : packet(packet), hostAddress(hostAddress), port(port) {}

            T const*        packet;
            HostAddress     hostAddress;
            uint16          port;
        };

        Proxy(ASocket* socket, IProxyDelegate<T>* delegate) :
        _socket(socket), _delegate(delegate), _writing(false) {
            _toSend = new std::list<ToSend>;
            _socket->setDelegate(this);
            _packet = new T();
            _packet->read(socket);
        }

        virtual ~Proxy() {
        }

        void    checkCriticalPackets(void) {
            for (std::map<uint32, Network::CriticalPacket*>::iterator it = _criticalPackets.begin(); it != _criticalPackets.end(); ++it) {
                if (it->second->needResend(0)) {
                    sendPacket(it->second->getPacket());
                    it->second->resent();
                }
            }
        }

        void sendPacket(const ToSend& toSend) {
            _toSendMutex.lock();
            _toSend->push_back(toSend);
            _toSendMutex.unlock();
            if (!_writing)
                this->_write();
        }

        void sendPacket(const T* packet) {
            sendPacket(ToSend(packet, HostAddress::AnyAddress, 0));
        }

        void sendPackets(const std::vector<ToSend>& toSend) {
            _toSendMutex.lock();
            typename std::vector<ToSend>::const_iterator it;
            for (it = toSend.begin(); it != toSend.end(); ++it)
                _toSend->push_back(*it);
            _toSendMutex.unlock();
            if (!_writing)
                this->_write();
        }

        void newConnection(ASocket*) {}


        void readFinished(ASocket*, ByteArray&, const HostAddress&, uint16) {
            _packet->update();
            if (_packet->isComplete()) {
                if (_delegate) {
                    _delegate->packetReceived(_packet);
                }
                _packet = new T();
                _packet->read(_socket);
            }
            else
                _packet->read(_socket);
        }

        void dataReceived(ASocket* socket, ByteArray& data, uint32 totalSize) {
			uint32 code;
			bool ok = T::getHeaderInfos(data, code);

			if (ok)
				_delegate->packetInProgress(code, (float32)data.getSize() / totalSize);
        }

        void dataSent(ASocket*, ByteArray const&, uint32) {

        }

        void writeFinished(ASocket*, ByteArray const&) {
            _toSendMutex.lock();
            ToSend toSend = _toSend->front();
            _toSend->pop_front();
            typename std::list<ToSend>::iterator it;
            bool found = false;
            for (it = _toSend->begin(); it != _toSend->end(); ++it)
                if ((*it).packet == toSend.packet)
                    found = true;
            _toSendMutex.unlock();
            if (!found) {
                if (_delegate)
                    _delegate->packetSent(toSend.packet);
            }
            this->_write();
        }

        void disconnection(ASocket*) {
            _delegate->connectionClosed(this);
        }

		void connectionFinished(ASocket*, bool success) {
		}

    private:
        void		_write() {
            _toSendMutex.lock();
            _writing = true;
            if (_toSend->size() == 0)
                _writing = false;
            else {
                ToSend toSend = _toSend->front();
                _socket->write(toSend.packet->getData(), toSend.hostAddress, toSend.port);
            }
            _toSendMutex.unlock();
        }

        ASocket*                                     _socket;
        IProxyDelegate<T>*                           _delegate;
        T*                                           _packet;
        std::list<ToSend>                            *_toSend;
        bool                                         _writing;
        Threading::Mutex                             _toSendMutex;
        std::map<uint32, Network::CriticalPacket*>   _criticalPackets;
    };


    typedef Network::Proxy<TcpPacket> TcpProxy;
    typedef Network::Proxy<UdpPacket> UdpProxy;

    template<> void Proxy<Network::UdpPacket>::readFinished(ASocket*, ByteArray&, const HostAddress&, uint16);
}




#endif
