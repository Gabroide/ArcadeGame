#pragma once
#include "Module.h"
#include "MathGeoLib.h"

class ModuleRenderExercise : public Module
{
public:
    ModuleRenderExercise();
    ~ModuleRenderExercise();

	bool            Init    ();
	update_status   Update  ();
	bool            CleanUp ();

private:
    unsigned vbo        = 0;
	float xRot, yRot, zRot, xT, yT, zT, xS, yS, zS;
	
	float4x4 model;
};