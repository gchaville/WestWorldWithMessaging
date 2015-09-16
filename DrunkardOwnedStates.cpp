#include "DrunkardOwnedStates.h"
#include "fsm/State.h"
#include "Drunkard.h"
#include "Locations.h"
#include "messaging/Telegram.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "Time/CrudeTimer.h"
#include "EntityNames.h"

#include <iostream>
using std::cout;


#ifdef TEXTOUTPUT
#include <fstream>
extern std::ofstream os;
#define cout os
#endif


//------------------------------------------------------------------------methods for EnterSaloonAndGetSmashed
EnterSaloonAndGetSmashed* EnterSaloonAndGetSmashed::Instance()
{
  static EnterSaloonAndGetSmashed instance;

  return &instance;
}


void EnterSaloonAndGetSmashed::Enter(Drunkard* pDrunkard)
{
  //if the Drunkard is not already located at the goldmine, he must
  //change location to the gold mine
  if (pDrunkard->Location() != saloon)
  {
    cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " << "Walkin' to the saloon";

    pDrunkard->ChangeLocation(goldmine);
  }
}


void EnterSaloonAndGetSmashed::Execute(Drunkard* pDrunkard)
{  
  //Now the Drunkard is at the goldmine he digs for gold until he
  //is carrying in excess of MaxNuggets. If he gets thirsty during
  //his digging he packs up work for a while and changes state to
  //gp to the saloon for a whiskey.
  pDrunkard->BuyAndDrinkAWhiskey();

  pDrunkard->IncreaseDrunkenness();

  cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " << "That's mighty fine sippin' liquer";

  //if enough gold mined, go and put it in the bank
  if (pDrunkard->PocketsEmpty())
  {
    pDrunkard->GetFSM()->ChangeState(GoHomeAndSoberUpTilRested::Instance());
  }

  if (pDrunkard->Drunk())
  {
    pDrunkard->GetFSM()->ChangeState(GoHomeAndSoberUpTilRested::Instance());
  }
}


void EnterSaloonAndGetSmashed::Exit(Drunkard* pDrunkard)
{
  cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " 
       << "Ah'm leavin' the saloon with mah liver full o' sweet water";

  cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " 
       << "Alcohol kills!!! Yes I agree, the alcohol kills the germs o' mah body...";
}


bool EnterSaloonAndGetSmashed::OnMessage(Drunkard* pDrunkard, const Telegram& msg)
{
  //send msg to global message handler
  return false;
}

//------------------------------------------------------------------------methods for VisitBankAndDepositGoldLoto

VisitBankAndDepositGoldLoto* VisitBankAndDepositGoldLoto::Instance()
{
  static VisitBankAndDepositGoldLoto instance;

  return &instance;
}

void VisitBankAndDepositGoldLoto::Enter(Drunkard* pDrunkard)
{  
  //on entry the Drunkard makes sure he is located at the bank
  if (pDrunkard->Location() != bank)
  {
    cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " << "Goin' to the bank. Yes siree";

    pDrunkard->ChangeLocation(bank);
  }
}


void VisitBankAndDepositGoldLoto::Execute(Drunkard* pDrunkard)
{
  //deposit the gold
  pDrunkard->AddToWealth(pDrunkard->GoldEarned());
    
  pDrunkard->SetGoldEarned(0);

  cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " 
       << "Depositing gold. Total savings now: "<< pDrunkard->Wealth();

  //wealthy enough to have a well spend rest?
  if (pDrunkard->Wealth() <= 0)
  {
    cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " 
         << "Woow! Drink enough for now. Back home to mah bed";
      
    pDrunkard->GetFSM()->ChangeState(GoHomeAndSoberUpTilRested::Instance());      
  }

  //otherwise spend more gold
  else 
  {
    switch(RandInt(0,1)) 
	 {
	 case 0: 
		
		 pDrunkard->GetFSM()->ChangeState(EnterSaloonAndGetSmashed::Instance());
		
		 break;

	 case 1:

		 pDrunkard->GetFSM()->ChangeState(PlayLoto::Instance());
		
		 break;
	 }
  }
}


void VisitBankAndDepositGoldLoto::Exit(Drunkard* pDrunkard)
{
  cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " << "Leavin' the bank";
}


