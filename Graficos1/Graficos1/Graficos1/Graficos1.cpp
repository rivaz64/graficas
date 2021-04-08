#include <windows.h>

#include "imgui.h"
#include "imgui_impl_win32.h"
#ifdef directX
#include "imgui_impl_dx11.h"
#endif
#ifdef openGL

#include<glad\glad.h>
#define GLFW_INCLUDE_NONE
#include<glfw\glfw3.h>
#include<glfw\glfw3native.h>
#endif
#include "GraphicModule.h"
#include <string>
#include <iostream>

#include"assimp\Importer.hpp"
#include"assimp\scene.h"

/*#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"*/
//#include <GLFW/glfw3.h>
#pragma comment(lib, "ComDlg32.lib")
HWND g_hwnd=nullptr;
GraphicsModule::test MiObj;
GraphicsModule::Textura tx;
GraphicsModule::objeto pitola, pitola0, rana;
GraphicsModule::mesh mesho;

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
    /*if (ImGui_ImplWin32_WndProcHandler(_hwnd, _msg, _wParam, _lParam))
        return 1;*/

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

    // Setup Platform/Renderer back ends
    ImGui_ImplWin32_Init(g_hwnd);
#ifdef directX
    ImGui_ImplDX11_Init(GraphicsModule::getmanager()->getDevice()->get(), GraphicsModule::getmanager()->getConext()->get());
#endif
    return S_OK;
}

void UIRender()
{
    // Start the Dear ImGui frame
#ifdef directX
    ImGui_ImplDX11_NewFrame();
#endif
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    // example window
    if (ImGui::Begin("Another Window", nullptr))
    {
        ImGui::DragFloat3("light", MiObj.dirly, .001f, -1.f, 1.f);
        //ImGui::Image(pitola.tx->srv, ImVec2(256, 256), ImVec2(0.0f, 0.0f), ImVec2(1.0f, 1.0f), ImVec4(1.0f, 1.0f, 1.0f, 1.0f), ImVec4(1.0f, 1.0f, 1.0f, 0.5f));
    }
    ImGui::End();

    // render UI
    ImGui::Render();
#ifdef directX
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
#endif
}



int main()
{
#ifdef openGL
    if (!glfwInit())
        return 1; 
    
    
#endif
        // create the window and console
    
    if (FAILED(MiObj.InitWindow(1280, 720)))
    {
        DestroyWindow(g_hwnd);
        return 0;
    }


    // create Graphic API interface
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
#endif
        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();
        return 0;
    }
#ifdef directX
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(openfilename(), NULL);
    int numvertices = 0;
    int numfaces = 0;
    for (int i = 0; i < scene->mNumMeshes; i++) {
        numvertices += scene->mMeshes[i]->mNumVertices;
        numfaces += scene->mMeshes[i]->mNumFaces;
        //cout << numvertices << endl;
    }
    aiMesh* mesh;// = scene->mMeshes[0];
    GraphicsModule::Textura tx;
    tx.loadfromfile("pitola.dds");

    GraphicsModule::model mes;

    //mes.points = new GraphicsModule::mesh::vertex[numvertices];
    //mes.indices = new int[numfaces * 3];
    numvertices = 0;
    numfaces = 0;
    for (int o = 0; o < scene->mNumMeshes; o++) {
        mesh = scene->mMeshes[o];
        mes.modelo.push_back(new GraphicsModule::mesh);
        mes.modelo[mes.modelo.size()-1]->points= new GraphicsModule::mesh::vertex[mesh->mNumVertices];
        mes.modelo[mes.modelo.size() - 1]->indices= new int[mesh->mNumFaces * 3];
        for (int i = 0; i < mesh->mNumVertices; i++)
        {
            aiVector3D pos = mesh->mVertices[i];
            mes.modelo[mes.modelo.size() - 1]->points[i].posi[0] = pos.x;
            mes.modelo[mes.modelo.size() - 1]->points[i].posi[1] = pos.y;
            mes.modelo[mes.modelo.size() - 1]->points[i].posi[2] = pos.z;
            mes.modelo[mes.modelo.size() - 1]->points[i].normal[0] = mesh->mNormals[i].x;
            mes.modelo[mes.modelo.size() - 1]->points[i].normal[1] = mesh->mNormals[i].y;
            mes.modelo[mes.modelo.size() - 1]->points[i].normal[2] = mesh->mNormals[i].z;

            mes.modelo[mes.modelo.size() - 1]->points[i].uv[0] = mesh->mTextureCoords[0][i].x;
            mes.modelo[mes.modelo.size() - 1]->points[i].uv[1] = 1-mesh->mTextureCoords[0][i].y;
        }
        for (int i = 0; i < mesh->mNumFaces; i++) {
            const aiFace& Face = mesh->mFaces[i];
            if (Face.mNumIndices == 3) {
                mes.modelo[mes.modelo.size() - 1]->indices[i * 3] = i * 3 ;
                mes.modelo[mes.modelo.size() - 1]->indices[i * 3 + 1] = i * 3 +1;
                mes.modelo[mes.modelo.size() - 1]->indices[i * 3 + 2] = i * 3 +2;
            }
        }
        mes.modelo[mes.modelo.size() - 1]->init(mesh->mNumVertices, mesh->mNumFaces * 3);
    }
    pitola.mod = &mes;
    pitola.tx = &tx;
    pitola0.mod = &mes;
    pitola0.tx = &tx;
    pitola.posi.x = 3;
#endif



   
    GraphicsModule::mesh triangle;
    triangle.setvertex({
   -1.0f, -1.0f, 0.0f,
   1.0f, -1.0f, 0.0f,
   0.0f,  1.0f, 0.0f,
        },3);
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
#ifdef directX
        MiObj.draw(pitola);
#endif
#ifdef openGL
        MiObj.draw(triangle);
#endif
        MiObj.Render();
        

    }
  }

  // clean resources
#ifdef directX
  ImGui_ImplDX11_Shutdown();
#endif
  ImGui_ImplWin32_Shutdown();
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
