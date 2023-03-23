#pragma once
#include <single_model.h>

class ScoreModel
{
public:
	ScoreModel() {};
	~ScoreModel() {};

	void set_models_name(const std::vector<std::string>& filesname) { models_path = filesname; }
	std::vector<std::string> get_models_name() { return models_path; }
	void set_modals(const std::vector<std::string>& modelnames) { modals = modelnames; }
	std::vector<std::string> get_modals() { return modals; }
	void set_gallery_dir(const std::string& dirname) { gallery_dir = dirname; }
	std::string get_gallery_dir() { return gallery_dir; }
	void set_is_accelerate(bool flag) { is_accelerate = flag; }
	bool get_is_accelerate() { return is_accelerate; }
	
	void set_model_and_modals(const std::vector<std::string>& filesname, const std::vector<std::string>& modelnames);
	bool GetGalleryFiles(std::vector<std::vector<std::string>>& files);
	bool IsExistGallery();
	void LoadModels();
	std::vector<at::Tensor> Forward(std::vector<at::Tensor>& inputs);
	bool GetImageInput(const std::string imageName, at::Tensor& inputTensor);

	std::string Accelerate();
	void ComputeDis(const std::vector<std::string>& imageNames, std::vector<std::vector<float>>& distance, std::vector<std::vector<std::string>>& gallery_files);
	std::vector<std::vector<std::string>> GetMatchResult(const std::vector<std::string>& imageNames);


private:
	std::vector<std::string> models_path;
	std::string gallery_dir;
	std::vector<std::string> modals;
	std::vector<std::shared_ptr<torch::jit::Module>>  models;

	torch::Device device = torch::DeviceType(torch::kCPU);
	bool is_accelerate = false;
};

