#include "hw3.h"
#include "3rdparty/glad.h" // needs to be included before GLFW!
#include "3rdparty/glfw/include/GLFW/glfw3.h"
#include "hw3_scenes.h"

#include <glm-master/glm/glm.hpp>
#include <glm-master/glm/gtc/matrix_transform.hpp>
// #include <glm-master/glm/gtc/matrix_projection.hpp>

#include <glm-master/glm/gtc/type_ptr.hpp>


using namespace hw3;

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "// layout (location = 1) in vec2 aTexCoord;\n"

    "// out vec2 TexCoord;\n"
    "uniform mat4 transform;\n"
    "void main()\n"
    "{\n"
        "gl_Position = transform * vec4(aPos, 1.0);\n"
        "// TexCoord = vec2(aTexCoord.x, aTexCoord.y);\n"
    "}\0";

const char *fragShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
        "FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
    "}\0";


void resize_window(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}  

void processInput(GLFWwindow *window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}


// initialize openGL with version 3 and for apple
void hw_initialize_gl(){
    // initialize
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
}

void initialize_glad(){
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
    }   
}

GLFWwindow* newWindow(int height, int width, const char* name){
    GLFWwindow* window = glfwCreateWindow(height , width, name, NULL, NULL);

    // incase of error
    if (window == NULL){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    // put the window to current context
    glfwMakeContextCurrent(window);
    return window;
}

GLuint hw_compileShader(const char* source ,GLenum type){
    //create shader id
    GLuint ID = glCreateShader(type);
    // passin shader source code
    glShaderSource(ID, 1, &source, NULL );
    // compile and assign shader
    glCompileShader(ID);
    // check if shader successfully compiled
    int success = 0;
    char infoLog[512];
    glGetShaderiv(ID, GL_COMPILE_STATUS, &success);
    if (!(success)){
        glGetShaderInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::???::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    return ID;
}



GLuint hw_link_pragram(GLuint vertexShader, GLuint fragShader){
    GLuint shaderProgram =  glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragShader);
    glLinkProgram(shaderProgram);
    char infoLog[512];
    // check if linking works
    int success = 0;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::PROGRAM::SHADER_PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // delete used shader sources
    glDeleteShader(vertexShader);
    glDeleteShader(fragShader); 
    return shaderProgram;
}

void data_to_buffer(GLuint VAO, GLuint VBO,GLuint EBO, std::vector<TriangleMesh> meshes){

}

void hw_3_1(const std::vector<std::string> &params) {
    
    hw_initialize_gl();

    // create window obj
    GLFWwindow* window = newWindow(1280, 720, "hw 3_1");
    initialize_glad();

    while(!glfwWindowShouldClose(window)){
        // input
        processInput(window);
        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        // glfwSetFramebufferSizeCallback(window, resize_window);
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();    
    }
    glfwTerminate();
}

void hw_3_2(const std::vector<std::string> &params) {

    hw_initialize_gl();

    // create window
    GLFWwindow* window = newWindow(720, 720, "hw 3_2");
    initialize_glad();

    // compile shader
    GLuint vertexShader = hw_compileShader(vertexShaderSource ,GL_VERTEX_SHADER);
    GLuint fragShader = hw_compileShader(fragShaderSource ,GL_FRAGMENT_SHADER);
    
    // link the shade to program
    GLuint shaderProgram = hw_link_pragram(vertexShader, fragShader);
    

    // primitive input
    GLfloat vertices[] = {
    0.0f, 0.0f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.5f,  0.0f, 0.5f,
     -0.5f,  0.5f, 0.0f   
    }; 

    GLuint faces[] = {
        0 , 1 , 3,
        1 , 2 , 3,
        0, 2, 3
    };

    // gen VAO
    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO); //geneate a buffer with id
    glGenBuffers(1, &EBO); //geneate a buffer with id


    glBindVertexArray(VAO);
    // set vertex attributes pointers

    glBindBuffer(GL_ARRAY_BUFFER, VBO); // bind the buffer type
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); // bind the buffer type
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(faces), &faces, GL_STATIC_DRAW);

    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (void*)0);
    glEnableVertexAttribArray(0); 

    // unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0 );

    // render window
    while(!glfwWindowShouldClose(window)){
        // input
        processInput(window);
        // clear color buffer
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // create transformations
        glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

        // pass to shaderProgram
        glUseProgram(shaderProgram);
        unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

        // render the triangles
        glBindVertexArray(VAO);
        // glDrawArrays(GL_TRIANGLES, 1, 3); // draw one triangle
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
        glfwSetFramebufferSizeCallback(window, resize_window);
 
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();    
    }
    glfwTerminate();
}

