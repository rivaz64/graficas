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
vector<GraphicsModule::objeto*> objects;
GraphicsModule::mesh mesho;
char* nombre = new char[64];
string chnom = "qwerty";
char* nombrechader = new char[16];
int cual=0;
vector<string> filenames;
int inverted=0;
bool pixli,norli,pon,spek,blin,basic,reinhard;
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

std::string loadModel(string estefile, GraphicsModule::objeto*& obj) {
    GraphicsModule::Textura* tx;//= new GraphicsModule::Textura;
    obj = new GraphicsModule::objeto;
    GraphicsModule::model* mes = new GraphicsModule::model;
    //obj = new GraphicsModule::model;
    Assimp::Importer importer;

    
    
    //std::string estefile = openfilename();
    char drive[_MAX_DRIVE];
    char dir[_MAX_DIR];
    char ext[_MAX_EXT];
    char file[_MAX_FNAME];
    _splitpath_s(estefile.c_str(), drive, _MAX_DRIVE,dir, _MAX_DIR,file , _MAX_FNAME, ext, _MAX_EXT);
    string sfile = file;
    if (true/*std::find(filenames.begin(), filenames.end(), sfile) == filenames.end()*/) {
        //objects.push_back(new GraphicsModule::objeto);
        //filenames.push_back(sfile);
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
                if (mesh->HasNormals()) {
                    mes->modelo[mes->modelo.size() - 1]->points[i].normal[0] = mesh->mNormals[i].x;
                    mes->modelo[mes->modelo.size() - 1]->points[i].normal[1] = mesh->mNormals[i].y;
                    mes->modelo[mes->modelo.size() - 1]->points[i].normal[2] = mesh->mNormals[i].z;
                }
                if (mesh->HasTextureCoords(0)) {
                    mes->modelo[mes->modelo.size() - 1]->points[i].uv[0] = mesh->mTextureCoords[0][i].x;
                    mes->modelo[mes->modelo.size() - 1]->points[i].uv[1] = mesh->mTextureCoords[0][i].y;
                }
                

            }
            for (int i = 0; i < mesh->mNumFaces; i++) {
                const aiFace& Face = mesh->mFaces[i];
                if (Face.mNumIndices == 3) {
                    mes->modelo[mes->modelo.size() - 1]->indices[i * 3] = i * 3;
                    mes->modelo[mes->modelo.size() - 1]->indices[i * 3 + 1] = i * 3 + 1;
                    mes->modelo[mes->modelo.size() - 1]->indices[i * 3 + 2] = i * 3 + 2;
                    if (mesh->HasTextureCoords(0)) {
                        aiVector3D deltaPos1 = mesh->mVertices[i * 3 + 1] - mesh->mVertices[i * 3];
                        aiVector3D deltaPos2 = mesh->mVertices[i * 3 + 2] - mesh->mVertices[i * 3];
                        aiVector3D deltaUV1 = mesh->mTextureCoords[0][i * 3 + 1] - mesh->mTextureCoords[0][i * 3];
                        aiVector3D deltaUV2 = mesh->mTextureCoords[0][i * 3 + 2] - mesh->mTextureCoords[0][i * 3];
                        float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
                        aiVector3D tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y) * r;
                        aiVector3D bitangent = (deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x) * r;
                        mes->modelo[mes->modelo.size() - 1]->points[i * 3].binormal[0] = bitangent.x;
                        mes->modelo[mes->modelo.size() - 1]->points[i * 3].binormal[1] = bitangent.y;
                        mes->modelo[mes->modelo.size() - 1]->points[i * 3].binormal[2] = bitangent.z;
                        mes->modelo[mes->modelo.size() - 1]->points[i * 3 + 1].binormal[0] = bitangent.x;
                        mes->modelo[mes->modelo.size() - 1]->points[i * 3 + 1].binormal[1] = bitangent.y;
                        mes->modelo[mes->modelo.size() - 1]->points[i * 3 + 1].binormal[2] = bitangent.z;
                        mes->modelo[mes->modelo.size() - 1]->points[i * 3 + 2].binormal[0] = bitangent.x;
                        mes->modelo[mes->modelo.size() - 1]->points[i * 3 + 2].binormal[1] = bitangent.y;
                        mes->modelo[mes->modelo.size() - 1]->points[i * 3 + 2].binormal[2] = bitangent.z;
                        mes->modelo[mes->modelo.size() - 1]->points[i * 3].tangent[0] = tangent.x;
                        mes->modelo[mes->modelo.size() - 1]->points[i * 3].tangent[1] = tangent.y;
                        mes->modelo[mes->modelo.size() - 1]->points[i * 3].tangent[2] = tangent.z;
                        mes->modelo[mes->modelo.size() - 1]->points[i * 3 + 1].tangent[0] = tangent.x;
                        mes->modelo[mes->modelo.size() - 1]->points[i * 3 + 1].tangent[1] = tangent.y;
                        mes->modelo[mes->modelo.size() - 1]->points[i * 3 + 1].tangent[2] = tangent.z;
                        mes->modelo[mes->modelo.size() - 1]->points[i * 3 + 2].tangent[0] = tangent.x;
                        mes->modelo[mes->modelo.size() - 1]->points[i * 3 + 2].tangent[1] = tangent.y;
                        mes->modelo[mes->modelo.size() - 1]->points[i * 3 + 2].tangent[2] = tangent.z;

                    }

                }
            
            }

            mes->modelo[mes->modelo.size() - 1]->init(mesh->mNumVertices, mesh->mNumFaces * 3);
            aiMaterial* siaimatirial;// = scene->mMaterials[scene->mMeshes[o]->mMaterialIndex];
            for (int u = 0; u < scene->mNumMaterials; u++) {
                siaimatirial = scene->mMaterials[u];
                for (int i = 1; i < aiTextureType_UNKNOWN; i++) {
                    if (siaimatirial->GetTextureCount((aiTextureType)i) > 0) {
                        //std::cout << (siaimatirial->GetTexture(aiTextureType(o), 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) << std::endl;
                        if (siaimatirial->GetTexture(aiTextureType(o), 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
                            char drive[_MAX_DRIVE];
                            char dir[_MAX_DIR];
                            char fname[_MAX_FNAME];
                            char ext[_MAX_EXT];



                            _splitpath_s(Path.data, drive, _MAX_DRIVE, dir, _MAX_DIR, fname, _MAX_FNAME, ext, _MAX_EXT);
                            std::cout << fname << std::endl;
                            Filename = fname;
                            Filename += ext;
                            tx = new GraphicsModule::Textura;
                            tx->loadfromfile(Filename.c_str(), inverted,GraphicsModule::SRV_DIMENSION::TEXTURE2D);
                            //mes->modelo[mes->modelo.size() - 1]
                            obj->material.push_back(tx);
                            //break;
                        }
                    }
                }
            }
            //std::cout << 'a' << AI_SUCCESS << std::endl;
            
            
        }


        obj->mod = mes;
        if (objects.size() > 1)
            MiObj.fpl = objects[1];
        if (objects.size() > 2)
            MiObj.fsl = objects[2];
        return sfile;
        /*if (objects.size() > 3)
            MiObj.pases[0].objts.push_back(&objects[objects.size()-1]);*/
    }
    
}
void loadModel(string estefile) {
    objects.push_back(NULL);
    filenames.push_back(loadModel(estefile, objects[objects.size() - 1]));
}
void loadModel(string estefile, string name) {
    loadModel(estefile);
    filenames[filenames.size() - 1] = name;
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
    if (ImGui::Begin("objetos", nullptr))
    {
        
        for (int i = 0; i < filenames.size()-3; i++) {
            if (ImGui::Button(filenames[i+3].c_str()))
                cual = i+3;
        }
        if (cual >= 0 && cual < objects.size()) {
            ImGui::DragFloat3("location", objects[cual]->posi, .001f);
            ImGui::DragFloat3("size", objects[cual]->size, .001f);
            ImGui::DragFloat3("rotation", objects[cual]->rot, .1f);
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
            loadModel(openfilename());
        }
        
        
        //ImGui::DragInt("inverted", &inverted);
        /*if (cual >= 0 && cual < objects.size()) {
            for (GraphicsModule::mesh* i : objects[cual].mod->modelo) {
                ImGui::Image((ImTextureID)i->material[0]->geter(), ImVec2(256, 256), ImVec2(0.0f, 0.0f), ImVec2(1.0f, 1.0f), ImVec4(1.0f, 1.0f, 1.0f, 1.0f), ImVec4(1.0f, 1.0f, 1.0f, 0.5f));
            }
        }*/
        /*for (GraphicsModule::objeto& i : objects) 
            ImGui::Image((ImTextureID)i.tx->geter(), ImVec2(256, 256), ImVec2(0.0f, 0.0f), ImVec2(1.0f, 1.0f), ImVec4(1.0f, 1.0f, 1.0f, 1.0f), ImVec4(1.0f, 1.0f, 1.0f, 0.5f));
    */}
    ImGui::End();
    if (ImGui::Begin("lights", nullptr)) {
        if (ImGui::TreeNode("Ambience Light")) {
            ImGui::DragFloat("intencity", &MiObj.al.k, .001f);
            ImGui::ColorPicker4("color", MiObj.al.color);
            ImGui::TreePop();
        }
        if (ImGui::TreeNode("Directional Light")) {
            ImGui::DragFloat3("direction", MiObj.dl.dir, .001f, -1.f, 1.f);
            ImGui::ColorPicker4("color", MiObj.dl.color);
            ImGui::TreePop();
        }
        if (ImGui::TreeNode("Point Light")) {
            ImGui::DragFloat3("position", MiObj.pl.pos, .001f);
            ImGui::DragFloat("attenuation", &MiObj.pl.att, .001f);
            ImGui::ColorPicker4("color", MiObj.pl.color);
            ImGui::TreePop();
        }
        if (ImGui::TreeNode("Spot Light")) {
            ImGui::DragFloat3("direction", MiObj.sl.Dir, .001f, -1.f, 1.f);
            ImGui::DragFloat3("position", MiObj.sl.Pos, .001f);
            ImGui::DragFloat("attenuation", &MiObj.sl.Att, .001f);
            ImGui::DragFloat("radious", &MiObj.sl.Rad, .001f);
            ImGui::DragFloat("difucion", &MiObj.sl.dif, .001f);
            ImGui::ColorPicker4("color", MiObj.sl.Color);
            ImGui::TreePop();
        }
        
    }
    ImGui::End();
    if (ImGui::Begin("shaders", nullptr)) {
        if (ImGui::TreeNode("Light")) {
            ImGui::DragInt("chader", &MiObj.actual->chadernum, .01f, 0, 2);
            //ImGui::InputText("name",nombrechader,sizeof(nombrechader));
            ImGui::Checkbox("pixelight", &pixli);
            MiObj.actual->chadernum = 0;
            if (pixli) {
                MiObj.actual->chadernum = 1;
                ImGui::Checkbox("Normal map", &norli);
                ImGui::Checkbox("Phong", &pon);
                if (norli)
                    MiObj.actual->chadernum += 1;
                if (pon) {
                    MiObj.actual->chadernum += 2;
                    ImGui::DragFloat("shinines", &MiObj.shinines, .001f);
                    ImGui::Checkbox("Specular Map", &spek);
                    if (spek) {
                        MiObj.actual->chadernum += 2;
                    }
                    else {
                        ImGui::DragFloat("specular", &MiObj.specular, .001f);
                    }
                    ImGui::Checkbox("blinn", &blin);
                    if (blin) {
                        MiObj.actual->chadernum += 4;
                    }
                }
            }
            ImGui::TreePop();
        }
        if (ImGui::TreeNode("defered")) {
            ImGui::Checkbox("Gbuf", &MiObj.gbuf);
            if (MiObj.gbuf) {
                ImGui::DragInt("Gbufer", &MiObj.Gbuffer.outnum, .006f, 0, 3);
            }
            ImGui::Checkbox("lightson", &MiObj.lightson);
            /*if (MiObj.gbuf) {
                ImGui::DragInt("Gbufer", &MiObj.Gbuffer.outnum, .006f, 0, 3);
            }*/
            ImGui::Checkbox("Ambient Oclucion", &MiObj.sao);
            if (MiObj.sao) {
                ImGui::DragFloat("Sample Radius", &MiObj.amoc.sampleRadius, .001f);
                ImGui::DragFloat("Scale", &MiObj.amoc.scale, .001f);
                ImGui::DragFloat("Bias", &MiObj.amoc.bias, .001f);
                ImGui::DragFloat("Intensity", &MiObj.amoc.intensity, .001f);
                ImGui::DragInt("Sample Iterations", &MiObj.amoc.sampleIterations, .036f);
            }
            ImGui::Checkbox("acitve", &MiObj.deferar);
            if (MiObj.deferar) {
                ImGui::DragFloat("exposure", &MiObj.exp, .001f);
                ImGui::DragFloat("exponent", &MiObj.expo, .001f);
                ImGui::DragInt("defe", &MiObj.tonemap.chadernum, .006f, 0, 5);
                
            }
            ImGui::Checkbox("SkyBox", &MiObj.isky);
            ImGui::TreePop();
        }
        

    }
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
    
    //nombrechader = "qwerty";
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
    loadModel("D:/github/graficas/Graficos1/Graficos1/bin/Sphere.3ds",MiObj.skypox);
    MiObj.skypox->material.push_back(new GraphicsModule::Textura);
    MiObj.skypox->material[0]->loadfromfile("Snow.dds", false, GraphicsModule::SRV_DIMENSION::TEXTURECUBE);
    /*D3DX11_IMAGE_LOAD_INFO loadSMInfo;
    loadSMInfo.MiscFlags = D3D11_RESOURCE_MISC_TEXTURECUBE;
    D3DX11CreateTextureFromFile(GraphicsModule::getmanager()->getDevice()->get(), "Earth.dds",
        &loadSMInfo, 0, (ID3D11Resource**)&MiObj.skypox->material[0]->get, 0);*/
    loadModel("D:/github/graficas/Graficos1/Graficos1/bin/3D_model_of_a_Cube.stl","origin");
    for (int i = 0; i < 3; i++) {
        objects[0]->size[i] = .002f;
    }
    loadModel("D:/github/graficas/Graficos1/Graficos1/bin/3D_model_of_a_Cube.stl", "pointlight");
    for (int i = 0; i < 3; i++) {
        objects[1]->size[i] = .002f;
    }
    loadModel("D:/github/graficas/Graficos1/Graficos1/bin/3D_model_of_a_Cube.stl", "spotlight");
    for (int i = 0; i < 3; i++) {
        objects[2]->size[i] = .002f;
    }
    
    
    //MiObj.fpl = &objects[1];
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
        MiObj.draw(objects);
        /*for (GraphicsModule::objeto* i : objects)
            MiObj.draw(i);*/
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
  for (GraphicsModule::objeto* o : objects) {
      delete o;
  }
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
