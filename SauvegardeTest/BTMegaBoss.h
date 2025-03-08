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

            if (!detected)
            {
                return false;
            }
            return detected;
        }

        Status tick() override
        {
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
                boss->startIdle();
                return Running;
            }

            if (boss->endIdle())
            {
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
                std::cout << "BT: AttackPlayer tick() called" << std::endl;
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
            bool lowHealth = getGameObject()->getPV() <= 150;
            return lowHealth;
        }

        Status tick() override
        {
            MegaBoss* boss = getGameObject();
            if (!boss) 
                return Failed;

            if (condition())
            {
                boss->SpecialAttack();
                return Running;
            }

            return Success;

        }

    };

    class SpecialAttack : public BehaviorNodeDecorator<MegaBoss, IActionNode>
    {
    public:
        SpecialAttack(ICompositeNode* parent) : BehaviorNodeDecorator<MegaBoss, IActionNode>(parent) {}

        Status tick() override
        {
            MegaBoss* boss = getGameObject();
            if (!boss) return Failed;

            if (boss->canShoot())
            {
                std::cout << "BT: Special Attack Activated!" << std::endl;
                boss->SpecialAttack();
                boss->reseatShootTimer();
            }

            std::cout << "BT: Special Attack - MegaBoss still patrolling!" << std::endl;
            boss->Patrol();

            return Running;
        }
    };

}