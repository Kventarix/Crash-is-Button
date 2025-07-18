#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class $modify(CrashBtn, MenuLayer) {
    bool init() override {
        if (!MenuLayer::init()) return false;

        auto winSize = CCDirector::get()->getWinSize();

        auto closeMenu = this->getChildByID("close-menu");

        if (!closeMenu) {
            closeMenu = CCMenu::create();
            closeMenu->setID("close-menu");

            closeMenu->setContentSize({40.f, 200.f});
            closeMenu->ignoreAnchorPointForPosition(false);
            closeMenu->setAnchorPoint({0.f, 1.f});
            closeMenu->setPosition({10.f, winSize.height - 5.f});

            auto layout = ColumnLayout::create()
                ->setGap(4.f)
                ->setAxisReverse(true)
                ->setAxisAlignment(AxisAlignment::End)
                ->setCrossAxisOverflow(false);
            closeMenu->setLayout(layout);

            this->addChild(closeMenu);
        }

        if (!closeMenu->getChildByID("crash-button")) {
            auto bg = CCSprite::create("kventarix.crash_is_button/closeCircle.png");
            if (!bg) return true;
            bg->setScale(0.7f);

            if (auto icon = CCSprite::create("kventarix.crash_is_button/crashBtn.png")) {
                icon->setPosition(bg->getContentSize() / 2);
                bg->addChild(icon);
            }

            auto button = CCMenuItemSpriteExtra::create(
                bg,
                this,
                menu_selector(CrashBtn::onCrashBtn)
            );
            button->setID("crash-button");

            closeMenu->addChild(button);
            closeMenu->updateLayout();
        }

        return true;
    }

    void onCrashBtn(CCObject*) {
        geode::createQuickPopup(
            "Crash Game",
            "Are you sure you want to <cr>crash</c>?\n<cr>PROGRESS MAY BE NOT SAVED</c>!!!",
            "Cancel",
            "Yes",
            [](FLAlertLayer*, bool btn2) {
                if (btn2) {
                    volatile int* p = nullptr;
                    *p = 1234;
                }
            }
        );
    }
};