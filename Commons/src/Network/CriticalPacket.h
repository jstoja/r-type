//
// CriticalPacket.cpp by Melvin Laplanche
// 01-19-13
//


#ifndef _CRITICALPACKET_H
# define _CRITICALPACKET_H


# include "UdpPacket.h"
# include "Threading/Mutex.h"
# include <list>
# include "Clock.h"

namespace Network {
    class COMMON_EXPORT_IMPORT CriticalPacket {
    public:
        CriticalPacket(Network::UdpPacket *packet);
        ~CriticalPacket();

        Network::UdpPacket const*       getPacket(void) const;
        int                             getTime(void) const;
        static std::list<int> const&    getAllTimes(void);
        static double                   getAverageTime(void);

        void    resent(void);
        bool    needResend(uint64 time);
        uint64  getOptimizedValue(void);

    private:
        int                                                     _elapsedTime;
        int                                                     _sendCount;
        Network::UdpPacket*                                     _packet;
        Clock                                                   _clock;
        static std::list<int>                                   _allTimes;
        static Threading::Mutex*                                _mutexAllTimes;
    };
}
#endif