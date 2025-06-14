#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/CreatorLayer.hpp>
#include "cocos2d.h"
#include <Geode/modify/LevelSearchLayer.hpp>
#include <Geode/modify/ProfilePage.hpp>
#include <Geode/modify/GJGarageLayer.hpp>
#include <Geode/ui/Layout.hpp>
#include <Geode/loader/Loader.hpp>

using namespace geode::prelude;
namespace
{
	std::map<std::string, std::vector<std::string>> incompatibilities = {
		{"CreatorLayer", {"xanii.super_expert", "minemaker0430.gddp_integration", "alphalaneous.vanilla_pages"}}
	};

	bool incompatibleModsLoaded(const std::string& key)
	{
		bool isLoaded = false;
		if (incompatibilities.contains(key))
		{
			for (const auto &mod : incompatibilities[key])
			{
				if (Loader::get()->isModLoaded(mod))
				{
					isLoaded = true;
					break;
				}
			}
		}

		return isLoaded;
	}
}

class $modify(LinkHandler, MenuLayer) {
	bool init() {
		if (!MenuLayer::init()) return false;
		auto winSize = CCDirector::get()->getWinSize();
		
		auto socials = getChildByID("social-media-menu");
		if (!socials) return true;
		
		socials->setAnchorPoint(CCPoint(0.5, 0.5));
		socials->setScale(1.5);
		socials->setPosition((winSize.width / 2.0), 19);
		socials->setLayout(SimpleAxisLayout::create(Axis::Row));

		//reddit button!!!!!

		CCSprite* redditSprite = CCSprite::create("reddit-button.png"_spr);
		CCMenuItemSpriteExtra* menuItem = CCMenuItemSpriteExtra::create(redditSprite, nullptr, this, menu_selector(LinkHandler::redditOpen));
	
		// menuItem->setPosition(109,32);
		menuItem->setRotation(-90);
		menuItem->setContentSize(CCSize(25.5,25.5));
		menuItem->setID("reddit-button");
		menuItem->setNormalImage(redditSprite);

		redditSprite->setScale(0.975);
		socials->addChild(menuItem);
		socials->updateLayout();

		bool hideMoreGames = Mod::get()->getSettingValue<bool>("hideMoreGames");
		bool revertAccountPosition = Mod::get()->getSettingValue<bool>("revertProfileButton");

		bool robtopLogoHide = Mod::get()->getSettingValue<bool>("hideRobtopLogo");
		auto robtopLogo = socials->getChildByID("robtop-logo-button");

		if(robtopLogo) {
			if(robtopLogoHide == false) {
				// Recreate the logo in order to seperate it from the social icons
				CCSprite* rtlSprite = CCSprite::createWithSpriteFrameName("robtoplogo_small.png");
				rtlSprite->setContentSize(CCSize(100, 28));
				rtlSprite->setScale(0.8);

				CCMenuItemSpriteExtra* rtlButton = CCMenuItemSpriteExtra::create(rtlSprite, nullptr, this, menu_selector(LinkHandler::robtopOpen));
				rtlButton->setID("cm-robtop-logo-replacement");
				rtlButton->setAnchorPoint(CCPoint(0,0));
				rtlButton->m_scaleMultiplier = 1.15;
				
				CCMenu* rtlContainer = CCMenu::create();
				rtlContainer->setPosition(10, 10);
				rtlContainer->setContentSize(CCSize(80, 22.4));
				rtlContainer->setAnchorPoint(CCPoint(0,0));
				rtlContainer->setID("cm-robtop-logo-container");

				rtlContainer->addChild(rtlButton);
				this->addChild(rtlContainer);
			}

			robtopLogo->setContentSize(CCSize(0,0));
			robtopLogo->setVisible(false);
			socials->updateLayout();
		}

		auto account = getChildByID("profile-menu");
		float accBtnSetting = Mod::get()->getSettingValue<double>("whichSideProfileButton");
		auto username = getChildByID("player-username");

		if(
			account 
			&& !revertAccountPosition
			&& !(accBtnSetting == 1 && hideMoreGames == false)
			&& !(accBtnSetting == 0 && robtopLogoHide == false)
		) {
			account->setContentSize(CCSize(56, 56));
			account->setAnchorPoint(CCPoint(accBtnSetting,0));
			account->setPosition(accBtnSetting == 1 ? winSize.width : 0, 0);

			auto accountButton = account->getChildByID("profile-button");
			accountButton->setPosition(accBtnSetting == 1 ? 55 : 0, 0);
			accountButton->setAnchorPoint(CCPoint(accBtnSetting, 0));

			username->setPosition(accBtnSetting == 1  ? (winSize.width - 60) : 60, 24);
			username->setAnchorPoint(CCPoint(accBtnSetting, 0));
		}

		// auto logo = socials->getChildByID("robtop-logo-button");
		// if (logo) {
		// 	logo->setVisible(!robtopLogoHide);
		// }

		bool socialsHide = Mod::get()->getSettingValue<bool>("hideSocials");
		if (auto sm2 = getChildByID("social-media-menu")) {
			sm2->setVisible(!socialsHide);
			if (socialsHide == false) {
				auto bottomMenu = getChildByID("bottom-menu");
				if (bottomMenu) {
					bottomMenu->setPositionY(58);
				}
			}
		}
	
		if (auto moreGames = getChildByID("more-games-menu")) {
			moreGames->setVisible(!hideMoreGames);
		}

		return true;
	}

