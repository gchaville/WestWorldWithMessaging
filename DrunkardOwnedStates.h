#ifndef DRUNKARD_OWNED_STATES_H
#define DRUNKARD_OWNED_STATES_H
//------------------------------------------------------------------------
//
//  Name:   DrunkardOwnedStates.h
//
//  Desc:   All the states that can be assigned to the Drunkard class.
//          Note that a global state has not been implemented.
//
//  Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#include "fsm/State.h"


class Drunkard;
struct Telegram;




//------------------------------------------------------------------------
//
//  In this state the Drunkard will walk to a goldmine and pick up a nugget
//  of gold. If the Drunkard already has a nugget of gold he'll change state
//  to VisitBankAndDepositGoldLoto. If he gets thirsty he'll change state
//  to PlayLoto
//------------------------------------------------------------------------
class EnterSaloonAndGetSmashed : public State<Drunkard>
{
private:
  
  EnterSaloonAndGetSmashed(){}

  //copy ctor and assignment should be private
  EnterSaloonAndGetSmashed(const EnterSaloonAndGetSmashed&);
  EnterSaloonAndGetSmashed& operator=(const EnterSaloonAndGetSmashed&);
 
public:

  //this is a singleton
  static EnterSaloonAndGetSmashed* Instance();

  virtual void Enter(Drunkard* Drunkard);

  virtual void Execute(Drunkard* Drunkard);

  virtual void Exit(Drunkard* Drunkard);

  virtual bool OnMessage(Drunkard* agent, const Telegram& msg);

};

//------------------------------------------------------------------------
//
//  Entity will go to a bank and deposit any nuggets he is carrying. If the 
//  Drunkard is subsequently wealthy enough he'll walk home, otherwise he'll
//  keep going to get more gold
//------------------------------------------------------------------------
class VisitBankAndDepositGoldLoto : public State<Drunkard>
{
private:
  
  VisitBankAndDepositGoldLoto(){}

  //copy ctor and assignment should be private
  VisitBankAndDepositGoldLoto(const VisitBankAndDepositGoldLoto&);
  VisitBankAndDepositGoldLoto& operator=(const VisitBankAndDepositGoldLoto&);
 
public:

  //this is a singleton
  static VisitBankAndDepositGoldLoto* Instance();

  virtual void Enter(Drunkard* Drunkard);

  virtual void Execute(Drunkard* Drunkard);

  virtual void Exit(Drunkard* Drunkard);

  virtual bool OnMessage(Drunkard* agent, const Telegram& msg);
};


//------------------------------------------------------------------------
//
//  Drunkard will go home and sleep until his fatigue is decreased
//  sufficiently
//------------------------------------------------------------------------
class GoHomeAndSoberUpTilRested : public State<Drunkard>
{
private:
  
  GoHomeAndSoberUpTilRested(){}

  //copy ctor and assignment should be private
  GoHomeAndSoberUpTilRested(const GoHomeAndSoberUpTilRested&);
  GoHomeAndSoberUpTilRested& operator=(const GoHomeAndSoberUpTilRested&);
 
public:

  //this is a singleton
  static GoHomeAndSoberUpTilRested* Instance();

  virtual void Enter(Drunkard* Drunkard);

  virtual void Execute(Drunkard* Drunkard);

  virtual void Exit(Drunkard* Drunkard);

  virtual bool OnMessage(Drunkard* agent, const Telegram& msg);
};


//------------------------------------------------------------------------
//
//  Drunkard changes location to the saloon and keeps buying Whiskey until
//  his thirst is quenched. When satisfied he returns to the goldmine
//  and resumes his quest for nuggets.
//------------------------------------------------------------------------
class PlayLoto : public State<Drunkard>
{
private:
  
  PlayLoto(){}

  //copy ctor and assignment should be private
  PlayLoto(const PlayLoto&);
  PlayLoto& operator=(const PlayLoto&);
 
public:

  //this is a singleton
  static PlayLoto* Instance();

  virtual void Enter(Drunkard* Drunkard);

  virtual void Execute(Drunkard* Drunkard);

  virtual void Exit(Drunkard* Drunkard);

  virtual bool OnMessage(Drunkard* agent, const Telegram& msg);
};




#endif