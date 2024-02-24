#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/CreatorLayer.hpp>
#include "cocos2d.h"
#include <Geode/modify/LevelSearchLayer.hpp>
#include <Geode/modify/ProfilePage.hpp>
#include <Geode/modify/GJGarageLayer.hpp>
#include <Geode/cocos/base_nodes/Layout.hpp>

using namespace geode::prelude;

class $modify(LinkHandlerModification, MenuLayer) {
	bool init(){
		if(!MenuLayer::init()) return false;
		auto socials = this->getChildByID("social-media-menu");

		if (socials) {
			socials->setPosition(242, -15);
		}
		auto facebook = socials->getChildByID("facebook-button");
		facebook->setPosition(-21.4, 32);
		auto twitter = socials->getChildByID("twitter-button");
		twitter->setPosition(5.6, 32);
		auto youtube = socials->getChildByID("youtube-button");
		youtube->setPosition(31.5,32);
		auto twitch = socials->getChildByID("twitch-button");
		twitch->setPosition(57.3, 32);
		auto discord = socials->getChildByID("discord-button");
		discord->setPosition(83, 32);
		

		//reddit button!!!!!

		auto redditSprite = CCSprite::create("reddit-button.png"_spr);
		auto menuItem = CCMenuItemSpriteExtra::create(redditSprite, nullptr, this, menu_selector(LinkHandlerModification::redditOpen));
	
		menuItem->setPosition(109,34.5);
		menuItem->setRotation(-90);
		menuItem->setContentSize(CCSize(25.5,25.5));
		menuItem->setID("reddit-button");
		menuItem->setNormalImage(redditSprite);

		redditSprite->setScale(0.975);

		socials->addChild(menuItem);
		bool hideMoreGames = Mod::get()->getSettingValue<bool>("hideMoreGames");
		bool revertAccountPosition = Mod::get()->getSettingValue<bool>("revertProfileButton");
		auto robtoplogo = socials->getChildByID("robtop-logo-button");
		if (robtoplogo) {
			robtoplogo->setPosition(-198,31);
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
			if(socialsHide == false){
				auto bottomMenu = this->getChildByID("bottom-menu");
				if (bottomMenu) {
					bottomMenu->setPositionY(58);
				}
			}
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


class $modify(CreatorLayer){
	bool init(){
		if(!CreatorLayer::init()) return false;
		auto buttons = this->getChildByID("creator-buttons-menu");
		auto revert = Mod::get()->getSettingValue<bool>("revertCreatorPageChanges");
		if(buttons && !revert){
			// buttons is order by index
			auto featured = buttons->getChildByID("featured-button");
			auto lists = buttons->getChildByID("lists-button");
			auto paths = buttons->getChildByID("paths-button");
			auto mappacks = buttons->getChildByID("map-packs-button");
			auto search = buttons->getChildByID("search-button");
			auto map = buttons->getChildByID("map-button");
			auto daily = buttons->getChildByID("daily-button");
			auto weekly = buttons->getChildByID("weekly-button");
			auto event = buttons->getChildByID("event-button");
			auto gauntlets = buttons->getChildByID("gauntlets-button");
			auto create = buttons->getChildByID("create-button");
			auto saved = buttons->getChildByID("saved-button");
			auto scores = buttons->getChildByID("scores-button");
			auto quests = buttons->getChildByID("quests-button");
			auto versus = buttons->getChildByID("versus-button");

			auto smallButtonContentSize = CCSize(50,50);
			auto smallButtonSpriteAnchorPoint = CCPoint(.8,.8);

			// all small buttons have the same size properties, but different positions. This just saves lines
			std::vector<CCNode*> smallButtons = {featured, paths, mappacks, map, daily, weekly, event, gauntlets, scores, quests, versus};

			for (auto &button : smallButtons) {
				if(button){
					auto sprite = dynamic_cast<CCSprite*>(button->getChildren()->objectAtIndex(0));
					if(sprite){
						sprite->setScale(0.55);
						sprite->setAnchorPoint(smallButtonSpriteAnchorPoint);
						button->setContentSize(smallButtonContentSize);
					}
				}
			}

			//move them all
			if(featured) featured->setPosition(17.8, 117);
			
			if(lists) lists->setPosition(268, 215.6);
			
			if(paths) paths->setPosition(253, 117);
			
			if(mappacks) mappacks->setPosition(429, 117);
			
			if(search) search->setPosition(360.2, 215.6);
			
			if(map) map->setPosition(218.9, 155);
			
			if(daily) daily->setPosition(75.5,117);
			
			if(weekly) weekly->setPosition(134,117);
			
			if(gauntlets) gauntlets->setPosition(371.1, 117);
			
			if(create) create->setPosition(86.8, 215.6);
			
			if(saved) saved->setPosition(178.4, 215.6);
			
			if(scores) scores->setPosition(193, 117);
			
			if(quests) quests->setPosition(311.6, 117);

			if(event) event->setVisible(false);
			if(versus) versus->setVisible(false);
			if(map) map->setVisible(false);
		}
		return true;
	}
};

class $modify(LevelSearchLayer){
	bool init(int p1){
		if(!LevelSearchLayer::init(p1)) return false;

		auto dontdochanges = Mod::get()->getSettingValue<bool>("revertSearchPageChanges");

		if(!dontdochanges){
			auto filtersTitle = this->getChildByID("filters-title");
			auto quickSearchTitle = this->getChildByID("quick-search-title");

			if(filtersTitle) filtersTitle->setVisible(false);
			
			if(quickSearchTitle) quickSearchTitle->setVisible(false);
			

			auto quickSearch = this->getChildByID("quick-search-menu");
			auto quickSearchBg = this->getChildByID("quick-search-bg");

			quickSearch->setPositionY(145);
			quickSearchBg->setPositionY(173);

			auto levelSearchBg = this->getChildByID("level-search-bg");
			levelSearchBg->setContentSize(CCSize(365, 72));
			levelSearchBg->setPositionY(274);

			auto searchMenu = this->getChildByID("search-button-menu");
			auto searchButton = searchMenu->getChildByID("search-level-button");
			auto userSearchButton = searchMenu->getChildByID("search-user-button");

			if(searchButton) searchButton->setVisible(false);
			
			if(userSearchButton) userSearchButton->setVisible(false);
			

			auto largeSearchButtonCreate = CCSprite::create("search_long_button.png"_spr);
			auto sButton = CCMenuItemSpriteExtra::create(largeSearchButtonCreate, nullptr, this, menu_selector(LevelSearchLayer::onSearch));
			auto label1 = CCLabelBMFont::create("Search Levels", "bigFont.fnt");

			label1->setScale(0.4);
			label1->setPosition(78, 14);
			sButton->addChild(label1);

			sButton->setPosition(-91, 96);
			sButton->setID("cleanerMenu-search-level-button");
			largeSearchButtonCreate->setScale(1.2);

			searchMenu->addChild(sButton);

			auto largeSearchUserButtonCreate = CCSprite::create("usersearch_long_button.png"_spr);
			auto sButton2 = CCMenuItemSpriteExtra::create(largeSearchUserButtonCreate, nullptr, this, menu_selector(LevelSearchLayer::onSearchUser));
			auto label2 = CCLabelBMFont::create("Search Users", "bigFont.fnt");

			label2->setScale(0.4);
			label2->setPosition(83, 14);

			sButton2->addChild(label2);

			sButton2->setID("cleanerMenu-search-user-button");
			sButton2->setPosition(88, 96);
			largeSearchUserButtonCreate->setScale(1.2);
			
			searchMenu->addChild(sButton2);

			auto barbg = this->getChildByID("level-search-bar-bg");
			barbg->setPosition(262.5, 290);
			barbg->setScale(1.475, 1);
		}
		return true;
	}	
};

class $modify(ProfilePage){
	void loadPageFromUserInfo(GJUserScore* a2){

		ProfilePage::loadPageFromUserInfo(a2);

		auto dontdochanges = Mod::get()->getSettingValue<bool>("revertProfileChanges");
		auto mainLayer = dynamic_cast<CCLayer*>(this->getChildren()->objectAtIndex(0));
		if(mainLayer && !dontdochanges){
			auto mainProfileMenu = mainLayer->getChildByID("main-menu");

			auto commentButton = mainProfileMenu->getChildByID("comment-button");
			auto historyButton = mainProfileMenu->getChildByID("comment-history-button");

			// handle mod-specific exceptions
			auto cvoltonUsernameButton = mainProfileMenu->getChildByID("cvolton.betterinfo/username-button");
			auto geodeContributionsBadge = mainProfileMenu->getChildByID("geode-badge");

			// button repositioning in mainProfileMenu
			if(commentButton){
				auto sprite = dynamic_cast<CCSprite*>(commentButton->getChildren()->objectAtIndex(0));
				if(sprite){
					sprite->setScale(0.8);
					commentButton->setPosition(378, -232);
				}
			}

			if(historyButton) historyButton->setPosition(378, -141);
			if(m_leftArrow) m_leftArrow->setPositionX(34);
			if(m_rightArrow) m_rightArrow->setPositionX(386);

			auto bottomMenu = mainLayer->getChildByID("bottom-menu");
			bottomMenu->setLayout(
				RowLayout::create()
					->setGap(0.f)
					->setGrowCrossAxis(true)
					->setAxisAlignment(AxisAlignment::Center)
				);
			bottomMenu->updateLayout();
			// if(m_ownProfile){
				
			// } else {
			// 	auto messageButton = bottomMenu->getChildByID("message-button");
			// 	auto friendButton = bottomMenu->getChildByID("friend-button");
			// 	auto blockButton = bottomMenu->getChildByID("block-button");

			// 	auto myLevels = bottomMenu->getChildByID("my-levels-button");
			// 	auto myLists =bottomMenu->getChildByID("my-lists-button");

			// 	if(messageButton) messageButton->setPositionX(5.75);
			// 	if(friendButton) friendButton->setPositionX(38);
			// 	if(blockButton) blockButton->setPositionX(70.25);

			// 	if(myLevels) myLevels->setPositionX(280);
			// 	if(myLists) myLists->setPositionX(311);
			// }
				
		}

		// auto socialsMenu = mainLayer->getChildByID("socials-menu");
		// auto youtubeButton = socialsMenu->getChildByID("youtube-button");
		// auto twitterButton = socialsMenu->getChildByID("twitter-button");
		// auto twitchButton = socialsMenu->getChildByID("twitch-button");

		// if(youtubeButton && twitterButton && twitchButton){
		// 	auto youtubeSprite = youtubeButton->getChildren()->objectAtIndex(0);
		// 	auto twitterSprite = twitterButton->getChildren()->objectAtIndex(0);
		// 	auto twitchSprite =  twitchButton->getChildren()->objectAtIndex(0);

		// 	youtubeSprite->setScale(0.75);
		// 	twitterSprite->setScale(0.75);
		// 	twitchSprite->setScale(0.75);

		// 	youtubeButton->setPosition(-17, 105);
		// 	twitterButton->setPosition(-68, 105);
		// 	twitchButton->setPosition(-43, 105);
		// }
		// if(youtubeButton && twitchButton && !twitterButton){
		// 	auto youtubeSprite = youtubeButton->getChildren()->objectAtIndex(0);
		// 	auto twitchSprite =  twitchButton->getChildren()->objectAtIndex(0);


		// 	youtubeSprite->setScale(0.75);
		// 	twitchSprite->setScale(0.75);

		// 	youtubeSprite->setPosition(-30, 105);
		// 	twitchSprite->setPosition(-56, 105);
		// }
		// if(youtubeButton && !twitchButton && !twitterButton){
		// 	auto youtubeSprite = youtubeButton->getChildren()->objectAtIndex(0);

		// 	youtubeSprite->setScale(0.75);
		// 	youtubeSprite->setPosition(-44, 105);
		// }
		// if(youtubeButton && !twitchButton && twitterButton){
		// 	auto youtubeSprite = youtubeButton->getChildren()->objectAtIndex(0);
		// 	auto twitterSprite = twitterButton->getChildren()->objectAtIndex(0);


		// 	youtubeSprite->setScale(0.75);
		// 	twitterSprite->setScale(0.75);

		// 	youtubeSprite->setPosition(-30, 105);
		// 	twitterSprite->setPosition(-56, 105);
		// }
		// if(!youtubeButton && !twitchButton && twitterButton){
		// 	auto twitterSprite = twitterButton->getChildren()->objectAtIndex(0);
		// 	auto twitchSprite =  twitchButton->getChildren()->objectAtIndex(0);


		// 	twitterSprite->setScale(0.75);
		// 	twitterSprite->setPosition(-44, 105);
		// }
	}
};

class $modify(GJGarageLayer){
	bool init(){
		if(!GJGarageLayer::init()) return false;

		auto dontdochanges = Mod::get()->getSettingValue<bool>("revertIconKitChanges");

		if(!dontdochanges){

			// omg we're finally back to 'this' calls
			auto shardsMenu = this->getChildByID("shards-menu");
			auto colorButton = shardsMenu->getChildByID("color-button");

			auto topLeftMenu = this->getChildByID("top-left-menu");
			auto shopButton = topLeftMenu->getChildByID("shop-button");
			
			if(shopButton) shopButton->setPositionX(493);
			if(colorButton) colorButton->setPosition(473.25, -12.5);

			//oh no, this is where the pain begins....

			auto starsIcon =  dynamic_cast<CCSprite*>(this->getChildByID("stars-icon"));
			auto starsLabel = dynamic_cast<CCLabelBMFont*>(this->getChildByID("stars-label"));

			auto moonsIcon =  dynamic_cast<CCSprite*>(this->getChildByID("moons-icon"));
			auto moonsLabel = dynamic_cast<CCLabelBMFont*>(this->getChildByID("moons-label"));

			auto coinsIcon =  dynamic_cast<CCSprite*>(this->getChildByID("coins-icon"));
			auto coinsLabel = dynamic_cast<CCLabelBMFont*>(this->getChildByID("coins-label"));

			auto userCoinsIcon =  dynamic_cast<CCSprite*>(this->getChildByID("user-coins-icon"));
			auto userCoinsLabel = dynamic_cast<CCLabelBMFont*>(this->getChildByID("user-coins-label"));

			auto orbsIcon =  dynamic_cast<CCSprite*>(this->getChildByID("orbs-icon"));
			auto orbsLabel = dynamic_cast<CCLabelBMFont*>(this->getChildByID("orbs-label"));

			auto diamondsIcon =  dynamic_cast<CCSprite*>(this->getChildByID("diamonds-icon"));
			auto diamondsLabel = dynamic_cast<CCLabelBMFont*>(this->getChildByID("diamonds-label"));

			auto diamondShardsIcon = dynamic_cast<CCSprite*>(this->getChildByID("diamond-shards-icon"));
			auto diamondShardsLabel = dynamic_cast<CCLabelBMFont*>(this->getChildByID("diamond-shards-label"));

			// demons in garage 
			auto demonsIcon = dynamic_cast<CCSprite*>(this->getChildByID("demons-icon"));
			auto demonsLabel = dynamic_cast<CCLabelBMFont*>(this->getChildByID("demons-label"));

			if(starsIcon) starsIcon->setPositionX(83);
			if(starsLabel) starsLabel->setPositionX(126);

			if(moonsIcon) moonsIcon->setPositionX(83);
			if(moonsLabel) moonsLabel->setPositionX(126);

			if(coinsIcon) coinsIcon->setPositionX(83);
			if(coinsLabel) coinsLabel->setPositionX(126);

			if(userCoinsIcon) userCoinsIcon->setPositionX(83);
			if(userCoinsLabel) userCoinsLabel->setPositionX(126);

			if(orbsIcon) orbsIcon->setPositionX(83);
			if(orbsLabel) orbsLabel->setPositionX(126);

			// second row

			if(diamondsIcon) {
				diamondsIcon->setPositionX(149);
				diamondsIcon->setPositionY(307);
			};
			if(diamondsLabel) {
				diamondsLabel->setPositionX(184);
				diamondsLabel->setPositionY(307);
			}

			if(diamondShardsIcon) {
				diamondShardsIcon->setPositionX(149);
				diamondShardsIcon->setPositionY(292);
			}
			if(diamondShardsLabel) {
				diamondShardsLabel->setPositionX(184);
				diamondShardsLabel->setPositionY(292);
			}

			if(demonsIcon){
				demonsIcon->setPositionX(149);
				demonsIcon->setPositionY(277);
			}

			// demons in garage 
			if(demonsLabel){
				demonsLabel->setPositionX(184);
				demonsLabel->setPositionY(277);
			}
		}
		return true;
	}
};