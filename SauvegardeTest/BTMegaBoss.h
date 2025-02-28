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
            std::cout << getGameObject()->getPV()<< std::endl;
            return getGameObject()->getPV();   //isPlayerNear();
        }
    };

    class Idle : public BehaviorNodeDecorator<MegaBoss, IActionNode>
    {
    public:
        Idle(ICompositeNode* parent) : BehaviorNodeDecorator<MegaBoss, IActionNode>(parent) {}

        Status tick() override
        {

            std::cout << getGameObject()->getPV() << std::endl;
            getGameObject()->getPV();   //isPlayerNear();//idleBehavior();
            return Running;
        }
    };

    class Patrol : public BehaviorNodeDecorator<MegaBoss, IActionNode>
    {
    public:
        Patrol(ICompositeNode* parent) : BehaviorNodeDecorator<MegaBoss, IActionNode>(parent) {}

        Status tick() override
        {

            std::cout << getGameObject()->getPV() << std::endl;
            getGameObject()->getPV();
                //patrolArea();
            return Running;
        }
    };

    class AttackPlayer : public BehaviorNodeDecorator<MegaBoss, IActionNode>
    {
    public:
        AttackPlayer(ICompositeNode* parent) : BehaviorNodeDecorator<MegaBoss, IActionNode>(parent) {}

        Status tick() override
        {
            std::cout << getGameObject()->getPV() << std::endl;
            getGameObject()->getPV();
                //Shoot();
            return Success;
        }
    };

    class LowHealth : public BehaviorNodeDecorator<MegaBoss, IConditionalNode>
    {
    public:
        LowHealth(ICompositeNode* parent) : BehaviorNodeDecorator<MegaBoss, IConditionalNode>(parent) {}

        bool condition() override
        {
            return getGameObject()->getPV() < 150;
        }
    };

    class SpecialAttack : public BehaviorNodeDecorator<MegaBoss, IActionNode>
    {
    public:
        SpecialAttack(ICompositeNode* parent) : BehaviorNodeDecorator<MegaBoss, IActionNode>(parent) {}

        Status tick() override
        {
            std::cout << getGameObject()->getPV() << std::endl;
            getGameObject()->getPV();
                //SpecialAttack();
            return Success;
        }
    };
}