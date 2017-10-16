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

#include "batteryNode.h"
#include "Consumer2Battery_m.h"

#include <stdio.h>
#include <string.h>

Define_Module(BatteryNode);

BatteryNode::BatteryNode()
{
    // Set the pointer to nullptr, so that the destructor won't crash
    // even if initialize() doesn't get called because of a runtime
    // error or user cancellation during the startup process.
    Shutdown=nullptr;
}

BatteryNode::~BatteryNode()
{
    // Dispose of dynamically allocated the objects
    //cancelAndDelete(eventBatteryLevel);
    delete Shutdown;
    //delete Message;
}

void BatteryNode::initialize()
{
    Shutdown=nullptr;
    RatedCapacity=par("RatedCapacity");
    NominalCapacity=RatedCapacity;
    BatteryEfficiency=par("Efficiency");
    RecoveryProb=par("RecoveryProb");
    //display the battery level of the node

          sprintf(buf, "percent left: %f", BatteryEfficiency*100);
          getDisplayString().setTagArg("t", 0, buf);

   // getDisplayString().setTagArg("t", 0, NominalCapacity);
    SenderBatteryStatus=registerSignal("Battery");
    ReceiverBatteryStatus=registerSignal("Battery");


    emit(SenderBatteryStatus,NominalCapacity);
        emit(ReceiverBatteryStatus,NominalCapacity);
        last_time=simTime();
        //What is the shut-down level of the battery
                  WarningCapacity=0;
}

//void BatteryNode::handleConsumerMessage(Consumer2Battery *msg){


//}

