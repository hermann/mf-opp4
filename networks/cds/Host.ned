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

package org.mf2.networks.cds;

import org.mf2.contrib.applLayer.BroadcastTreeApp;
import org.mf2.contrib.netwLayer.SimpleArp;
import org.mf2.contrib.netwLayer.SimpleNetwLayer;
import org.mf2.contrib.nic.NicCsma;
import org.mf2.core.basicModules.BasicMobility;
import org.mf2.core.blackboard.Blackboard;

module Host
{
    parameters:
        @display("bgb=250,250,white;bgp=10,10;i=device/palm");
    gates:
        input radioIn; // gate for sendDirect

    submodules:
        blackboard: Blackboard {
            parameters:
                @display("p=200,75");

        }
        mobility: BasicMobility {
            parameters:
                @display("p=200,139");

        }
        arp: SimpleArp {
            parameters:
                @display("p=200,205");

        }
        appl: BroadcastTreeApp {
            parameters:
                @display("p=90,50");

        }
        net: SimpleNetwLayer {
            parameters:
                @display("p=90,114");

        }
        nic: NicCsma {
            parameters:
                @display("p=90,176");

        }

    connections:
        nic.uppergateOut --> net.lowergateIn;
        nic.uppergateIn <-- net.lowergateOut;
        nic.upperControlOut --> net.lowerControlIn;

        net.uppergateOut --> appl.lowergateIn;
        net.uppergateIn <-- appl.lowergateOut;
        net.upperControlOut --> appl.lowerControlIn;

        radioIn --> nic.radioIn;
}
