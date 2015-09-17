#ifndef MESSAGE_TYPES
#define MESSAGE_TYPES

#include <string>
#include "MinersWife.h"

enum message_type
{
  Msg_HiHoneyImHome,
  Msg_StewReady,
  Msg_Insult
};


inline std::string MsgToStr(int msg)
{
  switch (msg)
  {
  case Msg_HiHoneyImHome:
    
    return "HiHoneyImHome"; 

  case Msg_StewReady:
    
    return "StewReady";

  case Msg_Insult:

	  switch(RandInt(0,2))
	  {
	  case 0:
		  
		  return "Your mama so fat, she curves space and time !";
	  
	  case 1:
			
		  return "Your mama so fat, she blocks the WiFi signal!";
	  
	  case 2:
			
		  return "Your mama so fat, she stands on 2 times zones!";
	  }


  default:

    return "Not recognized!";
  }
}

#endif