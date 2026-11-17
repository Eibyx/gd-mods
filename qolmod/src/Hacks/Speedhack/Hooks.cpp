#include "Hooks.hpp"
#include "Speedhack.hpp"
#include "../../Utils/ColourUtils.hpp"
#include "../../Labels/LabelManager.hpp"

Mod* cbf = nullptr;

bool CBFCheckMenuLayer::init()
{
    cbf = Loader::get()->getLoadedMod("syzzi.click_between_frames");
    return MenuLayer::init();
}

void SpeedhackScheduler::update(float dt)
{
    // QOLMod's own logic must not run while the game is still loading, the
    // scheduler is used by the loading screen itself
    if (auto scene = CCScene::get(); scene && scene->getChildByType<LoadingLayer>(0))
    {
        CCScheduler::update(dt);
        return;
    }

    auto* speedhack = Speedhack::get();
    speedhack->realDeltatime = dt;

    if (dt <= 0)
    {
        CCScheduler::update(dt);
        return;
    }

    ColourUtils::get()->update(dt);
    LabelManager::get()->update(dt);

    float value = speedhack->getRealValue();

    static float lastPitch = 0;
    float pi = (speedhack->getMusicEnabled() && speedhack->gameplayOnlyCheck()) ? value : 1;

    if (lastPitch != pi)
    {
        // the master channel isn't available on every platform, without it the
        // pitch can't be changed
        if (auto* master = speedhack->getMasterChannel())
        {
            master->setPitch(pi);

            lastPitch = pi;
        }
    }

    if (speedhack->getGameplayEnabled())
    {
        CCScheduler::update(dt);
        
        return;
    }

    if (cbf)
    {
        auto director = CCDirector::get();

        director->m_fActualDeltaTime *= value;
        director->m_fDeltaTime *= value;
    }

    CCScheduler::update(dt * value);
}

bool isNodeUnpausable(CCNode* node)
{
    if (!node)
        return false;

    if (node->getUserObject("unpausable"_spr))
        return true;

    if (node->getParent())
        return isNodeUnpausable(node->getParent());

    return false;
}

void SpeedhackScheduler::pauseTarget(CCObject *pTarget)
{
    if (auto node = typeinfo_cast<CCNode*>(pTarget))
    {
        if (isNodeUnpausable(node))
            return;
    }

    CCScheduler::pauseTarget(pTarget);
}

void SpeedhackBaseGameLayer::update(float dt)
{
    if (Speedhack::get()->getGameplayEnabled())
    {
        dt *= Speedhack::get()->getRealValue();
    }

    GJBaseGameLayer::update(dt);
}