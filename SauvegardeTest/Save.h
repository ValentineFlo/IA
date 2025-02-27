#pragma once
#include "IGameObjects.h"
#include "Pieces.h"

class ISave
{
public:
    virtual ~ISave() = default;
    virtual bool save(int score, int PV_Player, int PV_Boss, int PV_MegaBoss) = 0;
    virtual bool load(int& score, int& PV_Player, int& PV_Boss, int& PV_MegaBoss) = 0;
};

class SaveFile : public ISave
{
public:

    SaveFile(const std::string& filename);
    bool save(int score, int PV_Player, int PV_Boss, int PV_MegaBoss) override;
    bool load(int& score, int& PV_Player, int& PV_Boss, int& PV_MegaBoss) override;

private:
    std::string m_filename;

};