/*
GLfloat v3vec_to_vert(std::vector<Vector3f> vertices){
    GLfloat VAO[sizeof(vertices) * 3];
    for (int i = 0; i < sizeof(vertices); i++){
        vertices[i] = (GLfloat)vertices[i].x;
    }
    return 
}
*/

glm::mat4 hw_convert_mat(Matrix4x4 m){
    glm::mat4 n;
    for(int i = 0; i < 4; i++){
    for(int j = 0; j < 4; j++){
        n[i][j] = m.data[i][j];
    }}
    return n;
}

void hw_3_3(const std::vector<std::string> &params) {
    if (params.size() == 0) {
        std::cout << "no args" << std::endl;
        return;
    }
    // parsing scene
    Scene scene = parse_scene(params[0]);
    std::cout << scene << std::endl;
    Camera camera = scene.camera;
    Vector3f background = scene.background;
    std::vector<TriangleMesh> meshes = scene.meshes;
    Real z_far = camera.z_far; Real z_near = camera.z_near;
    const float radius = z_far/10;
    Real height = camera.resolution.x;
    Real width = camera.resolution.y;
    Real s = camera.s;
    GLfloat aspect_ratio = (GLfloat) width / (GLfloat) height;

    
    hw_initialize_gl();

    // create window
    GLFWwindow* window = newWindow(height, width, "hw 3_3");
    initialize_glad();

    // compile shader
    Shader shader("hw3_3_vert.vs", "hw3_3_frag.fs");


    GLuint VAO[1];
    
    // gen VAO
    for (int i = 0; i < meshes.size(); i++){
        std::vector<Vector3f> vertices = meshes[i].vertices;
        std::vector<Vector3i> faces = meshes[i].faces;
        std::vector<Vector3f> colors = meshes[i].vertex_colors;
        glGenVertexArrays(1, &VAO[i]);
        glBindVertexArray(VAO[i]);
        GLuint VBO_vertex, VBO_color, EBO;

        glGenBuffers(1, &VBO_vertex); //geneate a buffer with id
        glBindBuffer(GL_ARRAY_BUFFER, VBO_vertex); // bind the buffer typel
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vector3f) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glGenBuffers(1, &VBO_color); //geneate a buffer with id
        glBindBuffer(GL_ARRAY_BUFFER, VBO_color); // bind the buffer typel
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vector3f) * colors.size(), colors.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);

        glGenBuffers(1, &EBO); //generate a buffer with id
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); // bind the buffer type
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, faces.size() * sizeof(Vector3i), faces.data(), GL_STATIC_DRAW);
    }
    // unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0 );


    Matrix4x4f proj = Matrix4x4f::identity();
    proj(0,0) = Real(1/(aspect_ratio*s));
    proj(1,1) = Real(1/(s));
    proj(2,2) = Real(-((z_far)/(z_far - z_near)));
    proj(2,3) = Real(-((z_far*z_near)/(z_far - z_near)));
    proj(3,2) = Real(-1);

    Matrix4x4f view = inverse(camera.cam_to_world);
    glm::mat4 v = hw_convert_mat(view);
  

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_FRAMEBUFFER_SRGB);
    // render window
    while(!glfwWindowShouldClose(window)){
        // input
        processInput(window);
        // clear color buffer
        glClearColor(background.x,background.y,background.z, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // create transformations
        // glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        // transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

        // use shaderProgram
        shader.use();

        // pass in matrices
        unsigned int projLoc = glGetUniformLocation(shader.ID, "projection");
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, proj.ptr());

        Vector3f obj = meshes[0].vertices[0];

        float camX = sin(glfwGetTime()) * radius;
        float camY = cos(glfwGetTime()) * radius;
        v = glm::lookAt(glm::vec3(obj.x + camX, obj.y + camY, obj.z ), glm::vec3(obj.x, obj.y, obj.z), glm::vec3(0.0, 0.0, 1.0)); 

        unsigned int viewLoc = glGetUniformLocation(shader.ID, "view");
        // glUniformMatrix4fv(viewLoc, 1, GL_FALSE, view.ptr());
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(v));

        // render the triangles
        for (int i = 0; i < meshes.size(); i++){
            TriangleMesh mesh = meshes[i];
            Matrix4x4f model = mesh.model_matrix;
            unsigned int modelLoc = glGetUniformLocation(shader.ID, "model");
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model.ptr());
            glBindVertexArray(VAO[i]);
            // glDrawArrays(GL_TRIANGLES, 1, 3); // draw one triangle
            glDrawElements(GL_TRIANGLES, 3 * mesh.faces.size(), GL_UNSIGNED_INT, 0);
            glfwSetFramebufferSizeCallback(window, resize_window);
        }

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();    
    }
    glfwTerminate();
}



