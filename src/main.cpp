#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class $modify(CrashButtonLayer, MenuLayer) {
public:
    bool init() override {
        if (!MenuLayer::init()) {
            return false;
        }

        auto buttonSprite = CCSprite::create("kventarix.crash_is_button/CrashBtn.png");
        if (!buttonSprite) {
            log::warn("CrashButton: failed to load CrashBtn.png");
            return true;
        }

        auto crashButton = CCMenuItemSpriteExtra::create(
            buttonSprite,
            this,
            menu_selector(CrashButtonLayer::onCrashButton)
        );
        crashButton->setID("crash-button"_spr);

        auto crashMenu = CCMenu::create(crashButton, nullptr);
        crashMenu->setID("crash-menu"_spr);

        auto size = this->getContentSize();

        float offsetX = 35.f;
        float offsetY = 35.f;
        float posX = size.width - offsetX;
        float posY = size.height - offsetY;

        crashMenu->setPosition(ccp(posX, posY));

        this->addChild(crashMenu);

        return true;
    }

    void onCrashButton(CCObject*) {
        int* p = nullptr;
        *p = 42; // forced crash by null pointer dereference
    }
};

GEODE_API bool load() {
    log::info("CrashButton: loaded successfully");
    return true;
}