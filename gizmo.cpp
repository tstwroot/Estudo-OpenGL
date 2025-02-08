#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <cmath>

// Camera variables
float cameraDistance = 5.0f;
float cameraAngleX = 0.0f;
float cameraAngleY = 0.0f;
bool mouseLeftDown = false;
double lastMouseX, lastMouseY;

void drawCone(float height, float radius, int segments) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(height, 0.0f, 0.0f); // Tip
    for (int i = 0; i <= segments; ++i) {
        float theta = 2.0f * M_PI * i / segments;
        float y = radius * cos(theta);
        float z = radius * sin(theta);
        glVertex3f(0.0f, y, z);
    }
    glEnd();
}

void drawGizmo() {
    // X-axis (Red)
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.8f, 0.0f, 0.0f);
    glEnd();
    glPushMatrix();
    glTranslatef(0.8f, 0.0f, 0.0f);
    drawCone(0.2f, 0.05f, 8);
    glPopMatrix();

    // Y-axis (Green)
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.8f, 0.0f);
    glEnd();
    glPushMatrix();
    glTranslatef(0.0f, 0.8f, 0.0f);
    glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
    drawCone(0.2f, 0.05f, 8);
    glPopMatrix();

    // Z-axis (Blue)
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.8f);
    glEnd();
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.8f);
    glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
    drawCone(0.2f, 0.05f, 8);
    glPopMatrix();
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        if (action == GLFW_PRESS) {
            mouseLeftDown = true;
            glfwGetCursorPos(window, &lastMouseX, &lastMouseY);
        } else if (action == GLFW_RELEASE) {
            mouseLeftDown = false;
        }
    }
}

void cursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
    if (mouseLeftDown) {
        float dx = static_cast<float>(xpos - lastMouseX);
        float dy = static_cast<float>(ypos - lastMouseY);
        cameraAngleY += dx * 0.5f;
        cameraAngleX += dy * 0.5f;
        lastMouseX = xpos;
        lastMouseY = ypos;
    }
}

void resizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float aspect = (float)width / (float)height;
    gluPerspective(45.0f, aspect, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

int main() {
    if (!glfwInit()) return -1;

    GLFWwindow* window = glfwCreateWindow(800, 600, "Cube with Gizmo", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, cursorPosCallback);
    glfwSetFramebufferSizeCallback(window, resizeCallback);

    glEnable(GL_DEPTH_TEST);

    // Initial resize
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    resizeCallback(window, width, height);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(cameraDistance, cameraDistance, cameraDistance, 0, 0, 0, 0, 1, 0);
        glRotatef(cameraAngleX, 1.0f, 0.0f, 0.0f);
        glRotatef(cameraAngleY, 0.0f, 1.0f, 0.0f);

        drawGizmo();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
