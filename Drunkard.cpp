#include "Drunkard.h"

bool Drunkard::HandleMessage(const Telegram& msg)
{
  return m_pStateMachine->HandleMessage(msg);
}


void Drunkard::Update()
{
  SetTextColor(FOREGROUND_BLUE| FOREGROUND_INTENSITY);

  //m_iThirst += 1;
  
  m_pStateMachine->Update();
}



void Drunkard::AddToGoldEarned(const int val)
{
  m_iGoldEarned += val;

  if (m_iGoldEarned < 0) m_iGoldEarned = 0;
}

void Drunkard::AddToWealth(const int val)
{
  m_iMoneyInBank += val;

  if (m_iMoneyInBank < 0) m_iMoneyInBank = 0;
}

bool Drunkard::Drunk()const
{
  if (m_iAlcohol > AlcoholLevel){return true;}

  return false;
}

