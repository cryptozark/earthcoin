// Copyright (c) 2009-2012 The Bitcoin developers
// Copyright (c) 2011-2012 Litecoin Developers
// Copyright (c) 2013 EarthCoin Developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "main.h"
#include "uint256.h"

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

	// no checkpoint now, can be added in later releases
    static MapCheckpoints mapCheckpoints =
            boost::assign::map_list_of
            (   100, uint256("0xc3d91cb4726610d422f8652a5a7cc21bd42e1b8009c00462081c81316d9abad6"))
            ( 10000, uint256("0x7b50ea3b42e613e65ec2aca6797a5780e1c545a617e4a610577fb4b040f0035b"))
			( 30000, uint256("0x43e2fe7c700191ddfabe2cd09dfd3fc9eb6331f3c19e59b3e4a87cfa88cac543"))
			( 50000, uint256("0x6a4f705b7a34de7dc1b6573b3595fde05c7b4303b35ede20a3b945244adc6c70"))
			( 69500, uint256("0x8387b49853928fc67d8b8421fd9214184db590eeecd90a200c9d902d8b42e11f"))
			;


    bool CheckBlock(int nHeight, const uint256& hash)
    {
        if (fTestNet) return true; // Testnet has no checkpoints

        MapCheckpoints::const_iterator i = mapCheckpoints.find(nHeight);
        if (i == mapCheckpoints.end()) return true;
        return hash == i->second;
    }

    int GetTotalBlocksEstimate()
    {
        if (fTestNet) return 0;
	
        return mapCheckpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        if (fTestNet) return NULL;
	
        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, mapCheckpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
		
        return NULL;
    }
}
