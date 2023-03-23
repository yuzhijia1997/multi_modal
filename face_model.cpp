#include "face_model.h"
#include <fstream>
#include <direct.h>
#include <ctime>

const std::string kCacheDirectoy = ".\\.cache";
const std::string kRecordFile = kCacheDirectoy + "\\gallery_features_record.txt";

bool FaceModel::IsExistGallery()
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

bool FaceModel::GetGalleryFiles(std::vector<std::vector<std::string>>& files)
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
			std::vector<std::string> person_image;
			std::string face_path = dirname + "\\" + file_info.name + "\\face";
			std::vector<std::string> imagePathList;
			cv::glob(face_path, imagePathList);
			for (auto iter : imagePathList) {
				files.push_back({ file_info.name,iter});
			}
		}
	} while (!_findnext(handle, &file_info));

	_findclose(handle);
	return true;
}

std::string FaceModel::Accelerate()
{
	if (_access(kCacheDirectoy.c_str(), 0) == -1)
		_mkdir(kCacheDirectoy.c_str());
	//如果存在，返回文件路径
	std::ifstream record(kRecordFile,std::ios::in);
	if (record.is_open()) {
		std::string model, gallery, file_path;
		while (record >> model && !record.eof()) {
			record >> gallery >> file_path;
			if (model == "face" && gallery == get_gallery_dir()) {
				record.close();
				return file_path;
			}
		}
	}
	record.close();

	//不存在，创建，名称为日期名称“yy_mm_dd_hh_MM_ss”
	time_t now = time(0);
	tm* ltm = localtime(&now);
	std::string file_path = kCacheDirectoy+"\\";
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
	for (int i = 0;i < person_num; i=i+64) {
		std::vector<at::Tensor> inputsVector;
		int current_num = std::min(i + 64, person_num) - i;
		gfeats_file.write((char*)&current_num, sizeof(int));
		int a = (128 + 1024) * current_num;
		gfeats_file.write((char*)&a, sizeof(int));
		for (int j = i;j < i + current_num;++j) {
			at::Tensor inputTensor;
			GetImageInput(gallery_files[j][1], inputTensor);
			inputsVector.push_back(inputTensor);

			char person[128], image_path[1024];
			strcpy_s(person, gallery_files[j][0].c_str());
			strcpy_s(image_path, gallery_files[j][1].c_str());
			gfeats_file.write(person, 128);
			gfeats_file.write(image_path, 1024);
		}
		auto inputs = torch::cat(inputsVector, 0);
		inputs = inputs.to(device);
		auto outputs = Forward(inputs).cpu();
		std::vector<float> g_feat(outputs.data_ptr<float>(), outputs.data_ptr<float>() + outputs.numel());
		int b = g_feat.size() * sizeof(float);
		gfeats_file.write((char*)&b, sizeof(int));
		gfeats_file.write((char*)&g_feat[0], g_feat.size() * sizeof(float));
	}
	gfeats_file.close();

	std::ofstream record1(kRecordFile, std::ios::out | std::ios::app);
	record1 << "face" <<" "<< get_gallery_dir() << " " << file_path << std::endl;
	record1.close();
	return file_path;
}

void FaceModel::ComputeDis(const std::string& imageName, std::vector<float>& distance, std::vector<std::vector<std::string>>& gallery_files)
{
	at::Tensor inputs;
	GetImageInput(imageName, inputs);
	inputs = inputs.to(device);
	auto t_feat = Forward(inputs);

	std::vector<at::Tensor> disVector;
	if (get_is_accelerate()) {
		std::string file_path = Accelerate();
		std::ifstream gfeats_file(file_path.c_str(), std::ios::binary);
		int person_num, current_num;
		gfeats_file.read((char*)&person_num, sizeof(int));
		while (gfeats_file.read((char*)&current_num, sizeof(int)) && !gfeats_file.eof()) {
			int size;
			gfeats_file.read((char*)&size, sizeof(int));
			for (int i = 0;i < current_num;++i) {
				char person[128], image_path[1024];
				gfeats_file.read(person, 128);
				gfeats_file.read(image_path, 1024);
				gallery_files.push_back({ person,image_path });
			}
			gfeats_file.read((char*)&size, sizeof(int));
			std::vector<float> g_featsVector(size/sizeof(float));
			gfeats_file.read((char*)&g_featsVector[0], size);
			at::Tensor g_feats = torch::tensor(g_featsVector, torch::kFloat);
			g_feats = g_feats.reshape({ current_num,-1 });
			g_feats = g_feats.to(device);
			at::Tensor dist;
			ComputeDistance(t_feat, g_feats, dist);
			disVector.push_back(dist);
		}
		gfeats_file.close();
	}
	else
	{
		GetGalleryFiles(gallery_files);
		for (int i = 0;i < gallery_files.size(); i = i + 64) {
			std::vector<at::Tensor> inputsVector;
			for (int j = i;j < std::min(i + 64, int(gallery_files.size()));++j) {
				at::Tensor inputTensor;
				GetImageInput(gallery_files[j][1], inputTensor);
				inputsVector.push_back(inputTensor);
			}
			inputs = torch::cat(inputsVector, 0);
			inputs = inputs.to(device);
			auto g_feats = Forward(inputs);
			at::Tensor dist;
			ComputeDistance(t_feat, g_feats, dist);
			disVector.push_back(dist);
		}
	}
	at::Tensor disTensor = torch::cat(disVector, 1)[0].toType(torch::kFloat);
	distance.assign(disTensor.data_ptr<float>(), disTensor.data_ptr<float>() + disTensor.numel());
}

std::vector<std::vector<std::string>> FaceModel::GetMatchResult(const std::string& imageName)
{
	std::vector<float> distance;
	std::vector<std::vector<std::string>> gallery_files;
	ComputeDis(imageName, distance, gallery_files);
	std::vector<int> index = argsort(distance);
	std::vector<std::vector<std::string>> results;
	for (int i : index) {
		results.push_back(gallery_files[i]);
	}
	return results;
}
