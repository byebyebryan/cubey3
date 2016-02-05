#pragma once

#include <unordered_map>

#include "IService.h"

namespace cubey3 {
	const int kDefaultOutputFileBufferSize = 4096;
	const std::string kDefaultOutputFilePath = "./";

	class FileManager : public IService<FileManager> {
	public:
		size_t AddOutputFile(const std::string& _file_name, const std::string& _file_path = kDefaultOutputFilePath, size_t _buffer_size = kDefaultOutputFileBufferSize) {
			size_t key = hasher(_file_path + _file_name);
			output_files_.emplace(std::make_pair(key, OutputFile(_file_name, _file_path, _buffer_size)));
			if (!output_files_[key].ScanFromDisk()) {
				output_files_[key].CreateNewFile();
			}
			return key;
		}

		OutputFile* GetOutputFile(size_t _key) {
			return &output_files_[_key];
		}

		OutputFile* GetOutputFile(const std::string& _file_name, const std::string& _file_path = kDefaultOutputFilePath) {
			return &output_files_[hasher(_file_path + _file_name)];
		}

	private:
		std::unordered_map<size_t, OutputFile> output_files_;
		std::hash<std::string> hasher;
	};
}


