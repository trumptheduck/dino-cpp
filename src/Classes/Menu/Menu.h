#include "Classes/Clock/Clock.h"
#include "Classes/SFMLWindow/SFMLWindow.h"
#include "Classes/Vector2/Vector2.h"

#ifndef __MenuItem_H_INCLUDED__ // if Node.h hasn't been included yet...
#define __MenuItem_H_INCLUDED_

class MenuItem
{
public:
	static std::vector<MenuItem*> generateItemList(std::vector<MenuItem*> list, int x, int y, int interval)
	{
		std::vector<MenuItem*> result;
		int fIndex = 0;
		for (auto& item : list)
		{
			result.push_back(new MenuItem(x, y + fIndex * interval, item->mContent, item->mCallback));
			fIndex++;
		}
		return result;
	}
	std::string mContent;
	std::function<void()> mCallback;
	Vector2* pos;
	MenuItem(float x, float y, std::string content, std::function<void()> callback)
	{
		pos = new Vector2(x, y);
		mContent = content;
		mCallback = callback;
	}
	MenuItem(std::string content, std::function<void()> callback)
	{
		pos = new Vector2(0, 0);
		mContent = content;
		mCallback = callback;
	}
	void activate()
	{
		mCallback();
	}
};
class MenuScreen
{
public:
	Vector2* dim;
	std::vector<MenuItem*> menuItems;
	int index = 0;
	std::string mTitle;
	bool hasTitle = false;
	MenuScreen(std::vector<MenuItem*> items, float width, float height, std::string title)
	{
		dim = new Vector2(width, height);
		mTitle = title;
		hasTitle = true;
		menuItems = items;
	}
	MenuScreen(std::vector<MenuItem*> items, float width, float height)
	{
		dim = new Vector2(width, height);
		menuItems = items;
	}
	void changeIndex(int amount)
	{
		if (index + amount < 0)
		{
			index = 0;
		}
		else if (index + amount > (int)menuItems.size() - 1)
		{
			index = menuItems.size() - 1;
		}
		else
		{
			index += amount;
		}
	}
	void activate() {
		menuItems[index]->activate();
	}
};
#endif
#ifndef __Menu_H_INCLUDED__ // if Node.h hasn't been included yet...
#define __Menu_H_INCLUDED_

class Menu
{
public:
	SFMLWindow* window = new SFMLWindow(new Vector2(1, 1));
	std::vector<MenuScreen*> menuArray;
	unsigned int menuIndex;
	int counter = 0;
	Menu()
	{
		menuArray.push_back(new MenuScreen(MenuItem::generateItemList({
		new MenuItem("StartGame", [&] {
			close();
		}),
		new MenuItem("Options", [&] {
			close();
		}),
			}, 100, 100, 50), 1024, 768, "Main Menu"));
		close();
	}
	void tick()
	{
		if (window->window.isOpen())
		{
			update();
			window->poolEvents();
			window->clear();
			int selectionIndex = 0;
			for (auto& menuItem : menuArray[menuIndex]->menuItems)
			{
				if (menuArray[menuIndex]->index == selectionIndex)
				{
					window->drawText(menuItem->pos->x, menuItem->pos->y, menuItem->mContent, sf::Color::Red, 29);
				}
				else
				{
					window->drawText(menuItem->pos->x, menuItem->pos->y, menuItem->mContent, sf::Color::White, 29);
				}
				selectionIndex++;
			}

			window->display();
		}
	}

	void openWindow(int index) {
		if (!window->window.isOpen())
		{
			if (index < 0)
			{
				menuIndex = 0;
			}
			else if (index > (int)menuArray.size() - 1)
			{
				menuIndex = menuArray.size() - 1;
			}
			else
			{
				menuIndex = index;
			}

			if (menuArray[menuIndex]->hasTitle) {
				window = new SFMLWindow(new Vector2(menuArray[menuIndex]->dim->x, menuArray[menuIndex]->dim->y), menuArray[menuIndex]->mTitle);
			}
			else {
				window = new SFMLWindow(new Vector2(menuArray[menuIndex]->dim->x, menuArray[menuIndex]->dim->y));
			}

		}
	}
	void close()
	{
		if (window->window.isOpen())
		{
			window->window.close();
		}
	}

	void update()
	{
		if (counter > 0)
		{
			counter--;
		};
		if (counter == 0)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				menuArray[menuIndex]->changeIndex(-1);
				counter = 10;
			}
			//Kiểm tra nếu người chơi ấn shift
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				menuArray[menuIndex]->changeIndex(1);
				counter = 10;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			{
				menuArray[menuIndex]->activate();
				counter = 10;
			}
		}
	}
};

#endif