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

package org.mf2.contrib.applLayer;

// Broadcast tree application
//
// @author Hermann S. Lichte
simple BroadcastTreeApp like BasicApplLayer
{
    parameters:
        bool debug = default(false); // debug switch
        double headerLength; // length of the application message header (in bits)

        // Rate to use for broadcast
        //
        // If the broadcast rate is zero, the host does not belong to the broadcast
        // tree. Otherwise, a non-zero value indicates which rate to use.
        int broadcastRate = default(0);
    gates:
        input lowergateIn;  // from network layer
        input lowerControlIn;
        output lowergateOut; // to network layer
}
