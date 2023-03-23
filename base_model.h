#pragma once
#undef slots
#include <torch/torch.h>
#include <torch/script.h>
#define slots Q_SLOTS
#include <opencv2/opencv.hpp>

#include <io.h>
#include <iostream>
#include <memory>

template <typename T>
std::vector<int> argsort(const std::vector<T>& array, bool flag=true)
{
	const int array_len(array.size());
	std::vector<int> array_index(array_len, 0);
	for (int i = 0; i < array_len; ++i)
		array_index[i] = i;

	if (flag) {
		std::sort(array_index.begin(), array_index.end(),
			[&array](int pos1, int pos2) {return (array[pos1] < array[pos2]);});
	}
	else {
		std::sort(array_index.begin(), array_index.end(),
			[&array](int pos1, int pos2) {return (array[pos1] > array[pos2]);});
	}
	return array_index;
}

void ComputeDistance(at::Tensor& qf, at::Tensor& gf, at::Tensor& dis);


class BaseModel
{
public:
	BaseModel():device(torch::Device(torch::DeviceType(torch::kCPU))){};
	BaseModel(const std::string& filename);
	BaseModel(const std::string& filename, const std::string& dirname);
	~BaseModel() {};

	void set_model_name(const std::string& filename) { model_path = filename; LoadModel(); }
	std::string get_model_name() { return model_path; }
	void set_gallery_dir(const std::string& dirname) { gallery_dir = dirname; }
	std::string get_gallery_dir() { return gallery_dir; }
	void set_is_accelerate(bool flag) { is_accelerate = flag; }
	bool get_is_accelerate() { return is_accelerate; }

	virtual bool IsExistGallery() = 0;
	virtual bool GetGalleryFiles(std::vector<std::vector<std::string>>& files) = 0;
	void LoadModel();
	at::Tensor Forward(at::Tensor& inputs);
	bool GetImageInput(const std::string imageName, at::Tensor& inputTensor);

	torch::Device device;

private:
	std::string model_path;
	std::string gallery_dir;
	std::shared_ptr<torch::jit::Module> model;

	bool is_accelerate = false;
};