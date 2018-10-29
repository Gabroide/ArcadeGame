#include "Application.h"

#include "ModuleRenderExercise.h"
#include "ModuleWindow.h"
#include "ModuleProgram.h"
#include "ModuleCamera.h"
#include "GL/glew.h"
#include "SDL.h"

/*COMMENT
#define NEULER 2.718281f
#define ASPECT 1.7777778f
*/
ModuleRenderExercise::ModuleRenderExercise()
{
}

ModuleRenderExercise::~ModuleRenderExercise()
{
}

bool ModuleRenderExercise::Init()
{
	// model
	xRot = 0;
	yRot = 0;
	zRot = 0;
	xT = 0;
	yT = 0;
	zT = -10;
	xS = 1;
	yS = 1;
	zS = 1;

	// triangle vertices
	/* COMMENTfloat4 v1(-1.0f, -1.0f, 0.0f, 1.0f);
	float4 v2(1.0f, -1.0f, 0.0f, 1.0f);
	float4 v3(0.0f, 1.0f, 0.0f, 1.0f);
	*/
	float vertex_buffer_data[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f,  1.0f, 0.0f,
	};

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return vbo;

	/* COMMENT
	// create object
	triangle = new ModuleTransf();
	triangle->position = { 0.0f, 1.0f, 0.0f };
	triangle->scale = { 0.5f, 1.0f, 0.5f };
	triangle->rotation = { 0.0f, 0.0f, 10.0f };

	// base
	triangle->AddVertex(-0.5f, -0.5f, -0.33f);
	triangle->AddVertex(0.0f, -0.5f, 0.66f);
	triangle->AddVertex(0.5f, -0.5f, -0.33f);

	// first side
	triangle->AddVertex(0.5f, -0.5f, -0.33f);
	triangle->AddVertex(0.0f, -0.5f, 0.66f);
	triangle->AddVertex(0.0f, 0.5f, 0.0f);
	
	// second side
	triangle->AddVertex(0.0f, -0.5f, 0.66f);
	triangle->AddVertex(-0.5f, -0.5f, -0.33f);
	triangle->AddVertex(0.0f, 0.5f, 0.0f);

	// thir side
	triangle->AddVertex(-0.5f, -0.5f, -0.33f);
	triangle->AddVertex(0.5f, -0.5f, -0.33f);
	triangle->AddVertex(0.0f, 0.5f, 0.0f);

	// Camera
	camera = new ModuleTransf();
	camera->position = { 2.0f, 2.0f, 10.0f };
	camera->scale = { 1.0f, 1.0f, 1.0f };
	camera->rotation = { 0.0f, 0.0f, 0.0f };
	//camera->behaviours.push_back(new EditorCameraMove(camera));

	// Loading GL
	LoadShaderProgram();
	glUseProgram(program);

	// filling Buffer
	std::vector<float>* vertex_buffer_data = triangle->GetVertices();
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, (*vertex_buffer_data).size() * sizeof(float), (*vertex_buffer_data).data(), GL_STATIC_DRAW);

	// setting
	math::float4x4 model = triangle->ModelMatrix();
	//math::float4x4 view = LookAt(*triangle, *camera);
	math::float4x4 view = camera->ModelMatrix().Inverted();
	math::float4x4 projection = ProjectionMatrix();
	glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_TRUE, &model[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_TRUE, &view[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "proj"), 1, GL_TRUE, &projection[0][0]);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	delete vertex_buffer_data;

	triangle->Start();
	camera->Start();
	
	return vbo;
	
	
    float vertex_buffer_data[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f,  1.0f, 0.0f,
	};

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return vbo;*/
}

