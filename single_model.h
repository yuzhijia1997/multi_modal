#pragma once
#include "base_model.h"
class SingleModel :
    public BaseModel
{
public:
    using BaseModel::BaseModel;

    void set_modal(const std::string& m) { modal = m; }
    std::string get_modal() { return modal; }

    bool IsExistGallery();
    bool GetGalleryFiles(std::vector<std::vector<std::string>>& files);

    std::string Accelerate();
    void ComputeDis(const std::string& imageName, std::vector<float>& distance, std::vector<std::vector<std::string>>& gallery_files);
    std::vector<std::vector<std::string>> GetMatchResult(const std::string& imageName);

private:
    std::string modal;
};

