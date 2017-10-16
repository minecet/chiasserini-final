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

#include "energyConsumptionModel.h"
#include "Consumer2Battery_m.h"

Define_Module(EnergyConsumptionModel);
EnergyConsumptionModel::EnergyConsumptionModel()
{
    // Set the pointer to nullptr, so that the destructor won't crash
    // even if initialize() doesn't get called because of a runtime
    // error or user cancellation during the startup process.
     eventIdleMsg =eventScheduleMsg=eventReceiveMsg=nullptr;
}

EnergyConsumptionModel::~EnergyConsumptionModel()
{
    // Dispose of dynamically allocated the objects
    cancelAndDelete(eventScheduleMsg);

    cancelAndDelete(eventIdleMsg);

    cancelAndDelete(eventReceiveMsg);

}

void EnergyConsumptionModel::initialize()
{

    //at the initialization, send all consumer parameters to the battery
    //SleepMode, RcvMode, SendMode booleans =false means it is still in wake-up period
    //in energy consumer handleMessage, the messages passed to the battery model
    //will have different bool values depending on the mode(sleep, receive, or send)
    eventIdleMsg =eventScheduleMsg=eventReceiveMsg=nullptr;

  //  InterSendPeriod= par("SendingInterval");
   // MsgLength =par("MsgLength");
//    SleepModeCons=par("SleepModeCons");
//    RcvModeCons=par("RcvModeCons");
//    SendModeCons=par("SendModeCons");
//    //SendingFreq=par("SendingFreq");
//    //MinCapacity=par("MinCapacity");
//    MsgPeriod=par("LoadDuration");
//    SleepPeriod=par("SleepDuration");
//    Consumer2Battery *parameters=new Consumer2Battery("parameters");
//   // parameters->setInterSendPeriod(InterSendPeriod);
//   // parameters->setMsgLength(MsgLength);
//    parameters->setSleepModeCons(SleepModeCons);
//   // parameters->setSleepMode(false);
//    parameters->setRcvModeCons(RcvModeCons);
//    //parameters->setRcvMode(false);
//    parameters->setSendModeCons(SendModeCons);
    //parameters->setSendMode(false);
    //parameters->setSendingFreq(SendingFreq);
    //parameters->setMinCapacity(MinCapacity);
   // send(parameters,"consumerout");
    //how long will it take to send/rcv the message
    //MsgPeriod=MsgLength/SendingFreq;
    //how long the sleep period lasts in every sending interval
    //SleepPeriod=InterSendPeriod-MsgPeriod;
  //  MsgPeriod=InterSendPeriod-0.33;
                    //how long the sleep period lasts in every sending interval
    //                SleepPeriod=InterSendPeriod-1;
    //this case is for sending mode
    if(MsgPeriod!=0){
    eventScheduleMsg= new cMessage("eventScheduleMsg");
    scheduleAt(simTime()+MsgPeriod, eventScheduleMsg);
    eventIdleMsg= new cMessage("eventIdleMsg");
    }
    //this case is for receiving mode
    //though the intersendperiod=0, we need to know the sender node's intersendperiod in order to
    //synchronously initiate receiving mode
    else{
    //e.g. upperlayer passes a message to energyconsumer telling the sender node's intersend period
    // double SenderIntersendPeriod=1; //this should be dynamic, we need to change it,our sender case was tested with 1sec,so for now let's set to 1 sec
     //how long the sleep period lasts in every receiving interval
    // SleepPeriod=SenderIntersendPeriod-MsgPeriod;
     //self-event to start receiving mode synchronous with the sender node's intersendperiod
     eventReceiveMsg= new cMessage("eventReceiveMsg");
     scheduleAt(simTime()+5, eventReceiveMsg);
    // eventIdleMsg= new cMessage("eventIdleMsg");

    }
}

