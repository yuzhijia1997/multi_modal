#pragma once
#include "base_model.h"

class FaceModel :
    public BaseModel
{
public:
    using BaseModel::BaseModel;
    bool IsExistGallery();
    bool GetGalleryFiles(std::vector<std::vector<std::string>>& files);

    std::string Accelerate();
    void ComputeDis(const std::string& imageName, std::vector<float>& distance, std::vector<std::vector<std::string>>& gallery_files);
    std::vector<std::vector<std::string>> GetMatchResult(const std::string& imageName);
};

