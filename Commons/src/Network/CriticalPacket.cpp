//
// CriticalPacket.cpp by Melvin Laplanche
// 01-19-13
//


#include <vector>
#include <cmath>
#include "Network/CriticalPacket.h"


std::list<int>      Network::CriticalPacket::_allTimes = std::list<int>();
Threading::Mutex*    Network::CriticalPacket::_mutexAllTimes = new Threading::Mutex();

Network::CriticalPacket::CriticalPacket(Network::UdpPacket *packet) : _elapsedTime(0), _sendCount(1), _packet(packet) {
}

Network::CriticalPacket::~CriticalPacket() {
    _mutexAllTimes->lock();
    _allTimes.push_back(_elapsedTime);
    if (_allTimes.size() > 100) {
        _allTimes.pop_front();
    }
    _mutexAllTimes->unlock();
}

std::list<int> const&     Network::CriticalPacket::getAllTimes(void) {
    return _allTimes;
}

double      Network::CriticalPacket::getAverageTime(void) {
    double  total = 0;

    _mutexAllTimes->lock();
    for (std::list<int>::iterator it = _allTimes.begin(); it != _allTimes.end(); it++) {
        total += *it;
    }

    double value = (_allTimes.size() == 0) ? (0) : (total / _allTimes.size());
    _mutexAllTimes->unlock();
    return value;
}

void    Network::CriticalPacket::resent(void) {
    _clock.reset();
    _sendCount += 1;
}

bool    Network::CriticalPacket::needResend(uint64 time) {
    uint64 elapsedTime = _clock.getEllapsedTime();

    if (time == 0) {
        time = getOptimizedValue();
    }
    return elapsedTime >= time;
}

uint64    Network::CriticalPacket::getOptimizedValue(void) {
    double average = getAverageTime();
    int total;

    if (_allTimes.size() == 0) {
        return 20;
    }

    for (std::list<int>::iterator it = _allTimes.begin(); it != _allTimes.end(); it++) {
        total += (*it - average) * (*it - average);
    }

    total /= _allTimes.size();
    total = sqrt(total);
    return (average + 2 * total);
}

Network::UdpPacket const*       Network::CriticalPacket::getPacket(void) const {
    return _packet;
}