void EnergyConsumptionModel::handleMessage(cMessage *msg)
{
    if(msg->isSelfMessage()){
        if(msg==eventScheduleMsg){
            cancelEvent(eventScheduleMsg);
            SendModeCons=par("SendModeCons");
               //SendingFreq=par("SendingFreq");
               //MinCapacity=par("MinCapacity");
               MsgPeriod=par("LoadDuration");
               SleepPeriod=par("SleepDuration");
            Consumer2Battery *parameters=new Consumer2Battery("parameters");
               // parameters->setInterSendPeriod(InterSendPeriod);
               // parameters->setMsgLength(MsgLength);
                parameters->setSleepModeCons(0);
               // parameters->setSleepMode(false);
                parameters->setRcvModeCons(0);
               // parameters->setRcvMode(false);
                parameters->setSendModeCons(SendModeCons);
               // parameters->setSendMode(true);
                //parameters->setSendingFreq(SendingFreq);
                //parameters->setMinCapacity(MinCapacity);
                send(parameters,"consumerout");
                EV << "Sending Message\n";
              //  Message= new cMessage("Message!");
               // send(Message,"batteryenergyout");
            scheduleAt(simTime()+MsgPeriod, eventIdleMsg);

           // scheduleAt(simTime()+InterSendPeriod, eventScheduleMsg);

        }
        if(msg==eventIdleMsg){

            cancelEvent(eventIdleMsg);
            SleepModeCons=par("SleepModeCons");
           //    RcvModeCons=par("RcvModeCons");
             //  SendModeCons=par("SendModeCons");
               //SendingFreq=par("SendingFreq");
               //MinCapacity=par("MinCapacity");
              // MsgPeriod=par("LoadDuration");
               SleepPeriod=par("SleepDuration");
            Consumer2Battery *parameters=new Consumer2Battery("parameters");
                        //    parameters->setInterSendPeriod(InterSendPeriod);
                         //   parameters->setMsgLength(MsgLength);
                            parameters->setSleepModeCons(SleepModeCons);
                          //  parameters->setSleepMode(true);
                            parameters->setRcvModeCons(0);
                            //parameters->setRcvMode(false);
                            parameters->setSendModeCons(0);
                           // parameters->setSendMode(false);
                           // parameters->setSendingFreq(SendingFreq);
                           // parameters->setMinCapacity(MinCapacity);
                            send(parameters,"consumerout");
                            EV << "Idle period starting\n";
          //if the node is in sending mode, schedule the next sending message event
         // if(InterSendPeriod!=0){
            scheduleAt(simTime()+SleepPeriod, eventScheduleMsg);
         // }
          //else the node is in receiving mode, schedule the next sending message event
         // else{
           //   scheduleAt(simTime()+SleepPeriod, eventReceiveMsg);
          //}
        }
      if(msg==eventReceiveMsg){
          cancelEvent(eventReceiveMsg);
          RcvModeCons=par("RcvModeCons");
          Consumer2Battery *parameters=new Consumer2Battery("parameters");
        //  parameters->setInterSendPeriod(InterSendPeriod);
         // parameters->setMsgLength(MsgLength);
          parameters->setSleepModeCons(0);
         // parameters->setSleepMode(false);
          parameters->setRcvModeCons(RcvModeCons);
         // parameters->setRcvMode(true);
          parameters->setSendModeCons(0);
         // parameters->setSendMode(false);
          //parameters->setSendingFreq(SendingFreq);
          //parameters->setMinCapacity(MinCapacity);
          send(parameters,"consumerout");
          EV << "Receiving message\n";


          scheduleAt(simTime()+0.05, eventReceiveMsg);
      }

    }
    else{
        //shutdown warning arrived

        EV << "Battery level low-Shuttind down\n";
        //delete msg;

       // cancelEvent(eventIdleMsg);
        //sender case, cancel the schedule messaging event
        if(MsgPeriod!=0){
            if(eventScheduleMsg->isScheduled()){
              cancelEvent(eventScheduleMsg);
              delete eventScheduleMsg;
            }
            if(eventIdleMsg->isScheduled()){
              cancelEvent(eventIdleMsg);
              delete eventIdleMsg;
            }
        }
        //receiver case,cancel the receive message event
        else{
            if(eventReceiveMsg->isScheduled()){
              cancelEvent(eventReceiveMsg);
              delete eventReceiveMsg;
             }

        }
    }

}
