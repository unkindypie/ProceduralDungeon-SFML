#pragma once
class DebugInformation //класс для сбора информации о работе программы(с использованием паттерна Singleton)
{
private:
	DebugInformation() = default;
	~DebugInformation() = default;
public:
	int renderedEntitiesCounter = 0;
	int updatedEntitiesCounter = 0;

	DebugInformation(const DebugInformation&) = delete;
	DebugInformation& operator=(DebugInformation&) = delete;
	static DebugInformation & getInstance();
	void clear();
};

