#include "base_model.h"

namespace F = torch::nn::functional;

//template <typename T>
//std::vector<int> argsort(const std::vector<T>& array)
//{
//	const int array_len(array.size());
//	std::vector<int> array_index(array_len, 0);
//	for (int i = 0; i < array_len; ++i)
//		array_index[i] = i;
//
//	std::sort(array_index.begin(), array_index.end(),
//		[&array](int pos1, int pos2) {return (array[pos1] < array[pos2]);});
//
//	return array_index;
//}

void ComputeDistance(at::Tensor& qf, at::Tensor& gf, at::Tensor& dis) {
	qf = F::normalize(qf, F::NormalizeFuncOptions().p(2).dim(1));
	gf = F::normalize(gf, F::NormalizeFuncOptions().p(2).dim(1));
	int m = qf.size(0);
	int n = gf.size(0);
	dis = torch::pow(qf, 2).sum(1, true).expand({ m,n }) + torch::pow(gf, 2).sum(1, true).expand({ n,m }).t();
	dis = dis.addmm(qf, gf.t(), 1, -2);
	dis = dis.cpu();
}

BaseModel::BaseModel(const std::string& filename)
	:model_path(filename), device(torch::Device(torch::DeviceType(torch::kCPU)))
{
	LoadModel();
}

BaseModel::BaseModel(const std::string& filename, const std::string& dirname)
	:model_path(filename),gallery_dir(dirname), device(torch::Device(torch::DeviceType(torch::kCPU)))
{
	LoadModel();
}

void BaseModel::LoadModel()
{
	if (!model_path.empty() && model_path.substr(model_path.length() - 3) == ".pt") {
		torch::DeviceType device_type;
		if (torch::cuda::is_available()) {
				device_type = torch::kCUDA;
				std::cout << "enable cuda ..." << std::endl;
			}
			else {
				device_type = torch::kCPU;
			}
			device = torch::Device(device_type);
			try
			{
				model = std::make_shared<torch::jit::Module>(torch::jit::load(model_path, device));
			}
			catch (const c10::Error& e)
			{
				std::cout << "error loading the model" << std::endl;
			}
	}
}

at::Tensor BaseModel::Forward(at::Tensor& inputs)
{
	(*model).eval();
	torch::NoGradGuard no_grad;

	auto outputs = (*model).forward({ inputs }).toTuple();
	return outputs->elements()[2].toTensor();
}

bool BaseModel::GetImageInput(const std::string imageName, at::Tensor& inputTensor)
{
	cv::Mat srcImage, rgbImage;
	srcImage = cv::imread(imageName);
	if (srcImage.empty() || !srcImage.data) {
		std::cout << "load image " << imageName << " failed" << std::endl;
		return false;
	}
	cv::cvtColor(srcImage, rgbImage, cv::COLOR_BGR2RGB);
	rgbImage.convertTo(rgbImage, CV_32FC3, 1.0 / 255.0);
	cv::Size scale(256, 256);
	cv::resize(rgbImage, rgbImage, scale, 0, 0, cv::INTER_LINEAR);

	inputTensor = torch::from_blob(rgbImage.data, { 1,rgbImage.rows,rgbImage.cols,3 }, torch::kFloat).clone();
	inputTensor = inputTensor.permute({ 0,3,1,2 });
	inputTensor = inputTensor.sub(0.5).div(0.5);
	return true;
}