bool VisitBankAndDepositGoldLoto::OnMessage(Drunkard* pDrunkard, const Telegram& msg)
{
  //send msg to global message handler
  return false;
}
//------------------------------------------------------------------------methods for GoHomeAndSoberUpTilRested

GoHomeAndSoberUpTilRested* GoHomeAndSoberUpTilRested::Instance()
{
  static GoHomeAndSoberUpTilRested instance;

  return &instance;
}

void GoHomeAndSoberUpTilRested::Enter(Drunkard* pDrunkard)
{
  if (pDrunkard->Location() != shack)
  {
    cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " << "Walkin' home";

    pDrunkard->ChangeLocation(shack); 

    /*let the wife know I'm home
    Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
                              pDrunkard->ID(),        //ID of sender
                              ent_Elsa,            //ID of recipient
                              Msg_HiHoneyImHome,   //the message
                              NO_ADDITIONAL_INFO);    */
  }
}

void GoHomeAndSoberUpTilRested::Execute(Drunkard* pDrunkard)
{ 
  //if Drunkard is not fatigued start to dig for nuggets again.
  if (!pDrunkard->Drunk())
  {
     cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " 
          << "All mah drunkenness has drained away. Time to get smashed!";

	 switch(RandInt(0,1)) 
	 {
	 case 0: 
		
		 pDrunkard->GetFSM()->ChangeState(EnterSaloonAndGetSmashed::Instance());
		
		 break;

	 case 1:

		 pDrunkard->GetFSM()->ChangeState(PlayLoto::Instance());
		
		 break;
	 }
  }

  else 
  {
    //sleep
    do 
	{
		pDrunkard->DecreaseDrunkenness();
		cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " << "ZZZZ... ";
	}
	while (pDrunkard->Drunkenness() <= 0);
  } 

  //if Drunkard hasn't got enough money
  if (pDrunkard->PocketsEmpty())
    pDrunkard->SetWealth(10);
}

void GoHomeAndSoberUpTilRested::Exit(Drunkard* pDrunkard)
{ 
}


bool GoHomeAndSoberUpTilRested::OnMessage(Drunkard* pDrunkard, const Telegram& msg)
{
   SetTextColor(BACKGROUND_RED|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);

   /*switch(msg.Msg)
   {
   case Msg_StewReady:

     cout << "\nMessage handled by " << GetNameOfEntity(pDrunkard->ID()) 
     << " at time: " << Clock->GetCurrentTime();

     SetTextColor(FOREGROUND_RED|FOREGROUND_INTENSITY);

     cout << "\n" << GetNameOfEntity(pDrunkard->ID()) 
          << ": Okay Hun, ahm a comin'!";

     pDrunkard->GetFSM()->ChangeState(EatStew::Instance());
      
     return true;

   }//end switch*/

   return false; //send message to global message handler
}

//------------------------------------------------------------------------PlayLoto

PlayLoto* PlayLoto::Instance()
{
  static PlayLoto instance;

  return &instance;
}

void PlayLoto::Enter(Drunkard* pDrunkard)
{
  if (pDrunkard->Location() != saloon)
  {    
    pDrunkard->ChangeLocation(saloon);

    cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " << "Boy, ah sure is lucky! Walking to the saloon";
  }
}

void PlayLoto::Execute(Drunkard* pDrunkard)
{
  pDrunkard->PlayLoto();

  pDrunkard->AddToGoldEarned(RandInt(0,6));

  cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " << "I coulda be rich today";
  
  if (!pDrunkard->EarnMoney())
	  pDrunkard->GetFSM()->ChangeState(EnterSaloonAndGetSmashed::Instance());  
  else
	  pDrunkard->GetFSM()->ChangeState(VisitBankAndDepositGoldLoto::Instance());  
}


void PlayLoto::Exit(Drunkard* pDrunkard)
{ 
  if (pDrunkard->EarnMoney())
    cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " << "Leaving the loto, feelin' good";
  else
    cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " << "Leaving the loto, unlucky day";

}


bool PlayLoto::OnMessage(Drunkard* pDrunkard, const Telegram& msg)
{
  //send msg to global message handler
  return false;
}
