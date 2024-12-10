#pragma once

#include "FigureCollector.h"

class CommandHandler
{
public:
	static void handleDeleteCommand(FigureCollector& figureCollector, size_t indexToDelete);
	static void handleCloneCommand(FigureCollector& figureCollector, size_t indexToClone);
	static void handleSerialiseCommand(const FigureCollector& figureCollector);
	static void handlePrintCommand(const FigureCollector& figureCollector);

};
