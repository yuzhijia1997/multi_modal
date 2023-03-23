#include "score_model.h"

#include <fstream>
#include <direct.h>
#include <ctime>

const std::string kCacheDirectoy = ".\\.cache";
const std::string kRecordFile = kCacheDirectoy + "\\gallery_features_record.txt";

void ScoreModel::set_model_and_modals(const std::vector<std::string>& filesname, const std::vector<std::string>& modelnames)
{
	set_models_name(filesname);
	set_modals(modelnames);
	LoadModels();
}

bool ScoreModel::GetGalleryFiles(std::vector<std::vector<std::string>>& files)
{
	_finddata_t file_info;
	std::string dir_path;
	std::string dirname = get_gallery_dir();
	auto handle = _findfirst(dir_path.assign(dirname).append("\\*.*").c_str(), &file_info);
	if (-1 == handle)
		return false;
	do
	{
		if (file_info.attrib == _A_SUBDIR && strcmp(file_info.name, ".") && strcmp(file_info.name, "..")) {

			std::string path;
			int image_num = INT_MAX;
			std::vector<std::vector<std::string>> pathLists;
			for (auto modal : modals) {
				path = dirname + "\\" + file_info.name + "\\" + modal;
				std::vector<std::string> pathList;
				cv::glob(path, pathList);
				image_num = std::min(image_num, (int)pathList.size());
				pathLists.push_back(pathList);
			}
			for (int i = 0;i < image_num; ++i) {
				std::vector<std::string> one_file = {file_info.name};
				for (auto iter = pathLists.begin();iter != pathLists.end();iter++)
					one_file.push_back((*iter)[i]);
				files.push_back(one_file);
			}
		}
	} while (!_findnext(handle, &file_info));

	_findclose(handle);
	return true;
}

bool ScoreModel::IsExistGallery()
{
	std::vector<std::vector<std::string>> files;
	if (GetGalleryFiles(files) && files.size()) {
		return true;
	}
	else
	{
		set_gallery_dir("");
		return false;
	}
}

void ScoreModel::LoadModels()
{
	torch::DeviceType device_type;
	if (torch::cuda::is_available()) {
		device_type = torch::kCUDA;
		std::cout << "enable cuda ..." << std::endl;
	}
	else {
		device_type = torch::kCPU;
	}
	device = torch::Device(device_type);

	for (auto model_path : models_path) {
		if (!model_path.empty() && model_path.substr(model_path.length() - 3) == ".pt") {
			try
			{
				std::shared_ptr<torch::jit::Module> model =\
					std::make_shared<torch::jit::Module>(torch::jit::load(model_path, device));
				models.push_back(model);
			}
			catch (const c10::Error& e)
			{
				std::cout << "error loading the model" << std::endl;
			}
		}
	}
}

std::vector<at::Tensor> ScoreModel::Forward(std::vector<at::Tensor>& inputs)
{
	std::vector<at::Tensor> outputs;
	for (int i = 0;i < inputs.size();++i) {
		(*(models[i])).eval();
		torch::NoGradGuard no_grad;
		auto output = (*(models[i])).forward({ inputs[i].to(device) }).toTuple();
		outputs.push_back(output->elements()[2].toTensor().cpu());
	}
	return outputs;
}

bool ScoreModel::GetImageInput(const std::string imageName, at::Tensor& inputTensor)
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

std::string ScoreModel::Accelerate()
{
	if (_access(kCacheDirectoy.c_str(), 0) == -1)
		_mkdir(kCacheDirectoy.c_str());
	//如果存在，返回文件路径
	std::ifstream record(kRecordFile, std::ios::in);
	if (record.is_open()) {
		std::string model, gallery, file_path;
		while (record >> model && !record.eof()) {
			record >> gallery >> file_path;
			if (model == "score" && gallery == get_gallery_dir()) {
				record.close();
				return file_path;
			}
		}
	}
	record.close();

	//不存在，创建，名称为日期名称“yy_mm_dd_hh_MM_ss”
	time_t now = time(0);
	tm* ltm = localtime(&now);
	std::string file_path = kCacheDirectoy + "\\";
	file_path += std::to_string(1900 + ltm->tm_year) + "_";
	file_path += std::to_string(1 + ltm->tm_mon) + "_";
	file_path += std::to_string(ltm->tm_mday) + "_";
	file_path += std::to_string(ltm->tm_hour) + "_";
	file_path += std::to_string(ltm->tm_min) + "_";
	file_path += std::to_string(ltm->tm_sec);

	std::ofstream gfeats_file(file_path, std::ios::out | std::ios::binary);
	std::vector<std::vector<std::string>> gallery_files;
	GetGalleryFiles(gallery_files);
	int person_num = gallery_files.size();
	gfeats_file.write((char*)&person_num, sizeof(int));
	for (int i = 0;i < person_num; i = i + 64) {
		std::vector<std::vector<at::Tensor>> inputsVector(modals.size());
		int current_num = std::min(i + 64, person_num) - i;
		gfeats_file.write((char*)&current_num, sizeof(int));
		int a = (128 + 1024 * modals.size()) * current_num;
		gfeats_file.write((char*)&a, sizeof(int));
		for (int j = i;j < i + current_num;++j) {
			for (int k = 0;k < modals.size();++k) {
				at::Tensor inputTensor;
				GetImageInput(gallery_files[j][k+1], inputTensor);
				inputsVector[k].push_back(inputTensor.clone());
			}

			char person[128], image_path[1024];
			strcpy_s(person, gallery_files[j][0].c_str());
			gfeats_file.write(person, 128);
			for (int k = 0;k < modals.size();++k) {
				strcpy_s(image_path, gallery_files[j][k+1].c_str());
				gfeats_file.write(image_path, 1024);
			}
		}
		std::vector<at::Tensor> inputsTensor;
		for (auto t:inputsVector) {
			inputsTensor.push_back(torch::cat(t, 0));
		}
		auto outputs = Forward(inputsTensor);
		int b = outputs.size() * outputs[0].numel() * sizeof(float);
		gfeats_file.write((char*)&b, sizeof(int));
		gfeats_file.write((char*)&b, sizeof(int));
		for (auto t : outputs) {
			std::vector<float> g_feat(t.data_ptr<float>(), t.data_ptr<float>() + t.numel());
			gfeats_file.write((char*)&g_feat[0], g_feat.size() * sizeof(float));
		}
	}
	gfeats_file.close();

	std::ofstream record1(kRecordFile, std::ios::out | std::ios::app);
	record1 <<"score" << " " << get_gallery_dir() << " " << file_path << std::endl;
	record1.close();
	return file_path;
}