	void redditOpen(CCObject* pSender) {
		cocos2d::CCApplication::sharedApplication()->openURL("https://www.reddit.com/r/geometrydash/");
	}

	void robtopOpen(CCObject* pSender) {
		cocos2d::CCApplication::sharedApplication()->openURL("https://robtopgames.com");	
	}
};

class $modify(CreatorLayer) {
	bool init() {
		if (!CreatorLayer::init()) return false;
		const auto buttons = getChildByID("creator-buttons-menu");
		const auto revert = Mod::get()->getSettingValue<bool>("revertCreatorPageChanges");
		if (buttons && !revert && !incompatibleModsLoaded("CreatorLayer")) {
			const auto featured = buttons->getChildByID("featured-button");
			const auto lists = buttons->getChildByID("lists-button");
			const auto paths = buttons->getChildByID("paths-button");
			const auto mappacks = buttons->getChildByID("map-packs-button");
			const auto search = buttons->getChildByID("search-button");
			const auto map = buttons->getChildByID("map-button");
			const auto daily = buttons->getChildByID("daily-button");
			const auto weekly = buttons->getChildByID("weekly-button");
			const auto event = buttons->getChildByID("event-button");
			const auto gauntlets = buttons->getChildByID("gauntlets-button");
			const auto create = buttons->getChildByID("create-button");
			const auto saved = buttons->getChildByID("saved-button");
			const auto scores = buttons->getChildByID("scores-button");
			const auto quests = buttons->getChildByID("quests-button");
			const auto versus = buttons->getChildByID("versus-button");

			buttons->setLayout(nullptr);

			auto lowerButtons = CCMenu::create();
			lowerButtons->setID("lower-buttons-menu");
			lowerButtons->setContentSize(CCSize(496, 82));
			lowerButtons->setPosition(223.5, 122);
			buttons->addChild(lowerButtons);

			auto upperButtons = CCMenu::create();
			upperButtons->setID("upper-buttons-menu");
			upperButtons->setContentSize(CCSize(450, 83.6));
			upperButtons->setPosition(224.5, 196);
			buttons->addChild(upperButtons);

			lowerButtons->setLayout(RowLayout::create()->setGap(7.5)->setAxisAlignment(AxisAlignment::Center));
			upperButtons->setLayout(RowLayout::create()->setGap(0.5)->setAxisAlignment(AxisAlignment::Center));

			// all small buttons have the same size properties, but different positions. This just saves lines
			std::vector<CCNode*> smallButtons = {featured, paths, mappacks, daily, weekly, event, gauntlets, scores, quests};
			std::vector<CCNode*> upperButtonsList = {create, saved, lists, search};

			for (const auto &button : smallButtons) {
				if (button) {
					button->removeFromParent();

					if (auto sprite = typeinfo_cast<CCSprite*>(button->getChildren()->objectAtIndex(0))) {
						sprite->setScale(0.55);
						sprite->setAnchorPoint(CCPoint(.8,.8));
						button->setContentSize(CCSize(50,50));
					}

					lowerButtons->addChild(button);
				}
			}

			for (const auto &button : upperButtonsList) {
				if (button) {
					button->removeFromParent();
					upperButtons->addChild(button);
				}
			}

			lowerButtons->updateLayout();
			upperButtons->updateLayout();

			if (versus) versus->setVisible(false);
			if (map) map->setVisible(false);
		}
		return true;
	}
};

