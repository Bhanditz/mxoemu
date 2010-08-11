// ***************************************************************************
//
// Reality - The Matrix Online Server Emulator
// Copyright (C) 2006-2010 Rajko Stojadinovic
// http://mxoemu.info
//
// ---------------------------------------------------------------------------
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// ---------------------------------------------------------------------------
//
// ***************************************************************************

#ifndef MXOSIM_GAMESERVER_H
#define MXOSIM_GAMESERVER_H

#include "Common.h"
#include "ByteBuffer.h"
#include "Singleton.h"
#include "ObjectMgr.h"
#include <Sockets/SocketHandler.h>
#include "MessageTypes.h"
#include "Timer.h"

#include <boost/timer.hpp>

class GameServer : public Singleton <GameServer>
{
public:
	GameServer() { };
	~GameServer() { /* TODO: Add destructor code */ };
	bool Start();
	void Stop();
	void Loop();
	ObjectMgr &getObjMgr() { return m_objMgr; }
	class GameClient *GetClientWithSessionId(uint32 sessionId);
	void Broadcast(const ByteBuffer &message);
	void AnnounceStateUpdate(class GameClient* clFrom,msgBaseClassPtr theMsg, bool immediateOnly=false);
	void AnnounceCommand(class GameClient* clFrom,msgBaseClassPtr theCmd);
	uint32 GetSimTime() const
	{
		uint64 timeDiff = getMSTime64() - m_serverStartMS;
		timeDiff = (timeDiff*64)/1000;
		return uint32(timeDiff);
	}
private:	
	ObjectMgr m_objMgr;
	SocketHandler m_udpHandler;
	shared_ptr<class GameSocket> m_mainSocket;
	uint64 m_serverStartMS;
};


#define sGame GameServer::getSingleton()
#define sObjMgr GameServer::getSingleton().getObjMgr()

#endif

