#pragma once

#include <fstream>
#include <string>

#include "DuoBufferMT.h"
#include "TimeManager.h"

namespace cubey2 {
	

	class OutputFile {
	public:
		OutputFile() :
				file_name_(""),
				file_path_(""),
				file_size_(-1) {
		}

		OutputFile(const std::string& _file_name, const std::string& _file_path, size_t _buffer_size) :
				file_name_(_file_name),
				file_path_(_file_path),
				file_size_(-1) {
			auto f_lock = buffer_.LockFrontBuffer();
			auto b_lock = buffer_.LockBackBuffer();
			buffer_.front_buffer()->reserve(_buffer_size);
			buffer_.back_buffer()->reserve(_buffer_size);
		}

		void Append(const std::string& text) {
			auto f_lock = buffer_.LockFrontBuffer();
			buffer_.front_buffer()->append(text);
		}

		bool ScanFromDisk() {
			if (!fstream_.is_open()) {
				fstream_.open(file_path_ + file_name_, std::fstream::in | std::fstream::ate);
				if (fstream_.is_open()) {
					file_size_ = fstream_.tellg();
					fstream_.close();
					return true;
				}
				else {
					file_size_ = -1;
					return false;
				}
			}
			return false;
		}

		bool CreateNewFile() {
			if (!fstream_.is_open()) {
				fstream_.open(file_path_ + file_name_, std::fstream::out | std::fstream::trunc);
				if (fstream_.is_open()) {
					fstream_ << "-------- FILE : " + file_name_ + " -- CREATED ON : " + TimeManager::GetInstance()->GetTimeString() + " --------\n";
					fstream_.close();
					return ScanFromDisk();
				}
				else {
					return false;
				}
			}
			return false;
		}

		bool OpenFile() {
			if (!fstream_.is_open()) {
				fstream_.open(file_path_ + file_name_, std::fstream::out | std::fstream::app);
			}

			return fstream_.is_open();
		}

		bool WriteToDisk() {
			buffer_.SwapMTB();
			if (OpenFile()) {
				auto b_lock = buffer_.LockBackBuffer();
				fstream_.write(buffer_.back_buffer()->c_str(), buffer_.back_buffer()->size());
				fstream_.close();
				buffer_.back_buffer()->clear();

				return ScanFromDisk();
			}
			return false;
		}

		size_t file_size() {
			return file_size_;
		}

	private:
		std::fstream fstream_;
		DuoBufferMT<std::string> buffer_;
		std::string file_name_;
		std::string file_path_;

		size_t file_size_;
	};
}