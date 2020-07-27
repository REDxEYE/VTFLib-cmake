/*
 * VTFLib
 * Copyright (C) 2005-2010 Neil Jedrzejewski & Ryan Gregg

 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later
 * version.
 */

#include "../include/VTFLib.h"
#include "../include/FileWriter.h"

using namespace VTFLib;
using namespace VTFLib::IO::Writers;

CFileWriter::CFileWriter(const vlChar *cFileName)
{
	this->hFile = NULL;

	this->cFileName = new vlChar[strlen(cFileName) + 1];
	strcpy(this->cFileName, cFileName);
}

CFileWriter::~CFileWriter()
{
	this->Close();

	delete []this->cFileName;
}

vlBool CFileWriter::Opened() const
{
	return this->hFile != nullptr;
}

vlBool CFileWriter::Open()
{
	this->Close();

	this->hFile = CreateFile(this->cFileName, GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

	if(this->hFile == INVALID_HANDLE_VALUE)
	{
		this->hFile = nullptr;

		LastError.Set("Error opening file.", vlTrue);

		return vlFalse;
	}

	return vlTrue;
}

vlVoid CFileWriter::Close()
{
	if(this->hFile != nullptr)
	{
		CloseHandle(this->hFile);
		this->hFile = nullptr;
	}
}

vlUInt CFileWriter::GetStreamSize() const
{
	if(this->hFile == nullptr)
	{
		return 0;
	}

	return GetFileSize(this->hFile, nullptr);
}

vlUInt CFileWriter::GetStreamPointer() const
{
	if(this->hFile == nullptr)
	{
		return 0;
	}

	return (vlUInt)SetFilePointer(this->hFile, 0, nullptr, FILE_CURRENT);
}

vlUInt CFileWriter::Seek(vlLong lOffset, vlUInt uiMode)
{
	if(this->hFile == nullptr)
	{
		return 0;
	}

	return (vlUInt)SetFilePointer(this->hFile, lOffset, nullptr, uiMode);
}

vlBool CFileWriter::Write(vlChar cChar)
{
	if(this->hFile == nullptr)
	{
		return vlFalse;
	}

	vlULong ulBytesWritten = 0;

	if(!WriteFile(this->hFile, &cChar, 1, &ulBytesWritten, nullptr))
	{
		LastError.Set("WriteFile() failed.", vlTrue);
	}

	return ulBytesWritten == 1;
}

vlUInt CFileWriter::Write(vlVoid *vData, vlUInt uiBytes)
{
	if(this->hFile == nullptr)
	{
		return 0;
	}

	vlULong ulBytesWritten = 0;

	if(!WriteFile(this->hFile, vData, uiBytes, &ulBytesWritten, nullptr))
	{
		LastError.Set("WriteFile() failed.", vlTrue);
	}

	return (vlUInt)ulBytesWritten;
}