#include "Shader.h"



Shader::Shader()
{
}

Shader::Shader(LPCTSTR fileName)
{
	//셰이더 파일 이름 읽어오기
	this->fileName = fileName;
	entryPoint = "main";

}

Shader::Shader(LPCTSTR fileName, LPCSTR entry, LPCSTR profile)
{
	this->fileName = fileName;
	this->entryPoint = entry;
	this->profile = profile;
}


Shader::~Shader()
{
}

void Shader::Release()
{
	Memory::SafeRelease(shaderBuffer);
}