void BatteryNode::handleMessage(cMessage *msg)
{

        // TODO - Generated method body
        Consumer2Battery *copypars = check_and_cast<Consumer2Battery *>(msg);
        //initialization, since all modes are false, set the nominal capacity to the rated capacity of the battery
        //get message length, sending interval, min voltage(capacity as percentage), and sending freq parameters
        //and initiate the simtime_t Timerecorder
      //  if(NominalCapacity>WarningCapacity){
            if(BatteryEfficiency>0.01){
//            if(copypars->getRcvMode()!=0 && copypars->getSendMode()==false && copypars->getSleepMode()==false ){
//           // TimeRecorder=0;
//
//            InterSendPeriod=copypars->getInterSendPeriod();
//            MsgLength=copypars->getMsgLength();
//            SleepModeCons=copypars->getSleepModeCons();
//            RcvModeCons=copypars->getRcvModeCons();
//            SendModeCons=copypars->getSendModeCons();
//            SendingFreq=copypars->getSendingFreq();
//            MinCapacity=copypars->getMinCapacity();
//
//            //how long will it take to send the message
//               // MsgPeriod=MsgLength/SendingFreq;
//            MsgPeriod=InterSendPeriod;
//                //how long the sleep period lasts in every sending interval
//                SleepPeriod=InterSendPeriod/10;
//                //display the battery level of the node
//                getDisplayString().setTagArg("t", 0, NominalCapacity);
//                emit(SenderBatteryStatus,NominalCapacity);
//                emit(ReceiverBatteryStatus,NominalCapacity);
//
//            }

            if(copypars->getSendModeCons()!=0){
                delta_t=(simTime()-last_time);
                timepassed=delta_t.dbl();
                ModeCons=copypars->getSendModeCons();
                BatteryEfficiency=par("Efficiency");
                NominalCapacity-=(ModeCons/BatteryEfficiency)*timepassed;
                BatteryEfficiency=NominalCapacity/RatedCapacity;
              par("Efficiency")=BatteryEfficiency;
                last_time=simTime();
                EV << "Message sending consumption deducted\n";
                //display the battery level of the node
              //  char buf[40];
                sprintf(buf, "percent left: %f", BatteryEfficiency*100);
                         getDisplayString().setTagArg("t", 0, buf);
               // getDisplayString().setTagArg("t", 0, NominalCapacity);
                emit(SenderBatteryStatus,NominalCapacity);

                }
            if(copypars->getRcvModeCons()!=0){
                delta_t=(simTime()-last_time);
                            timepassed=delta_t.dbl();
                            ModeCons=copypars->getRcvModeCons();
                            BatteryEfficiency=par("Efficiency");
                            NominalCapacity -= ModeCons/BatteryEfficiency * timepassed;
                            BatteryEfficiency=NominalCapacity/RatedCapacity;
                            par("Efficiency")=BatteryEfficiency;
                            last_time=simTime();
                 EV << "Message receiving consumption deducted\n";
                 //display the battery level of the node
             //    char buf[40];
                 sprintf(buf, "percent left: %f", BatteryEfficiency*100);
                          getDisplayString().setTagArg("t", 0, buf);
                 //getDisplayString().setTagArg("t", 0, NominalCapacity);

                             emit(ReceiverBatteryStatus,NominalCapacity);
                            }
            if(copypars->getSleepModeCons()!=0){
                delta_t=(simTime()-last_time);
                timepassed=delta_t.dbl();
                ModeCons=copypars->getSleepModeCons();
                if(NominalCapacity<RatedCapacity){
               // int k = bernoulli(1); //q
                    double R=uniform(0,1);
                  if(R>RecoveryProb){
                      BatteryEfficiency=par("Efficiency");

                      NominalCapacity-=(ModeCons/BatteryEfficiency)*timepassed;
                      BatteryEfficiency=NominalCapacity/RatedCapacity;
                      par("Efficiency")=BatteryEfficiency;
                      last_time=simTime();
                      EV << "Idle period consumption deducted\n";
                      //display the battery level of the node
              //        char buf[40];
                      sprintf(buf, "percent left: %f", BatteryEfficiency*100);
                               getDisplayString().setTagArg("t", 0, buf);
                      //  getDisplayString().setTagArg("t", 0, NominalCapacity);
                      emit(SenderBatteryStatus,NominalCapacity);


                  }
                  else{//p=1-q
                    // NominalCapacity-=SleepModeCons*SleepPeriod;
                      delta_t=(simTime()-last_time);
                       timepassed=delta_t.dbl();
                       ModeCons=copypars->getSleepModeCons();
                       BatteryEfficiency=par("Efficiency");
                     NominalCapacity+=(ModeCons/BatteryEfficiency)*timepassed;
                     BatteryEfficiency=NominalCapacity/RatedCapacity;
                     par("Efficiency")=BatteryEfficiency;
                             last_time=simTime();
                     EV << "Idle period recovery added\n";
                     //display the battery level of the node
            //         char buf[40];
                     sprintf(buf, "percent left: %f", BatteryEfficiency*100);
                              getDisplayString().setTagArg("t", 0, buf);

                     //      getDisplayString().setTagArg("t", 0, NominalCapacity);
                     emit(SenderBatteryStatus,NominalCapacity);


                  }
                }
                else{
                    delta_t=(simTime()-last_time);
                       timepassed=delta_t.dbl();
                       ModeCons=copypars->getSleepModeCons();
                       BatteryEfficiency=par("Efficiency");
                NominalCapacity-=(ModeCons/BatteryEfficiency)*timepassed;
                BatteryEfficiency=NominalCapacity/RatedCapacity;
                par("Efficiency")=BatteryEfficiency;
                last_time=simTime();
                EV << "Idle period consumption deducted\n";
               // display the battery level of the node
               // getDisplayString().setTagArg("t", 0, NominalCapacity);
           //     char buf[40];
                sprintf(buf, "percent left: %f", BatteryEfficiency*100);
                         getDisplayString().setTagArg("t", 0, buf);

                }
                emit(SenderBatteryStatus,NominalCapacity);

            }
        }
        else{
            //send the shut-down message
            //display the battery level of the node
           // getDisplayString().setTagArg("t", 0, NominalCapacity);
            BatteryEfficiency=par("Efficiency");
        //    char buf[40];
            sprintf(buf, "percent left: %f", BatteryEfficiency*100);
                                   getDisplayString().setTagArg("t", 0, buf);
            Shutdown=new cMessage("shutdown");
            send(Shutdown,"batteryout");
           // delete Shutdown;
            emit(SenderBatteryStatus,NominalCapacity);
                        emit(ReceiverBatteryStatus,NominalCapacity);
        }

}
