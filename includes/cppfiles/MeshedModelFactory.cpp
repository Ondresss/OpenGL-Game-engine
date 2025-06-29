#include "../headers/MeshedModelFactory.h"

std::vector<Mesh> MeshedModelFactory::loadMeshes(const std::string& name) {

     Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(name, aiProcess_Triangulate | aiProcess_OptimizeMeshes | aiProcess_FlipUVs);

    std::vector<Mesh> meshDataList;

    if (scene && scene->HasMeshes()) {
        printf("scene->mNumMeshes = %d\n", scene->mNumMeshes);

        for (unsigned int i = 0; i < scene->mNumMeshes; i++) {
            aiMesh* mesh = scene->mMeshes[i];

            // Allocate and populate vertices
            Vertex* pVertices = new Vertex[mesh->mNumVertices];
            std::memset(pVertices, 0, sizeof(Vertex) * mesh->mNumVertices);

            for (unsigned int j = 0; j < mesh->mNumVertices; j++) {
                if (mesh->HasPositions()) {
                    pVertices[j].Position[0] = mesh->mVertices[j].x;
                    pVertices[j].Position[1] = mesh->mVertices[j].y;
                    pVertices[j].Position[2] = mesh->mVertices[j].z;
                }
                if (mesh->HasNormals()) {
                    pVertices[j].Normal[0] = mesh->mNormals[j].x;
                    pVertices[j].Normal[1] = mesh->mNormals[j].y;
                    pVertices[j].Normal[2] = mesh->mNormals[j].z;
                }
                if (mesh->HasTextureCoords(0)) {
                    pVertices[j].Texture[0] = mesh->mTextureCoords[0][j].x;
                    pVertices[j].Texture[1] = mesh->mTextureCoords[0][j].y;
                }
                if (mesh->HasTangentsAndBitangents()) {
                    pVertices[j].Tangent[0] = mesh->mTangents[j].x;
                    pVertices[j].Tangent[1] = mesh->mTangents[j].y;
                    pVertices[j].Tangent[2] = mesh->mTangents[j].z;
                }
            }

            // Allocate and populate indices
            unsigned int* pIndices = nullptr;
            unsigned int indexCount = 0;
            if (mesh->HasFaces()) {
                indexCount = mesh->mNumFaces * 3;
                pIndices = new unsigned int[indexCount];
                for (unsigned int j = 0; j < mesh->mNumFaces; j++) {
                    const aiFace& face = mesh->mFaces[j];
                    pIndices[j * 3] = face.mIndices[0];
                    pIndices[j * 3 + 1] = face.mIndices[1];
                    pIndices[j * 3 + 2] = face.mIndices[2];
                }
            }

            Mesh meshData;
            glGenVertexArrays(1, &meshData.VAO);
            glGenBuffers(1, &meshData.VBO);
            glGenBuffers(1, &meshData.IBO);

            glBindVertexArray(meshData.VAO);

            glBindBuffer(GL_ARRAY_BUFFER, meshData.VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * mesh->mNumVertices, pVertices, GL_STATIC_DRAW);

            glEnableVertexAttribArray(0); // Position
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(0));
            glEnableVertexAttribArray(1); // Normal
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(3 * sizeof(GLfloat)));
            glEnableVertexAttribArray(2); // Texture
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(6 * sizeof(GLfloat)));
            glEnableVertexAttribArray(3); // Tangent
            glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(8 * sizeof(GLfloat)));

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshData.IBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indexCount, pIndices, GL_STATIC_DRAW);

            glBindVertexArray(0);

            meshData.indexCount = indexCount;
            meshDataList.push_back(meshData);

            delete[] pVertices;
            delete[] pIndices;
        }
    } else {
        std::cerr << "Failed to load file: " << name << std::endl;
    }

    return meshDataList;

}

MeshedModel* MeshedModelFactory::loadModel(const std::string& name) {
    std::vector<Mesh> meshes(MeshedModelFactory::loadMeshes(name)); 
    MeshedModel* meshed_model = new MeshedModel(meshes);

    return meshed_model;
}