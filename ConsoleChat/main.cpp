#include "Chat.h"

int main()
{
	Chat chat;

	chat.start();

	chat.startMessage();

	while (chat.chatStart())
	{
		chat.mainMenu();

		while (chat.getCurrentUser())
		{
			chat.userMenu();
		}
	}
	return 0;
}