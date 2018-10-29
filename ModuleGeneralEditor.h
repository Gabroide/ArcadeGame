#ifndef __MODULE_GENERAL_EDITOR_H
#define __MODULE_GENERAL_EDITOR_H
class ModuleGeneralEditor
{
public:
	ModuleGeneralEditor() {};
	~ModuleGeneralEditor() {};

	virtual bool drawSubmodule()
	{
		return true;
	};
};

#endif