class $modify(LevelSearchLayer) {
	bool init(int p1) {
		if (!LevelSearchLayer::init(p1)) return false;

		const auto dontdochanges = Mod::get()->getSettingValue<bool>("revertSearchPageChanges");

		if (!dontdochanges) {
			const auto filtersTitle = getChildByID("filters-title");
			const auto quickSearchTitle = getChildByID("quick-search-title");

			if (filtersTitle) filtersTitle->setVisible(false);
			if (quickSearchTitle) quickSearchTitle->setVisible(false);

			const auto quickSearch = getChildByID("quick-search-menu");
			const auto quickSearchBg = getChildByID("quick-search-bg");

			quickSearch->setPositionY(145);
			quickSearchBg->setPositionY(173);

			const auto levelSearchBg = getChildByID("level-search-bg");
			levelSearchBg->setContentSize(CCSize(365, 72));
			levelSearchBg->setPositionY(274);

			const auto searchMenu = getChildByID("search-button-menu");
			const auto searchButton = searchMenu->getChildByID("search-level-button");
			const auto userSearchButton = searchMenu->getChildByID("search-user-button");

			if (searchButton) searchButton->setVisible(false);
			
			if (userSearchButton) userSearchButton->setVisible(false);

			const auto largeSearchButtonCreate = CCSprite::create("search_long_button.png"_spr);
			const auto sButton = CCMenuItemSpriteExtra::create(largeSearchButtonCreate, nullptr, this, menu_selector(LevelSearchLayer::onSearch));
			const auto label1 = CCLabelBMFont::create("Search Levels", "bigFont.fnt");

			label1->setScale(0.4);
			label1->setPosition(78, 14);
			sButton->addChild(label1);

			sButton->setPosition(-91, 96);
			sButton->setID("cleanerMenu-search-level-button");
			largeSearchButtonCreate->setScale(1.2);

			searchMenu->addChild(sButton);

			const auto largeSearchUserButtonCreate = CCSprite::create("usersearch_long_button.png"_spr);
			const auto sButton2 = CCMenuItemSpriteExtra::create(largeSearchUserButtonCreate, nullptr, this, menu_selector(LevelSearchLayer::onSearchUser));
			const auto label2 = CCLabelBMFont::create("Search Users", "bigFont.fnt");

			label2->setScale(0.4);
			label2->setPosition(83, 14);

			sButton2->addChild(label2);

			sButton2->setID("cleanerMenu-search-user-button");
			sButton2->setPosition(88, 96);
			largeSearchUserButtonCreate->setScale(1.2);
			
			searchMenu->addChild(sButton2);

			const auto barbg = getChildByID("level-search-bar-bg");
			barbg->setPosition((CCDirector::get()->getWinSize().width / 2.f) - (getChildByIDRecursive("clear-search-button")->getContentWidth() / 2.f) - 2.5f, 290);
			barbg->setScale(1.475, 1);

			if (const auto searchBar = typeinfo_cast<CCTextInputNode*>(getChildByID("search-bar"))) {
				searchBar->setContentSize(CCSize(306, 50));
				if (const auto textField = typeinfo_cast<CCTextFieldTTF*>(searchBar->getChildren()->objectAtIndex(0))){
					textField->setContentSize(CCSize(306, 26.75));
				}
			}
		}
		return true;
	}	
};

class $modify(ProfilePage) {
	void loadPageFromUserInfo(GJUserScore* a2) {
		ProfilePage::loadPageFromUserInfo(a2);

		const auto dontdochanges = Mod::get()->getSettingValue<bool>("revertProfileChanges");
		const auto mainLayer = typeinfo_cast<CCLayer*>(getChildren()->objectAtIndex(0));
		if (mainLayer && !dontdochanges)  {
			const auto mainProfileMenu = mainLayer->getChildByID("main-menu");

			const auto commentButton = mainProfileMenu->getChildByID("comment-button");
			const auto historyButton = mainProfileMenu->getChildByID("comment-history-button");

			const auto cvoltonUsernameButton = mainProfileMenu->getChildByID("cvolton.betterinfo/username-button");
			const auto geodeContributionsBadge = mainProfileMenu->getChildByID("geode-badge");

			if (commentButton) {
				const auto sprite = typeinfo_cast<CCSprite*>(commentButton->getChildren()->objectAtIndex(0));
				if (sprite) {
					sprite->setScale(0.8);
					commentButton->setPosition(378, -232);
				}
			}

			if (historyButton) historyButton->setPosition(378, -141);
			if (m_leftArrow) m_leftArrow->setPositionX(34);
			if (m_rightArrow) m_rightArrow->setPositionX(386);

			if (const auto bottomMenu = mainLayer->getChildByID("bottom-menu")) {
				bottomMenu->setLayout(
				RowLayout::create()
					->setGap(0.f)
					->setGrowCrossAxis(true)
					->setAxisAlignment(AxisAlignment::Center)
				);
				bottomMenu->updateLayout();
			}
		}
	}
};

class $modify(GJGarageLayer) {
	bool init() {
		if (!GJGarageLayer::init()) return false;

		const auto dontdochanges = Mod::get()->getSettingValue<bool>("revertIconKitChanges");

		if (!dontdochanges) {
			const auto shardsMenu = getChildByID("shards-menu");
			const auto colorButton = shardsMenu->getChildByID("color-button");
			if (colorButton) colorButton->setPosition(473.25, -12.5);
		}
		return true;
	}
};
