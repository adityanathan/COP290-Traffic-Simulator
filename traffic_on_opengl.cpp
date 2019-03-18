#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}
void display()
{
  glBegin(GL_QUADS);
               glColor3f(1.0f, 0.0f, 1.0f); // make this vertex purple
               glVertex2f(-0.75, 0.75);
               glColor3f(1.0f, 0.0f, 0.0f); // make this vertex red
               glVertex2f(-0.75, -0.75);
               glColor3f(0.0f, 1.0f, 0.0f); // make this vertex green
               glVertex2f(0.75, -0.75);
               glColor3f(1.0f, 1.0f, 0.0f); // make this vertex yellow
               glVertex2f(0.75, 0.75);
       glEnd();
}
int main(void)
{
    GLFWwindow* window;
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        exit(EXIT_FAILURE);
    window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    while (!glfwWindowShouldClose(window))
    {
        float ratio;
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
      //  glRotatef((float) glfwGetTime() * 50.f, 0.f, 0.f, 1.f);
         //glColor3f(0.0, 1.0, 0.0);
         glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
      glColor3f(0.0, 1.0, 0.0); // Red
      glVertex2f(-1.5, 1.0);     // Define vertices in counter-clockwise (CCW) order
      glVertex2f(-1.5, 0.8);     //  so that the normal (front-face) is facing you
      glVertex2f( 1.5, 0.8);
      glVertex2f( 1.5, 1.0);

      glColor3f(0.0f, 1.0f, 0.0f); // Red
      glVertex2f(-1.5f, -1.0f);     // Define vertices in counter-clockwise (CCW) order
      glVertex2f(-1.5f, -0.8f);     //  so that the normal (front-face) is facing you
      glVertex2f( 1.5f, -0.8f);
      glVertex2f( 1.5f, -1.0f);
   glEnd();

   glFlush();
       //glutSwapBuffers();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
