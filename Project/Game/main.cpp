#include "IntegrationLibrary.h"

#include "Game_Manager.h"


enum class mainstate
{
    Title,
	MainMenu,
    mainPlay,
    Playing,
    Paused,
	Exit
    //mainOver
};
mainstate currentState = mainstate::Title;



int main()
{
    Game_Manager game_manager;
    game_manager.run();
    return 0;
}