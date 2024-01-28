#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include "cocos2d.h"
#include "LinkHandler.h" 
using namespace geode::prelude;

class $modify(MenuLayer) {
	bool init(){
		if(!MenuLayer::init()) return false;
		auto socials = this->getChildByID("social-media-menu");

		if (socials) {
			socials->setPosition(242, -15);
		}

		auto discord = socials->getChildByID("discord-button");
		if (discord) {
			discord->setPosition(88, 30);
		}

		//reddit button!!!!!

		LinkHandler* lh = new LinkHandler();
		auto redditSprite = CCSprite::create("reddit-button.png"_spr);
		auto menuItem = CCMenuItemSpriteExtra::create(redditSprite, nullptr, lh, menu_selector(LinkHandler::openLink));
	
		menuItem->setPosition(115,33);
		menuItem->setRotation(-90);
		menuItem->setContentSize(CCSize(31.5,31.5));
		menuItem->setID("reddit-button");
		menuItem->setNormalImage(redditSprite);

		redditSprite->setScale(1);

		

		socials->addChild(menuItem);
		bool hideMoreGames = Mod::get()->getSettingValue<bool>("hideMoreGames");
		auto robtoplogo = socials->getChildByID("robtop-logo-button");
		if (robtoplogo) {
			robtoplogo->setPosition(-198,31);
		}

		auto bottomMenu = this->getChildByID("bottom-menu");
		if (bottomMenu) {
			bottomMenu->setPositionY(58);
		}

		auto account = this->getChildByID("profile-menu");

		auto accbtn = account->getChildByID("profile-button");

		if(account && accbtn && hideMoreGames == true){
			accbtn->setPosition(27.5,29);
			accbtn->setContentSize(CCSize(55,58));
		}

		if(account && hideMoreGames == true){
			account->setPosition(587,30);
		}

		auto username = this->getChildByID("player-username");
		if(username && hideMoreGames == true){
			username->setPosition(479,12);
		}
		//settings
		bool robtopLogoHide = Mod::get()->getSettingValue<bool>("hideRobtopLogo");
		auto logo = this->getChildByID("robtop-logo-button");
		if(logo){
			logo->setVisible(!robtopLogoHide);
		}

		bool socialsHide = Mod::get()->getSettingValue<bool>("hideSocials");
		auto sm2 = this->getChildByID("social-media-menu");
		if(sm2){
			sm2->setVisible(!socialsHide);
		}

		
		auto moreGames = this->getChildByID("more-games-menu");
		if(moreGames){
			moreGames->setVisible(!hideMoreGames);
		}

		return true;
	}
};

