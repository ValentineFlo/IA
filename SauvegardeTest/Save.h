#pragma once
#include "IGameObjects.h"
#include "Pieces.h"

class ISave
{
public:
    virtual ~ISave() = default;
    virtual bool save(int& score) = 0;
    virtual bool load(int& score) = 0;
};

class SaveFile : public ISave
{
public:

    SaveFile(const std::string& filename);
    bool save(int& score) override;
    bool load(int& score) override;

private:
    std::string m_filename;

};