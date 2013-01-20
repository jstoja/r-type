#include "Proxy.hpp"

template <>
void Network::Proxy<Network::UdpPacket>::readFinished(ASocket*, ByteArray&, const HostAddress& hostAddress, uint16 port) {
    _packet->update();
    if (_packet->isComplete()) {
		_packet->setFrom(hostAddress, port);
        if (_delegate) {
            _delegate->packetReceived(_packet);

//            uint32 code, id;
//            *_packet >> code >> id;
//
//            std::map<uint32, Network::CriticalPacket*>::iterator it = _criticalPackets.find(id);
//
//            if (it != _criticalPackets.end()) {
//               delete _criticalPackets[id];
//               _criticalPackets.erase(it);
//           }
       }
	_packet = new Network::UdpPacket();
       _packet->read(_socket);
   }
   else
    _packet->read(_socket);
}
