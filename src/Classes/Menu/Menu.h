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
	sf::String mContent;
	std::function<void()> mCallback;
	Vector2* pos;
	MenuItem(float x, float y, sf::String content, std::function<void()> callback)
	{
		pos = new Vector2(x, y);
		mContent = content;
		mCallback = callback;
	}
	MenuItem(sf::String content, std::function<void()> callback)
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
	sf::String mTitle;
	bool hasTitle = false;
	sf::Texture texture;
	sf::Sprite sprite;

	std::string imageSource = "content/dinosaur.png";
	MenuScreen(sf::String title, float width, float height, std::string src, std::vector<MenuItem*> items)
	{
		imageSource = src;
		dim = new Vector2(width, height);
		texture.loadFromFile(imageSource);
		sprite.setTexture(texture);
		float scaleX = width / texture.getSize().x;
		float scaleY = height / texture.getSize().y;
		sprite.setScale(sf::Vector2f(scaleX, scaleY));
		mTitle = title;
		hasTitle = true;
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
	void draw(SFMLWindow* window) {
		window->drawSprite(sprite, 0, 0);
		window->drawText(50, 50, mTitle, sf::Color::White, 50);
		int selectionIndex = 0;
		for (auto& menuItem : menuItems)
		{
			if (index == selectionIndex)
			{
				window->drawText(menuItem->pos->x, menuItem->pos->y, menuItem->mContent, sf::Color::Red, 29);
			}
			else
			{
				window->drawText(menuItem->pos->x, menuItem->pos->y, menuItem->mContent, sf::Color::White, 29);
			}
			selectionIndex++;
		}
	}
};
#endif
#ifndef __Menu_H_INCLUDED__ // if Node.h hasn't been included yet...
#define __Menu_H_INCLUDED_

class Menu
{
public:
	std::vector<MenuScreen*> menuArray;
	unsigned int menuIndex;
	bool isOpened = false;
	int counter = 0;
	Menu(std::vector<MenuScreen*> menus)
	{
		menuArray = menus;
	}
	void tick(SFMLWindow* window)
	{
		update();
		draw(window);
	}

	void openMenu(int index) {
		if (!isOpened)
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
			isOpened = true;
		}

	}
	void close()
	{
		isOpened = false;
	}

	void update()
	{
		if (counter > 0)
		{
			counter--;
		};
	}
	void draw(SFMLWindow* window) {
		window->clear();
		menuArray[menuIndex]->draw(window);
		window->display();
	}
	void moveIndex(int index) {
		if (counter == 0) {
			menuArray[menuIndex]->changeIndex(index);
			counter = 10;
		}
	}
	void confirm() {
		if (counter == 0) {
			menuArray[menuIndex]->activate();
			counter = 10;
		}
	}
};

#endif