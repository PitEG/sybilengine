#include <glad/glad.h> 
#include <GLFW/glfw3.h> 

int main() {
  glfwInit();
  GLFWwindow* window = glfwCreateWindow(10, 10, "window", NULL, NULL);

  glfwDestroyWindow(window);
  glfwTerminate();
}
