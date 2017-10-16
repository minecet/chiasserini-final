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
simple EnergyConsumptionModel
{
    
     parameters:
       @display("i=block/sink");
       // @signal[ReceiverMessage](type="long");
       // @statistic[numMsgReceived](title="numMsgReceived"; source="ReceiverMessage"; record=vector,stats; interpolationmode=none);
       // @signal[ReceiverSelfDischarging](type="long");
       // @statistic[numSenderSelfDischarge](title="numRcvSelfDischarge"; source="ReceiverSelfDischarging"; record=vector,stats; interpolationmode=none);
       // @signal[ReceiverRecharging](type="long");
       // @statistic[numRcvRecharge](title="numRcvRecharge"; source="ReceiverRecharging"; record=vector,stats; interpolationmode=none);
       // @signal[ReceiverBucket](type="double");
       // @statistic[bucketstatus](title="bucketstatus"; source="ReceiverBucket"; record=vector,stats; interpolationmode=none);
		//we need to set the SendingInterval to 0 to test the receiver node
		volatile double SendingInterval @unit(s) = 30s;
		//volatile double SendingInterval @unit(s) = default(1s);
		//volatile double MsgLength @unit(byte)=default(1024B);
		volatile double LoadDuration @unit(s) = 15ms;
		volatile double SleepDuration @unit(s) = 185ms;
		volatile double SleepModeCons=0.005;
		volatile double RcvModeCons=4;
		volatile double SendModeCons=4;
		//volatile double SendingFreq @unit(bps)=default(250kbps);
		//volatile double MinCapacity = default(0.1);
    gates:
        input consumerin;
        output consumerout;
}