void old_hw_3_3(const std::vector<std::string> &params) {
    if (params.size() == 0) {
        std::cout << "no args" << std::endl;
        return;
    }
    // parsing scene
    Scene scene = parse_scene(params[0]);
    std::cout << scene << std::endl;
    Camera camera = scene.camera;
    Vector3f background = scene.background;
    std::vector<TriangleMesh> meshes = scene.meshes;

    hw_initialize_gl();

    // create window
    GLFWwindow* window = newWindow(camera.resolution.x, camera.resolution.y, "hw 3_2");
    initialize_glad();

    // create shaderClass 
    Shader shader("hw3_3_vert.vs", "hw3_3_frag.fs");

    // pass meshes to VAOs
    GLuint VAO[meshes.size()];

    for (int i = 0; i < meshes.size(); i++){
        std::vector<Vector3f> vertices = meshes[i].vertices;
        std::vector<Vector3i> faces = meshes[i].faces;
        std::vector<Vector3f> colors = meshes[i].vertex_colors;
        glGenVertexArrays(1, &VAO[i]);
        glBindVertexArray(VAO[i]);
        GLuint VBO_vertex, VBO_color, EBO;

        glGenBuffers(1, &VBO_vertex); //geneate a buffer with id
        glBindBuffer(GL_ARRAY_BUFFER, VBO_vertex); // bind the buffer typel
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vector3f) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glGenBuffers(1, &VBO_color); //geneate a buffer with id
        glBindBuffer(GL_ARRAY_BUFFER, VBO_color); // bind the buffer typel
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vector3f) * colors.size(), colors.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);

        glGenBuffers(1, &EBO); //generate a buffer with id
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); // bind the buffer type
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, faces.size() * sizeof(Vector3i), faces.data(), GL_STATIC_DRAW);
    }

    // unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0 );

// forming matrices
    GLfloat aspect_ratio = (camera.resolution.x) / camera.resolution.y;
    Real z_far = camera.z_far; Real z_near = camera.z_near;

    Matrix4x4f v = inverse(camera.cam_to_world);
    glm::mat4 view = glm::mat4(1.0f); 

    view = hw_convert_mat(v);

    

    glm::mat4 projection(
                Real(1/(aspect_ratio*camera.resolution.y)), Real(0), Real(0), Real(0),
                Real(0), Real(1/ camera.resolution.y), Real(0), Real(0),
                Real(0), Real(0), Real(-((z_far)/(z_far - z_near))), Real(-((z_far * z_near)/(z_far - z_near))),
                Real(0), Real(0), Real(-1), Real(0));
                
    glm::mat4 model = glm::mat4(1.0f); 


/*
    // render window
    while(!glfwWindowShouldClose(window)){
        // input
        processInput(window);
        // clear color buffer
        glClearColor(background.x, background.y, background.z, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // activate shader
        shader.use();

        // pass in matrices
        unsigned int projLoc = glGetUniformLocation(shader.ID, "projection");
        // glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

        unsigned int viewLoc = glGetUniformLocation(shader.ID, "view");
        // glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        // render
        for (int i = 0; i < meshes.size(); i++){
            TriangleMesh mesh = meshes[i];
            // pass to shaderProgram
            model = hw_convert_mat(mesh.model_matrix);
            
            unsigned int modelLoc = glGetUniformLocation(shader.ID, "model");
            // glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

            glBindVertexArray(VAO[i]);
            glDrawElements(GL_TRIANGLES, 3 * mesh.faces.size(), GL_UNSIGNED_INT, 0);
            // glDrawArrays(GL_TRIANGLES, 1, 3); // draw one triangle

        }

        // render the triangle
        glfwSetFramebufferSizeCallback(window, resize_window);
 
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();    
    }*/

    // render window
    while(!glfwWindowShouldClose(window)){
        // input
        processInput(window);
        // clear color buffer
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // create transformations
        glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

        // pass to shaderProgram
        shader.use();
        unsigned int transformLoc = glGetUniformLocation(shader.ID, "model");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

        // render the triangles
        glBindVertexArray(VAO[0]);
        // glDrawArrays(GL_TRIANGLES, 1, 3); // draw one triangle
        glDrawElements(GL_TRIANGLES, meshes[0].faces.size() * 3, GL_UNSIGNED_INT, 0);
        glfwSetFramebufferSizeCallback(window, resize_window);
 
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();    
    }
    glfwTerminate();
    
}

void hw_3_4(const std::vector<std::string> &params) {
    // HW 3.4: Render a scene with lighting
    if (params.size() == 0) {
        return;
    }

    Scene scene = parse_scene(params[0]);
    std::cout << scene << std::endl;
}

