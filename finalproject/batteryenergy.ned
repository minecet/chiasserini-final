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

package finalproject;
//network batteryenergy
module batteryenergy
{
    //network elements Node1 and 2 are communicating with each other (passing each other msgs)
    //through the UpperLayerControl part of itself
    parameters:

        @display("bgb=336,117");

    gates:
        input batteryenergyin;
        output batteryenergyout;
    submodules:
        Battery: BatteryNode {
            parameters:
                @display("i=block/routing,cyan;p=224,38");

        }
        Consumer: EnergyConsumptionModel {
            parameters:
                @display("i=block/routing,gold;p=59.895,37.51");
        }
    connections allowunconnected: 
        Battery.batteryin <-- Consumer.consumerout;
        Battery.batteryout --> Consumer.consumerin;
        //Consumer.consumerout --> batteryenergyout;//?

}

