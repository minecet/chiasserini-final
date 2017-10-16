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

//
// TODO auto-generated module
//
simple BatteryNode
{
    parameters:
   		//capacity of the battery is 7200 Asec=2000mAh
   		volatile double RatedCapacity=7200000000; //
   	 	volatile double Efficiency=1;
   	 	volatile double RecoveryProb=0.7;
    	@display("i=block/control");
    	@signal[Battery](type="double");
        @statistic[NominalCapacity](title="NominalCapacity"; source="Battery"; record=vector,stats; interpolationmode=none);
    gates:
        input batteryin;
        output batteryout;
        
}
