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

#ifndef __FINALPROJECT_BATTERYNODE_H_
#define __FINALPROJECT_BATTERYNODE_H_

#include <omnetpp.h>
#include "Consumer2Battery_m.h"

#include <stdio.h>
#include <string.h>

using namespace omnetpp;

/**
 * TODO - Generated class
 */
class BatteryNode : public cSimpleModule
{
  private:

   //the receiver node (rx) has 3 pointers: 2 used for self-triggering events
   //discharge (eventBatteryLevel) periodically and recharging (eventRecharge) periodically and stochastically
   //the other one is for the received message (Message)
   // pointer for self-discharge (self message)
   //cMessage *eventBatteryLevel;
   // Message itself
   //cMessage *Message;
   cMessage *Shutdown;
   //simtime_t TimeRecorder;
   double RatedCapacity;
   double NominalCapacity;
  // double InterSendPeriod;
  // double MsgLength;
   double ModeCons;
   //double RcvModeCons;
   //double SendModeCons;
   //double SendingFreq;
  // double MinCapacity;
  // double MsgPeriod;
  // double SleepPeriod;
   double RecoveryProb;
   volatile double BatteryEfficiency;
   double WarningCapacity;
   simsignal_t SenderBatteryStatus;
   simsignal_t ReceiverBatteryStatus;
   simtime_t last_time;
     simtime_t delta_t;
     double timepassed;
     char buf[1000];
  public:
    BatteryNode();
    virtual ~BatteryNode();
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
   // virtual void handleConsumerMessage(Consumer2Battery *msg);
};

#endif
