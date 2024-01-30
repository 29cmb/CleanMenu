#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include "cocos2d.h"
using namespace geode::prelude;

class $modify(LinkHandlerModification, MenuLayer) {
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

		auto redditSprite = CCSprite::create("reddit-button.png"_spr);
		auto menuItem = CCMenuItemSpriteExtra::create(redditSprite, nullptr, this, menu_selector(LinkHandlerModification::redditOpen));
	
		menuItem->setPosition(115,33);
		menuItem->setRotation(-90);
		menuItem->setContentSize(CCSize(31.5,31.5));
		menuItem->setID("reddit-button");
		menuItem->setNormalImage(redditSprite);

		redditSprite->setScale(1);

		socials->addChild(menuItem);
		bool hideMoreGames = Mod::get()->getSettingValue<bool>("hideMoreGames");
		bool revertAccountPosition = Mod::get()->getSettingValue<bool>("revertProfileButton");
		auto robtoplogo = socials->getChildByID("robtop-logo-button");
		if (robtoplogo) {
			robtoplogo->setPosition(-198,31);
		}

		auto bottomMenu = this->getChildByID("bottom-menu");
		if (bottomMenu) {
			bottomMenu->setPositionY(58);
		}

		auto account = this->getChildByID("profile-menu");
		bool robtopLogoHide = Mod::get()->getSettingValue<bool>("hideRobtopLogo");
		auto accbtn = account->getChildByID("profile-button");

		float accBtnSetting = Mod::get()->getSettingValue<double>("whichSideProfileButton");
		auto username = this->getChildByID("player-username");
		if(account && !revertAccountPosition){
			if(accBtnSetting == 0 && robtopLogoHide == true){
				// Reset in order to attempt to fix icon account button
				accbtn->setPosition(27.5,29);
				accbtn->setContentSize(CCSize(55,58));
				username->setPosition(93,12);

				account->setPosition(77,30);
			} else if(accBtnSetting == 1 && hideMoreGames == true){
				// Reset in order to attempt to fix icon account button
				accbtn->setPosition(27.5,29);
				accbtn->setContentSize(CCSize(55,58));

				account->setPosition(587,30);
				username->setPosition(479,12);
			}
		}

		// other settings
		
		auto logo = socials->getChildByID("robtop-logo-button");
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

	void redditOpen(CCObject* pSender) {
        cocos2d::CCApplication::sharedApplication()->openURL("https://www.reddit.com/r/geometrydash/");
    }

};

