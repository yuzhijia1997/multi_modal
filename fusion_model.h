#pragma once
#include "base_model.h"
class FusionModel :
    public BaseModel
{
public:
    using BaseModel::BaseModel;

    void set_mode(const std::string& m) { mode = m; }
    std::string get_mode() { return mode; }

    bool IsExistGallery();
    bool GetGalleryFiles(std::vector<std::vector<std::string>>& files);

    std::string Accelerate();
    void ComputeDis(const std::vector<std::string>& imageNames, std::vector<float>& distance, std::vector<std::vector<std::string>>& gallery_files);
    std::vector<std::vector<std::string>> GetMatchResult(const std::vector<std::string>& imageNames);

private:
    std::string mode;
};

