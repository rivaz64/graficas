#include <windows.h>

#include "imgui.h"

#ifdef directX
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#endif
#ifdef openGL

#include<glad\glad.h>
#define GLFW_INCLUDE_NONE
#include<glfw\glfw3.h>
#include<glfw\glfw3native.h>

#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#endif
#include "GraphicModule.h"
#include <string>
#include <iostream>
#include<vector>
#include"assimp\Importer.hpp"
#include"assimp\scene.h"
#include<algorithm>
#pragma comment(lib, "ComDlg32.lib")
#undef _DEBUG
using std::vector;
using std::string;
HWND g_hwnd=nullptr;
GraphicsModule::test MiObj;
GraphicsModule::Textura tx;
GraphicsModule::objeto pitola, pitola0, rana;
vector<GraphicsModule::objeto> objects;
GraphicsModule::mesh mesho;
char* nombre = new char[64];
int cual=0;
vector<string> filenames;
int inverted=0;
bool b[4] = { true,false,false,false };
string flagas[4] = { "normal","inverted","special","surprice" };
#ifdef directX
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
#endif
string openfilename(const char* filter = "All Files (*.*)\0*.*\0", HWND owner = NULL) {
    OPENFILENAME ofn;
    char fileName[MAX_PATH] = "";
    ZeroMemory(&ofn, sizeof(ofn));

    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = owner;
    ofn.lpstrFilter = filter;
    ofn.lpstrFile = fileName;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
    ofn.lpstrDefExt = "";

    string fileNameStr;

    if (GetOpenFileName(&ofn))
        fileNameStr = fileName;

    return fileNameStr;
}
LRESULT CALLBACK WndProc(HWND _hwnd, UINT _msg, WPARAM _wParam, LPARAM _lParam)
{
    // Handle UI inputs
#ifdef directX
    if (ImGui_ImplWin32_WndProcHandler(_hwnd, _msg, _wParam, _lParam))
        return 1;
#endif
    // Handle Window inputs
    switch (_msg)
    {
    case WM_SIZE:
#ifdef directX
        if (_wParam != SIZE_MINIMIZED && GraphicsModule::getmanager()->getSwapchain()->get()) {

            MiObj.rezise(_hwnd, _lParam);
        }
#endif
        return 0;
        break;

    case WM_SYSCOMMAND:
        if ((_wParam & 0xfff0) == SC_KEYMENU)
        {
            return 0;
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    }
    return ::DefWindowProc(_hwnd, _msg, _wParam, _lParam);
}


HRESULT InitImgUI()
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

#ifdef directX
    
    ImGui_ImplDX11_Init(GraphicsModule::getmanager()->getDevice()->get(), GraphicsModule::getmanager()->getConext()->get());
    ImGui_ImplWin32_Init(g_hwnd);
#endif
#ifdef openGL
    ImGui_ImplGlfw_InitForOpenGL(MiObj.window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
#endif
    return S_OK;
}
void loadModel() {
    GraphicsModule::Textura* tx = new GraphicsModule::Textura;
    
    GraphicsModule::model* mes = new GraphicsModule::model;
    Assimp::Importer importer;

    
    
    std::string estefile = openfilename();
    char drive[_MAX_DRIVE];
    char dir[_MAX_DIR];
    char ext[_MAX_EXT];
    char file[_MAX_FNAME];
    _splitpath_s(estefile.c_str(), drive, _MAX_DRIVE,dir, _MAX_DIR,file , _MAX_FNAME, ext, _MAX_EXT);
    string sfile = file;
    if (std::find(filenames.begin(), filenames.end(), sfile) == filenames.end()) {
        objects.push_back(GraphicsModule::objeto());
        filenames.push_back(sfile);
        const aiScene* scene = importer.ReadFile(estefile, NULL);
        int numvertices = 0;
        int numfaces = 0;
        std::string Filename = "";
        aiMesh* mesh;// = scene->mMeshes[0];
        aiString Path;
        for (int o = 0; o < scene->mNumMeshes; o++) {
            mesh = scene->mMeshes[o];
            mes->modelo.push_back(new GraphicsModule::mesh);

            mes->modelo[mes->modelo.size() - 1]->points = new GraphicsModule::mesh::vertex[mesh->mNumVertices];
            mes->modelo[mes->modelo.size() - 1]->indices = new unsigned int[mesh->mNumFaces * 3];
            for (int i = 0; i < mesh->mNumVertices; i++)
            {
                aiVector3D pos = mesh->mVertices[i];
                mes->modelo[mes->modelo.size() - 1]->points[i].posi[0] = pos.x;
                mes->modelo[mes->modelo.size() - 1]->points[i].posi[1] = pos.y;
                mes->modelo[mes->modelo.size() - 1]->points[i].posi[2] = pos.z;
                mes->modelo[mes->modelo.size() - 1]->points[i].normal[0] = mesh->mNormals[i].x;
                mes->modelo[mes->modelo.size() - 1]->points[i].normal[1] = mesh->mNormals[i].y;
                mes->modelo[mes->modelo.size() - 1]->points[i].normal[2] = mesh->mNormals[i].z;

                mes->modelo[mes->modelo.size() - 1]->points[i].uv[0] = mesh->mTextureCoords[0][i].x;

                mes->modelo[mes->modelo.size() - 1]->points[i].uv[1] = mesh->mTextureCoords[0][i].y;

            }
            for (int i = 0; i < mesh->mNumFaces; i++) {
                const aiFace& Face = mesh->mFaces[i];
                if (Face.mNumIndices == 3) {
                    mes->modelo[mes->modelo.size() - 1]->indices[i * 3] = i * 3;
                    mes->modelo[mes->modelo.size() - 1]->indices[i * 3 + 1] = i * 3 + 1;
                    mes->modelo[mes->modelo.size() - 1]->indices[i * 3 + 2] = i * 3 + 2;
                }
            }
            mes->modelo[mes->modelo.size() - 1]->init(mesh->mNumVertices, mesh->mNumFaces * 3);
            aiMaterial* siaimatirial = scene->mMaterials[scene->mMeshes[o]->mMaterialIndex];
            std::cout << 'a' << AI_SUCCESS << std::endl;
            for (int i = 1; i < aiTextureType_UNKNOWN; i++) {
                if (siaimatirial->GetTextureCount((aiTextureType)i) > 0) {
                    std::cout << (siaimatirial->GetTexture(aiTextureType(o), 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) << std::endl;
                    if (siaimatirial->GetTexture(aiTextureType(o), 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
                        char drive[_MAX_DRIVE];
                        char dir[_MAX_DIR];
                        char fname[_MAX_FNAME];
                        char ext[_MAX_EXT];



                        _splitpath_s(Path.data, drive, _MAX_DRIVE, dir, _MAX_DIR, fname, _MAX_FNAME, ext, _MAX_EXT);

                        Filename = fname;
                        Filename += ext;
                        break;
                    }
                }
            }
            tx->loadfromfile(Filename.c_str(), inverted);
            mes->modelo[mes->modelo.size() - 1]->tx = tx;
        }


        objects[objects.size() - 1].mod = mes;
        objects[objects.size() - 1].posi[0] = 3;
        objects[objects.size() - 1].posi[1] = 3;
        objects[objects.size() - 1].posi[2] = 3;
    }
    
}
void UIRender()
{
    // Start the Dear ImGui frame
#ifdef directX
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
#endif
#ifdef openGL
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
#endif
    ImGui::NewFrame();
    std::string name ="pitola";
    // example window
    if (ImGui::Begin("Another Window", nullptr))
    {
        if (ImGui::TreeNode("Directional Light")) {
            ImGui::DragFloat3("direction", MiObj.dl.dir, .001f, -1.f, 1.f);
            ImGui::ColorPicker4("color", MiObj.dl.color);
            ImGui::TreePop();
        }
        if (ImGui::TreeNode("Point Light")) {
            ImGui::DragFloat3("direction", MiObj.pl.pos, .001f, -1.f, 1.f);
            ImGui::DragFloat("attenuation", &MiObj.pl.att);
            ImGui::ColorPicker4("color", MiObj.pl.color);
            ImGui::TreePop();
        }
        for (int i = 0; i < filenames.size(); i++) {
            if (ImGui::Button(filenames[i].c_str()))
                cual = i;
        }

        if (cual >= 0 && cual < objects.size()) {
            ImGui::DragFloat3("location", objects[cual].posi, .001f);
            ImGui::DragFloat3("size", objects[cual].size, .001f);
            ImGui::DragFloat3("rotation", objects[cual].rot, .001f);
        }


        for (int i = 0; i < 4; i++) {
            ImGui::Selectable(flagas[i].c_str(), &b[i]);
            if (b[i]) {
                inverted = i;
                for (int o = 0; o < 4; o++) {
                    if (i != o) {
                        b[o] = false;
                    }
                }
            }
        }
        if (ImGui::Button("load moddel", ImVec2(100, 50))) {
            loadModel();
        }
        
        
        //ImGui::DragInt("inverted", &inverted);
        if (cual >= 0 && cual < objects.size()) {
            for (GraphicsModule::mesh* i : objects[cual].mod->modelo) {
                ImGui::Image((ImTextureID)i->tx->geter(), ImVec2(256, 256), ImVec2(0.0f, 0.0f), ImVec2(1.0f, 1.0f), ImVec4(1.0f, 1.0f, 1.0f, 1.0f), ImVec4(1.0f, 1.0f, 1.0f, 0.5f));
            }
        }
        /*for (GraphicsModule::objeto& i : objects) 
            ImGui::Image((ImTextureID)i.tx->geter(), ImVec2(256, 256), ImVec2(0.0f, 0.0f), ImVec2(1.0f, 1.0f), ImVec4(1.0f, 1.0f, 1.0f, 1.0f), ImVec4(1.0f, 1.0f, 1.0f, 0.5f));
    */}
    ImGui::End();

    // render UI
    ImGui::Render();
#ifdef directX
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
#endif
#ifdef openGL
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#endif
}



int main()
{
#ifdef openGL
    if (!glfwInit())
        return 1; 
    
    
#endif
    if (FAILED(MiObj.InitWindow(1280, 720, WndProc)))
    {
        DestroyWindow(g_hwnd);
        return 0;
    }
    g_hwnd=MiObj.g_hwnd;

    HRESULT hr=MiObj.InitDevice();
    if (FAILED(hr) || hr== S_FALSE)
    {
        MiObj.CleanupDevice();
        return 0;
    }

    // create UI
    if (FAILED(InitImgUI()))
    {
#ifdef directX
        ImGui_ImplDX11_Shutdown();
        ImGui_ImplWin32_Shutdown();
#endif
        
        ImGui::DestroyContext();
        return 0;
    }
    /*

    //*/

    /*unsigned int text=0;
    GraphicsModule::Textura bitco;
    bitco.loadfromfile("bitco.jpg");
    
    GraphicsModule::mesh triangle;
    triangle.setvertex({ 
   -1.0f, 1.0f, -1.0f, 0,0,
    1.0f, 1.0f, -1.0f,1.0f, 0.0f,
    1.0f, 1.0f, 1.0f,1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,0.0f, 1.0f,
    -1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
    1.0f, -1.0f, -1.0f, 1.0f, 0.0f,
    1.0f, -1.0f, 1.0f,1.0f, 1.0f,
    -1.0f, -1.0f, 1.0f,1.0f, 1.0f,
    -1.0f, -1.0f, 1.0f,0.0f, 0.0f,
    -1.0f, -1.0f, -1.0f,1.0f, 0.0f,
    -1.0f, 1.0f, -1.0f,1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,1.0f, 1.0f,
    1.0f, -1.0f, 1.0f,0.0f, 0.0f,
    1.0f, -1.0f, -1.0f,1.0f, 0.0f,
    1.0f, 1.0f, -1.0f,1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,1.0f, 1.0f,
    -1.0f, -1.0f, -1.0f,0.0f, 0.0f,
    1.0f, -1.0f, -1.0f,1.0f, 0.0f,
    1.0f, 1.0f, -1.0f,1.0f, 1.0f,
    -1.0f, 1.0f, -1.0f,1.0f, 1.0f,
    -1.0f, -1.0f, 1.0f,0.0f, 0.0f,
    1.0f, -1.0f, 1.0f,1.0f, 0.0f,
    1.0f, 1.0f, 1.0f,1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,1.0f, 1.0f,
        },24);
    triangle.setcolor({
     0.583f,  0.771f,  0.014f,
     0.609f,  0.115f,  0.436f,
     0.327f,  0.483f,  0.844f,
     0.822f,  0.569f,  0.201f,
     0.435f,  0.602f,  0.223f,
     0.310f,  0.747f,  0.185f,
     0.597f,  0.770f,  0.761f,
     0.559f,  0.436f,  0.730f,
     0.359f,  0.583f,  0.152f,
     0.483f,  0.596f,  0.789f,
     0.559f,  0.861f,  0.639f,
     0.195f,  0.548f,  0.859f,
     0.014f,  0.184f,  0.576f,
     0.771f,  0.328f,  0.970f,
     0.406f,  0.615f,  0.116f,
     0.676f,  0.977f,  0.133f,
     0.971f,  0.572f,  0.833f,
     0.140f,  0.616f,  0.489f,
     0.997f,  0.513f,  0.064f,
     0.945f,  0.719f,  0.592f,
     0.543f,  0.021f,  0.978f,
     0.279f,  0.317f,  0.505f,
     0.167f,  0.620f,  0.077f,
     0.347f,  0.857f,  0.137f,
        });
    triangle.setindices({
         3,1,0,
                2,1,3,

                6,4,5,
                7,4,6,

                11,9,8,
                10,9,11,

                14,12,13,
                15,12,14,

                19,17,16,
                18,17,19,

                22,20,21,
                23,20,22 },36);

    GraphicsModule::model tris;
    //GraphicsModule::model cubo;
    tris.modelo.push_back(&triangle);
    //cubo.modelo.push_back(&cube);
    GraphicsModule::objeto t;
    t.mod = &tris;
    t.tx = &bitco;
    //GraphicsModule::objeto c;
    //c.mod = &cubo;
//    glGenBuffers(1, &vertexB.buf);
// The following commands will talk about our 'vertexbuffer' buffer
    //glBindBuffer(GL_ARRAY_BUFFER, vertexB.buf);
// Give our vertices to OpenGL.
    //glBufferData((GLenum)vertexB.BindFlags, vertexB.ByteWidth, vertexB.Mem, (GLenum)vertexB.Usage);
    
    //triangulo.mod->modelo.push_back(&mesho);
     /*scene = importer.ReadFile(openfilename(), NULL);
     numvertices = 0;
     numfaces = 0;
    for (int i = 0; i < scene->mNumMeshes; i++) {
        numvertices += scene->mMeshes[i]->mNumVertices;
        numfaces += scene->mMeshes[i]->mNumFaces;
        //cout << numvertices << endl;
    }
    aiMesh* me;// = scene->mMeshes[0];
    //GraphicsModule::Textura tx;
    //tx.loadfromfile("pitola.dds");

    GraphicsModule::mesh meshh;

    meshh.points = new GraphicsModule::mesh::vertex[numvertices];
    meshh.indices = new int[numfaces * 3];
    numvertices = 0;
    numfaces = 0;
    for (int o = 0; o < scene->mNumMeshes; o++) {
        me = scene->mMeshes[o];
        for (int i = 0; i < me->mNumVertices; i++)
        {
            aiVector3D pos = me->mVertices[i];
            meshh.points[i + numvertices].posi[0] = pos.x;
            meshh.points[i + numvertices].posi[1] = pos.y;
            meshh.points[i + numvertices].posi[2] = pos.z;
            meshh.points[i + numvertices].normal[0] = me->mNormals[i].x;
            meshh.points[i + numvertices].normal[1] = me->mNormals[i].y;
            meshh.points[i + numvertices].normal[2] = me->mNormals[i].z;
            meshh.points[i + numvertices].uv[0] = me->mTextureCoords[0][i].x;
            meshh.points[i + numvertices].uv[1] = 1 - me->mTextureCoords[0][i].y;
        }
        numvertices += me->mNumVertices;
        for (int i = 0; i < me->mNumFaces; i++) {
            const aiFace& Face = me->mFaces[i];
            if (Face.mNumIndices == 3) {
                meshh.indices[i * 3 + numfaces * 3] = i * 3 + numfaces * 3;
                meshh.indices[i * 3 + 1 + numfaces * 3] = i * 3 + 1 + numfaces * 3;
                meshh.indices[i * 3 + 2 + numfaces * 3] = i * 3 + 2 + numfaces * 3;
            }
        }
        numfaces += me->mNumFaces;
    }



    meshh.init(numvertices, numfaces * 3);
    rana.mod = &mes;
    rana.posi.x= 10;
    rana.posi.y = 10;
    rana.posi.z = 10;*/
  // main loop
  MSG msg = { 0 };
  while (WM_QUIT != msg.message && MiObj.cerrar )
  {
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
    else
    {
        MiObj.Update();
        MiObj.clear();
        for (GraphicsModule::objeto& i : objects)
            MiObj.draw(i);
        UIRender();
        MiObj.Render();
        

    }
  }

  // clean resources
#ifdef directX
  ImGui_ImplDX11_Shutdown();
  ImGui_ImplWin32_Shutdown();
#endif
#ifdef openGL
  ImGui_ImplGlfw_Shutdown();
  ImGui_ImplOpenGL3_Shutdown();
#endif
  ImGui::DestroyContext();
  MiObj.CleanupDevice();
  
  return (int)msg.wParam;
}
/*
// -----------------Global var-----------------------------------------------------------------

//using namespace std;



extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND _hwnd, UINT _msg, WPARAM _wParam, LPARAM _lParam);

/**
 * @brief   Message bomb.
 * @param   #HWND: A handle to the window.
 * @param   #UINT: The message.
 * @param   #WPARAM: Additional message information. The contents of this parameter depend on the value of the uMsg parameter.
 * @param   #LPARAM: Additional message information. The contents of this parameter depend on the value of the uMsg parameter.
 * @return  #LRESULT: The return value is the result of the message processing and depends on the message sent..


/**
 * @brief   Set the style for the main window and init it.
 * @param   #unsigned int: First window width.
 * @param   #unsigned int: First window height.
 * @bug     No know Bugs.
 * @return  #HRESULT: Status code.


/**
 * @brief   Init the UI.
 * @bug     No know Bugs.
 * @return  #HRESULT: Status code.



/**
 * @brief   Entry point.
 * @bug     No know Bugs.
 * @return  #int: Status code.

//*/
