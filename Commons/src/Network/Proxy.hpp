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
# include "APacket.h"
# include "IProxyDelegate.h"
# include "Threading/Mutex.h"
# include "HostAddress.h"

namespace Network {

    template <typename T>
    class COMMON_EXPORT_IMPORT_REMOVED Proxy : public ISocketDelegate {
    public:
        enum UdpActions {GRAPHIC_ELEMENTS, PHYSIC_ELEMENTS, PLAY_SOUND, STOP_SOUND,
            TIME, UPDATE_LIFE, UPDATE_SCORE, GAME_FINISHED};

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
                if (_delegate)
                    _delegate->packetReceived(_packet);
                _packet = new T();
                _packet->read(_socket);
            }
            else
                _packet->read(_socket);
        }

        void dataReceived(ASocket*, ByteArray&, uint32) {

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

        ASocket*                _socket;
        IProxyDelegate<T>*      _delegate;
        T*                      _packet;
        std::list<ToSend>       *_toSend;
        bool                    _writing;
        Threading::Mutex        _toSendMutex;
    };
}

#endif
