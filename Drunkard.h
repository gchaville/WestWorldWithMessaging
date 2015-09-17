#ifndef DRUNKARD_H
#define DRUNKARD_H
//------------------------------------------------------------------------
//
//  Name:   Drunkard.h
//
//  Desc:   A class defining a bar-drunkard.
//
//  Author: Gillian Chaville
//
//------------------------------------------------------------------------
#include <string>
#include <cassert>
#include <iostream>

#include "BaseGameEntity.h"
#include "Locations.h"
#include "misc/ConsoleUtils.h"
#include "DrunkardOwnedStates.h"
#include "fsm/StateMachine.h"
#include "misc/Utils.h"
#include "Miner.h"

template <class entity_type> class State;
struct Telegram;

//above this value a drunkard is too drunk
const int AlcoholLevel = 5;
//above this value a drunkard can provoke a fight
const int FightLevel	  = 3;
//the amount of gold a drunkard must spend before he feels he can go home to sober up
const int MoneySpent	 = 10;

class Drunkard : public BaseGameEntity
{
private:
	//an instance of the state machine class
	StateMachine<Drunkard>*  m_pStateMachine;

	location_type         m_Location;

	//how many gold the Drunkard earned and has in his pockets
	int                   m_iGoldEarned;

	int                   m_iMoneyInBank;

	//the higher the value, the more drunk the Drunkard
	int                   m_iAlcohol;

public:

	Drunkard(int id):m_Location(saloon),
	                      m_iGoldEarned(0),
	                      m_iMoneyInBank(10),
	                      m_iAlcohol(0),
	                      BaseGameEntity(id)
	                           
	{
	//set up state machine
	m_pStateMachine = new StateMachine<Drunkard>(this);

	m_pStateMachine->SetCurrentState(GoHomeAndSoberUpTilRested::Instance());

	/* NOTE, A GLOBAL STATE HAS NOT BEEN IMPLEMENTED FOR THE Drunkard */
	}

	~Drunkard(){delete m_pStateMachine;}

	//this must be implemented
	void Update();

	//so must this
	virtual bool  HandleMessage(const Telegram& msg);


	StateMachine<Drunkard>* GetFSM()const{return m_pStateMachine;}



	//-------------------------------------------------------------accessors
	location_type Location()const{return m_Location;}
	void          ChangeLocation(location_type loc){m_Location=loc;}

	int           GoldEarned()const{return m_iGoldEarned;}
	void          SetGoldEarned(int val){m_iGoldEarned = val;}
	void          AddToGoldEarned(int val);
	bool          PocketsEmpty()const{return m_iMoneyInBank <= 0;}

	bool          Drunk()const;
	int			  Drunkenness()const{return m_iAlcohol;}
	void          DecreaseDrunkenness(){m_iAlcohol -= 1;}
	void          IncreaseDrunkenness(){m_iAlcohol += 1;}
	void          BuyAndDrinkAWhiskey(){m_iMoneyInBank-=2;}

	int           Wealth()const{return m_iMoneyInBank;}
	void          SetWealth(int val){m_iMoneyInBank = val;}
	void          AddToWealth(int val);

	void		  PlayLoto(){m_iMoneyInBank-=2;}
	bool 		  EarnMoney()const{return m_iGoldEarned >= 0;}
};



#endif

