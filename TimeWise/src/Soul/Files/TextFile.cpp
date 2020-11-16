#include "TextFile.h"

#include <Other/Logger.h>
#include <Memory/MemoryManager.h>
#include <Utility/Macros.h>

#include <new>
#include <Windows.h>

namespace Soul
{
	TextFile::TextFile(const char* fileName) :
		m_FilePath(fileName),
		m_FileContents(nullptr)
	{
		HANDLE fileHandle = CreateFileA(m_FilePath, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		
		// TODO: Provide alternative?
		Assert(fileHandle != INVALID_HANDLE_VALUE);

		LARGE_INTEGER fileSize;
		// TODO: Provide alternative?
		Assert(GetFileSizeEx(fileHandle, &fileSize));

		m_FileContents = Partition(String, (unsigned int)fileSize.QuadPart);

		DWORD bytesRead = 15;
		// TODO: Provide alternative?
		Assert(ReadFile(fileHandle, m_FileContents->GetBufferStart(), (DWORD)fileSize.QuadPart, &bytesRead, 0));
		m_FileContents->SetLength((unsigned int)bytesRead);

		// We need to add a null terminator since the file doesn't contain one
		(*m_FileContents) += '\0';

		CloseHandle(fileHandle);
	}

	TextFile::TextFile(TextFile&& otherFile)
	{
		m_FileContents = otherFile.m_FileContents;
		m_FilePath = otherFile.m_FilePath;

		otherFile.m_FileContents = nullptr;
	}

	TextFile::~TextFile()
	{
		if (m_FileContents)
		{
			MemoryManager::FreeMemory(m_FileContents);
		}
	}

	void TextFile::WriteStringToFile()
	{
		DeleteFileA(m_FilePath);
		HANDLE fileHandle = CreateFileA(m_FilePath, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		// TODO: Provide alternative?
		Assert(fileHandle != INVALID_HANDLE_VALUE);

		DWORD bytesWritten;
		// TODO: Provide alternative?
		Assert(WriteFile(fileHandle, m_FileContents->GetCString(), m_FileContents->Length(), &bytesWritten, 0));

		CloseHandle(fileHandle);
	}

	const char* TextFile::GetCString() const
	{
		return m_FileContents->GetCString();
	}

	String& TextFile::GetString() const
	{
		return *m_FileContents;
	}
}