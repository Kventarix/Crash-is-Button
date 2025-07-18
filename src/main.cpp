#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class $modify(CrashButtonMod, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) {
            return false;
        }

        auto bg = CCSprite::create("kventarix.crash_is_button/closeCircle.png");
        if (!bg) return true;
        bg->setScale(0.7f);

        auto icon = CCSprite::create("kventarix.crash_is_button/crashBtn.png");
        if (!icon) return true;
        icon->setPosition(bg->getContentSize() / 2);
        bg->addChild(icon);

        auto button = CCMenuItemSpriteExtra::create(
            bg,
            this,
            menu_selector(CrashButtonMod::onCrashButton)
        );
        button->setID("crash-button"_spr);

        auto closeMenu = this->getChildByID("close-menu");
        closeMenu->addChild(button);
        closeMenu->updateLayout();

        return true;
    }

    void onCrashButton(CCObject*) {
        geode::createQuickPopup(
            "Crash Game",
            "Are you sure you want to <cr>crash</c>?\n<cr>PROGRESS MAY BE NOT SAVED</c>!!!",
            "Cancel",
            "Yes",
            [](auto, bool btn2) {
                if (btn2) {
                    int* p = nullptr;
                    *p = 42;
                }
            }
        );
    }
};