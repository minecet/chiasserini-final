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

#ifndef __FINALPROJECT_ENERGYCONSUMPTIONMODEL_H_
#define __FINALPROJECT_ENERGYCONSUMPTIONMODEL_H_

#include <omnetpp.h>
#include "Consumer2Battery_m.h"

using namespace omnetpp;

/**
 * TODO - Generated class
 */
class EnergyConsumptionModel : public cSimpleModule
{
    private:

        //the sender node (tx) has 4 pointers: 3 used for self-triggering events
        //to send a message (eventSendMsg) and discharge (eventBatteryLevel) periodically,
        //and recharging (eventRecharge) periodically and stochastically
        //the other one is the sent message itself (Message)

        // pointer for scheduling a message(self message)
        //cMessage *eventSendMsg;
        // pointer for self-discharge (self message)
        cMessage *eventScheduleMsg;
        // Message itself
        cMessage *Shutdown;
        //pointer for recharging event
        cMessage *eventIdleMsg;
       //pointer for receive message event
        cMessage *eventReceiveMsg;
        cMessage *Message;
    //    double InterSendPeriod;
       // double MsgLength;
        double SleepModeCons;
        double RcvModeCons;
        double SendModeCons;
       // double SendingFreq;
        //double MinCapacity;

        double MsgPeriod;
           double SleepPeriod;

  public:
   EnergyConsumptionModel();
   virtual ~EnergyConsumptionModel();
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};

#endif