update_status ModuleRenderExercise::Update()
{
	/* COMMENT
	triangle->Update();
	camera->Update();
	math::float4x4 view = camera->ModelMatrix().Inverted();
	glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_TRUE, &view[0][0]);

	//DrawPlane();

	++(triangle->rotation.y);
	math::float4x4 model = triangle->ModelMatrix();
	glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_TRUE, &model[0][0]);
	*/
	math::float4x4 identity = float4x4::identity;
	glUniformMatrix4fv(glGetUniformLocation(App->program->program,
		"model"), 1, GL_TRUE, &identity[0][0]);
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(&(GLfloat)App->camera->view[0][0]);
	glLineWidth(0.5f);

	glBegin(GL_LINES);

	float d = 200.0f;

	for (float i = -d; i <= d; i += 1.0f)
	{
		glVertex3f(i, 0.0f, -d);
		glVertex3f(i, 0.0f, d);
		glVertex3f(-d, 0.0f, i);
		glVertex3f(d, 0.0f, i);
	}

	glEnd();

	xRot += 0.01f;
	yRot += 0.01f;
	zRot += 0.01f;

	math::float4x4 tMat = float4x4::identity;
	tMat[0][3] = xT; tMat[1][3] = yT; tMat[2][3] = zT;

	math::float4x4 rMat = math::Quat::FromEulerXYZ(xRot, yRot, zRot).ToFloat4x4();

	math::float4x4 sMat = float4x4::identity;
	sMat[0][0] *= xS; sMat[1][1] *= yS; sMat[2][2] *= zS;

	model = sMat * tMat * rMat;

	glUniformMatrix4fv(glGetUniformLocation(App->program->program,
		"model"), 1, GL_TRUE, &model[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(App->program->program,
		"view"), 1, GL_TRUE, &App->camera->view[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(App->program->program,
		"proj"), 1, GL_TRUE, &App->camera->proj[0][0]);

	glUseProgram(App->program->program);// ->useProgram();
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(
            0,                  // attribute 0
            3,                  // number of componentes (3 floats)
            GL_FLOAT,           // data type
            GL_FALSE,           // should be normalized?
            0,                  // stride
            (void*)0            // array buffer offset
            );

	glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle

	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	/* COMMENT
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0 );

	glUniform3f(glGetUniformLocation(program, "albedo"), 1.0f, 0.0f, 0.0f);
	glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

	glUniform3f(glGetUniformLocation(program, "albedo"), 0.0f, 1.0f, 0.0f);
	glDrawArrays(GL_TRIANGLES, 3, 3);

	glUniform3f(glGetUniformLocation(program, "albedo"), 0.0f, 0.0f, 1.0f);
	glDrawArrays(GL_TRIANGLES, 6, 3);

	glUniform3f(glGetUniformLocation(program, "albedo"), 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLES, 9, 3);

	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	*/
	return UPDATE_CONTINUE;
}

bool ModuleRenderExercise::CleanUp()
{
	if(vbo != 0)
    {
        glDeleteBuffers(1, &vbo);
    }

	if (program != 0)
	{
		glDeleteProgram(program);
	}

	return true;
}
/* COMMENT
void ModuleRenderExercise::LoadShaderProgram()
{
	GLint success = 0;
	unsigned vShader = 0;
	unsigned fShader = 0;

	// ==== COMPILE VERTEX SHADER ====
	char* vShaderData = LoadShaderData("Default.vs");
	assert(vShaderData != nullptr);
	vShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vShader, 1, &vShaderData, NULL);
	glCompileShader(vShader);
	glGetShaderiv(vShader, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)	LOG("[GL] Vertex Shader failed to compile.")
	else LOG("[GL] Vertex Shader successfully compiled")

		// ==== COMPILE FRAGMENT SHADER ====
		char* fShaderData = LoadShaderData("default.fs");
	assert(fShaderData != nullptr);
	fShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fShader, 1, &fShaderData, NULL);
	glCompileShader(fShader);
	glGetShaderiv(vShader, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE) LOG("[GL] Fragment Shader failed to compile.")
	else LOG("[GL] Fragment Shader successfully compiled")

		// ==== LINK PROGRAM ====
		program = glCreateProgram();
	glAttachShader(program, vShader);
	glAttachShader(program, fShader);
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (success == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
		program = 0;

		LOG("[GL] Program failed to link.")
	}
	else
	{
		LOG("[GL] Program successfully linked")
	}

	glDetachShader(program, vShader);
	glDetachShader(program, fShader);

	if (vShader != 0)	glDeleteShader(vShader);
	if (fShader != 0)	glDeleteShader(fShader);
}

char* ModuleRenderExercise::LoadShaderData(const char* filename)
{
	char* data = nullptr;
	FILE* file = nullptr;
	fopen_s(&file, filename, "rb");

	if (file)
	{
		fseek(file, 0, SEEK_END);
		int size = ftell(file);
		rewind(file);
		data = (char*)malloc(size + 1);

		fread(data, 1, size, file);
		data[size] = 0;

		fclose(file);
	}
	return data;
}


math::float4x4 ModuleRenderExercise::LookAt(const ModuleTransf &target, const ModuleTransf &eye)
{
	math::float3 up(
		cos(eye.rotation.x) * sin(eye.rotation.z) + sin(eye.rotation.x) * sin(eye.rotation.y) * cos(eye.rotation.z),
		cos(eye.rotation.x) * cos(eye.rotation.z) - sin(eye.rotation.x) * sin(eye.rotation.y) * sin(eye.rotation.z),
		-sin(eye.rotation.x) * cos(eye.rotation.y)
	);

	math::float3 f(target.position - eye.position);
	f.Normalize();
	math::float3 s(f.Cross(up));
	s.Normalize();
	math::float3 u(s.Cross(f));

	math::float4x4 matrix = {
		 s.x,	 s.y,	 s.z,	-s.Dot(eye.position),
		 u.x,	 u.y,	 u.z,	-u.Dot(eye.position),
		-f.x,	-f.y,	-f.z,	 f.Dot(eye.position),
		0.0f,	0.0f,	0.0f,	 1.0f
	};

	return matrix;
}

math::float4x4 ModuleRenderExercise::ProjectionMatrix()
{
	math::Frustum frustrum;
	frustrum.type = FrustumType::PerspectiveFrustum;

	frustrum.pos = float3::zero;
	frustrum.front = -float3::unitZ;
	frustrum.up = float3::unitY;

	frustrum.nearPlaneDistance = 0.1f;
	frustrum.farPlaneDistance = 100.0f;
	frustrum.verticalFov = NEULER / 4.0f;
	frustrum.horizontalFov = 1.0f * atanf(tanf(frustrum.verticalFov * 0.5f) * ASPECT);

	return frustrum.ProjectionMatrix();
}

// drawing grid
void ModuleRenderExercise::DrawPlane()
{
	math::float4x4 identity = math::float4x4::identity;
	glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_TRUE, &identity[0][0]);

	for (float i = -200; i < 200; i++)
	{
		if (i == 0) continue;
		if ((int)i % 5 == 0)
		{
			glLineWidth(2.0f);
			glUniform3f(glGetUniformLocation(program, "albedo"), 1.0f, 1.0f, 1.0f);
		}
		else
		{
			glLineWidth(1.0f);
			glUniform3f(glGetUniformLocation(program, "albedo"), 0.66f, 0.66f, 0.66f);
		}

		glBegin(GL_LINES);
		glVertex3f(i, 0.0f, -200.f);
		glVertex3f(i, 0.0f,  200.f);
		glEnd();

		glBegin(GL_LINES);
		glVertex3f(-200.f, 0.0f, i);
		glVertex3f( 200.f, 0.0f, i);
		glEnd();
	}

	glLineWidth(2.0f);
	glUniform3f(glGetUniformLocation(program, "albedo"), 1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0f, -200.f);
	glVertex3f(0.0f, 0.0f, 0.f);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0f, 1.f);
	glVertex3f(0.0f, 0.0f, 200.f);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(-200.f, 0.0f, 0.0f);
	glVertex3f(0.f, 0.0f, 0.0f);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(1.f, 0.0f, 0.0f);
	glVertex3f(200.f, 0.0f, 0.0f);
	glEnd();

	glLineWidth(2.f);
	glUniform3f(glGetUniformLocation(program, "albedo"), 1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);
	glEnd();

	glUniform3f(glGetUniformLocation(program, "albedo"), 0.0f, 1.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glEnd();

	glUniform3f(glGetUniformLocation(program, "albedo"), 0.0f, 0.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 1.0f);
	glEnd();
}*/
