#pragma once

#include "Tree.h"
#include "MegaBoss.h"

namespace BT
{
   

    class PlayerDetect : public BehaviorNodeDecorator<MegaBoss, IConditionalNode>
    {
    public:
        PlayerDetect(ICompositeNode* node)
            : BehaviorNodeDecorator<MegaBoss, IConditionalNode>(node)
        {
        }

        bool condition() override
        {
            bool detected = getGameObject()->isPlayerDetect();
            std::cout << "BT: PlayerDetect condition() - Detected: " << detected << std::endl;

            if (!detected)
            {
                std::cout << "BT: Player lost, returning to Patrol" << std::endl;
                return false;
            }
            return detected;
        }

        Status tick() override
        {
            std::cout << "BT: PlayerDetect tick() called" << std::endl;
            return IConditionalNode::tick();
        }

    };


    class Patrol : public BehaviorNodeDecorator<MegaBoss, IActionNode>
    {
    public:
        Patrol(ICompositeNode* parent) : BehaviorNodeDecorator<MegaBoss, IActionNode>(parent) {}

        Status tick() override
        {

            MegaBoss* boss = getGameObject();
            if (!boss) return Failed;

            if (boss->isPlayerDetect())
            {
                return Success;
            }

            boss->Patrol();
            return Running;
        }

    };

    class Idle : public BehaviorNodeDecorator<MegaBoss, IActionNode>
    {
    public:
        Idle(ICompositeNode* parent) : BehaviorNodeDecorator<MegaBoss, IActionNode>(parent) {}

        Status tick() override
        {
            std::cout << "BT: Idle tick() called" << std::endl;

            MegaBoss* boss = getGameObject();
            if (!boss) 
                return Failed;


            if (!boss->isIdle())
            {
                std::cout << "BT: Switching to Idle mode before attacking" << std::endl;
                boss->startIdle();
                return Running;
            }

            if (boss->endIdle())
            {
                std::cout << "BT: Idle finished, switching to next action" << std::endl;
                return Success;
            }

            return Running;
        }

    };

    class AttackPlayer : public BehaviorNodeDecorator<MegaBoss, IActionNode>
    {
    public:
        AttackPlayer(ICompositeNode* parent) : BehaviorNodeDecorator<MegaBoss, IActionNode>(parent) {}

        Status tick() override
        {
            MegaBoss* boss = getGameObject();
            if (!boss) 
                return Failed;

            if (boss->canShoot())
            {
                std::cout << "BT: AttackPlayer tick() - Shooting" << std::endl;
                boss->Shoot();
                boss->reseatShootTimer();
                return Running;
            }

            if (!boss->isPlayerDetect())
            {
                return Failed;
            }

            return Running; 
        }
    };

    class LowHealth : public BehaviorNodeDecorator<MegaBoss, IConditionalNode>
    {
    public:
        LowHealth(ICompositeNode* parent) : BehaviorNodeDecorator<MegaBoss, IConditionalNode>(parent) {}

        bool condition() override
        {
            bool lowHealth = getGameObject()->getPV() < 150;
            std::cout << "BT: LowHealth condition = " << lowHealth << std::endl;
            return lowHealth;
        }

        Status tick() override
        {
            MegaBoss* boss = getGameObject();
            if (!boss) 
                return Failed;

            if (!hasExecuted)
            {
                std::cout << "BT: LowHealth tick() - Executing Special Attack!" << std::endl;
                std::cout << "BT: LowHealth condition() CHECKED - PV: " << boss->getPV() << std::endl;
                boss->SpecialAttack();
                hasExecuted = true;
                return Running;
            }

            return Success;

        }

    private:
        bool hasExecuted = false;
    };

    class SpecialAttack : public BehaviorNodeDecorator<MegaBoss, IActionNode>
    {
    public:
        SpecialAttack(ICompositeNode* parent) : BehaviorNodeDecorator<MegaBoss, IActionNode>(parent) {}

        Status tick() override
        {
            getGameObject()->SpecialAttack();
            return Success;
        }
    };

}