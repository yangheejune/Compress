#pragma once

class Compress
{
public:
	Compress() {};
	~Compress() {};

	DWORD ExtractFile(LPCWSTR lpSourceFile, LPCWSTR lpTargetPath);
	DWORD CompressFile(LPCWSTR lpSourceFile, LPCWSTR lpTargetPath);

	std::vector<std::string> get_files_inDirectory(const std::string& _path, const std::string& _filter);
	std::string convLPCWSTRtoString(LPCWSTR wString);
};