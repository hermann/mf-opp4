//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//

#ifndef BROADCASTTREEAPP_H_
#define BROADCASTTREEAPP_H_

#include "BasicApplLayer.h"

/**
 * @brief Broadcast tree application
 *
 * @ingroup applLayer
 * @author Hermann S. Lichte
 **/
class BroadcastTreeApp: public BasicApplLayer {
private:
	/** @brief Indicates whether the host has already broadcasted its packet. */
	bool broadcasted;

public:

	/** @brief Initialization of the module and some variables*/
	virtual void initialize(int);
	virtual void finish();

	enum APPL_MSG_TYPES {
		SEND_BROADCAST_TIMER, BROADCAST_MESSAGE, BROADCAST_REPLY_MESSAGE
	};

protected:
	cMessage *delayTimer;

protected:
	/** @brief Handle self messages such as timer... */
	virtual void handleSelfMsg(cMessage*);

	/** @brief Handle messages from lower layer */
	virtual void handleLowerMsg(cMessage*);

	/** @brief send a broadcast packet to all connected neighbors */
	void sendBroadcast();

	/** @brief send a reply to a broadcast message */
	void sendReply(ApplPkt *msg);
};

#endif /* BROADCASTTREEAPP_H_ */
