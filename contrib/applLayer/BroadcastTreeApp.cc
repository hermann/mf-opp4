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

#include "BroadcastTreeApp.h"

#include <NetwControlInfo.h>
#include <SimpleAddress.h>

Define_Module(BroadcastTreeApp);

/**
 * First we have to initialize the module from which we derived ours,
 * in this case BasicModule.
 *
 * Then we will set a timer to indicate the first time we will send a
 * message
 */
void BroadcastTreeApp::initialize(int stage) {
	BasicApplLayer::initialize(stage);
	if (stage == 0) {
		broadcasted = false;
		delayTimer = new cMessage("delay-timer", SEND_BROADCAST_TIMER);
	} else if (stage == 1) {
		scheduleAt(simTime() + dblrand() * 10, delayTimer);
	}
}

/**
 * There are two kinds of messages that can arrive at this module: The
 * first (kind = BROADCAST_MESSAGE) is a broadcast packet from a
 * neighbor node to which we have to send a reply. The second (kind =
 * BROADCAST_REPLY_MESSAGE) is a reply to a broadcast packet that we
 * have send and just causes some output before it is deleted
 **/
void BroadcastTreeApp::handleLowerMsg(cMessage* msg) {
	ApplPkt *m;
	switch (msg->getKind()) {
	case BROADCAST_MESSAGE:
		m = static_cast<ApplPkt *> (msg);
		EV << "Received a broadcast packet from host[" << m->getSrcAddr() << "]\n";
		if (broadcasted) {
			EV << "This host has already broadcasted.\n";
		} else {
			sendBroadcast();
		}
		break;
	case BROADCAST_REPLY_MESSAGE:
		m = static_cast<ApplPkt *>(msg);
		EV << "Received reply from host["<<m->getSrcAddr()<<"]; delete msg\n";
		delete msg;
		break;
	default:
		EV <<"Error! got packet with unknown kind: " << msg->getKind()<<endl;
		delete msg;
	}
}

/**
 * A timer with kind = SEND_BROADCAST_TIMER indicates that a new
 * broadcast has to be send (@ref sendBroadcast).
 *
 * There are no other timer implemented for this module.
 *
 * @sa sendBroadcast
 */
void BroadcastTreeApp::handleSelfMsg(cMessage *msg) {
	switch (msg->getKind()) {
	case SEND_BROADCAST_TIMER:
		sendBroadcast();
		delete msg;
		break;
	default:
		EV<< "Unkown selfmessage! -> delete, kind: "<<msg->getKind() <<endl;
		delete msg;
	}
}

/**
 * This function creates a new broadcast message and sends it down to
 * the network layer if the host is part of the broadcast tree.
 */
void BroadcastTreeApp::sendBroadcast() {
	// Check whether this host is part of the broadcast tree.
	int broadcastRate = par("broadcastRate");
	if (broadcastRate > 0) {
		ApplPkt *pkt = new ApplPkt("BROADCAST_MESSAGE", BROADCAST_MESSAGE);
		pkt->setDestAddr(-1);
		// we use the host modules getIndex() as a appl address
		pkt->setSrcAddr(myApplAddr());
		pkt->setBitLength(headerLength);

		// set the control info to tell the network layer the layer 3
		// address;
		// TODO: Communicate the desired rate to the lower layer.
		pkt->setControlInfo(new NetwControlInfo(L3BROADCAST));

		EV << "Sending broadcast packet.\n";
		sendDown(pkt);
		broadcasted = true;
	} else {
		EV << "This host does not belong to the broadcast tree.\n";
	}
}

void BroadcastTreeApp::sendReply(ApplPkt *msg) {
	simtime_t delay;

	delay = uniform(0, 0.01);

	msg->setDestAddr(msg->getSrcAddr());
	msg->setSrcAddr(myApplAddr());
	msg->setKind(BROADCAST_REPLY_MESSAGE);
	msg->setName("BROADCAST_REPLY_MESSAGE");
	sendDelayedDown(msg, delay);

	EV<< "sent message with delay " << delay << endl;

	//NOTE: the NetwControl info was already ste by the network layer
	//and stays the same
}

void BroadcastTreeApp::finish() {
	BasicApplLayer::finish();
	if (!delayTimer->isScheduled())
		delete delayTimer;
}
