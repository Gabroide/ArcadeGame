#ifndef __MODULE_CONSOLE_H
#define __MODULE_CONSOLE_H

#include "ModuleGeneralEditor.h"

class ModuleConsole :
	public ModuleGeneralEditor
{
public:
	ModuleConsole();
	~ModuleConsole();

	bool drawSubmodule();

};

#endif // !