void ScoreModel::ComputeDis(const std::vector<std::string>& imageNames, std::vector<std::vector<float>>& distance, std::vector<std::vector<std::string>>& gallery_files)
{
	std::vector<at::Tensor> inputsVector;
	for (auto imageName : imageNames) {
		at::Tensor inputTensor;
		GetImageInput(imageName, inputTensor);
		inputsVector.push_back(inputTensor.clone());
	}
	auto t_feat = Forward(inputsVector);

	std::vector<std::vector<at::Tensor>> disVector(modals.size());
	if (get_is_accelerate()) {
		std::string file_path = Accelerate();
		std::ifstream gfeats_file(file_path.c_str(), std::ios::binary);
		int person_num, current_num;
		gfeats_file.read((char*)&person_num, sizeof(int));
		while (gfeats_file.read((char*)&current_num, sizeof(int)) && !gfeats_file.eof()) {
			int size;
			gfeats_file.read((char*)&size, sizeof(int));
			char person[128], image_path[1024];
			for (int i = 0;i < current_num;++i) {
				gfeats_file.read(person, 128);
				std::vector<std::string> files = { person };
				for (int j = 0;j < modals.size();++j) {
					gfeats_file.read(image_path, 1024);
					files.push_back(image_path);
				}
				gallery_files.push_back(files);
			}
			gfeats_file.read((char*)&size, sizeof(int));
			size = size / modals.size();
			std::vector<at::Tensor> g_feats;
			for (int i = 0;i < modals.size();++i) {
				std::vector<float> g_featVector(size / sizeof(float));
				gfeats_file.read((char*)&g_featVector[0], size);
				at::Tensor g_feat = torch::tensor(g_featVector, torch::kFloat);
				g_feat = g_feat.reshape({ current_num,-1 });
				at::Tensor dist;
				ComputeDistance(t_feat[i], g_feat, dist);
				disVector[i].push_back(dist);
			}
		}
		gfeats_file.close();
	}
	else
	{
		GetGalleryFiles(gallery_files);
		for (int i = 0;i < gallery_files.size(); i = i + 64) {

			std::vector<std::vector<at::Tensor>> inputsVector(modals.size());
			for (int j = i;j < std::min(i + 64, int(gallery_files.size()));++j) {
				at::Tensor inputTensor;
				for (int k = 0;k < modals.size();++k) {
					GetImageInput(gallery_files[j][k+1], inputTensor);
					inputsVector[k].push_back(inputTensor.clone());
				}
			}
			std::vector<at::Tensor> inputsTensor;
			for (auto t : inputsVector) {
				inputsTensor.push_back(torch::cat(t, 0));
			}
			auto outputs = Forward(inputsTensor);
			for (int j = 0;j < modals.size();++j) {
				at::Tensor dist;
				ComputeDistance(t_feat[j], outputs[j], dist);
				disVector[j].push_back(dist);
			}
		}
	}

	for (int i = 0;i < modals.size();++i) {
		at::Tensor disTensor = torch::cat(disVector[i], 1)[0].toType(torch::kFloat);
		distance[i].assign(disTensor.data_ptr<float>(), disTensor.data_ptr<float>() + disTensor.numel());
	}
}

std::vector<std::vector<std::string>> ScoreModel::GetMatchResult(const std::vector<std::string>& imageNames)
{
	std::vector<std::vector<float>> distance(modals.size());
	std::vector<std::vector<std::string>> gallery_files;
	ComputeDis(imageNames, distance, gallery_files);
	std::vector<std::vector<float>> scores(modals.size());
	for (int i = 0;i < modals.size();++i) {
		for (float d : distance[i]) {
			scores[i].push_back((d - 20.0) / 20.0);
		}
	}
	std::vector<float> score(gallery_files.size(), 0.0);
	for (int i = 0;i < modals.size();++i) {
		for (int j = 0;j < gallery_files.size();++j) {
			score[j] += scores[i][j];
		}
	}
	std::vector<int> index = argsort(score);
	std::vector<std::vector<std::string>> results;
	for (int i : index) {
		results.push_back(gallery_files[i]);
	}
	return results;
}
