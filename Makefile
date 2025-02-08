EXE = main
IMGUI_DIR = ./third-party/imgui
SOURCES = main.cpp
SOURCES += $(IMGUI_DIR)/imgui.cpp $(IMGUI_DIR)/imgui_demo.cpp $(IMGUI_DIR)/imgui_draw.cpp $(IMGUI_DIR)/imgui_tables.cpp $(IMGUI_DIR)/imgui_widgets.cpp
SOURCES += $(IMGUI_DIR)/backends/imgui_impl_glfw.cpp $(IMGUI_DIR)/backends/imgui_impl_opengl3.cpp
	SOURCES += camera.cpp graphics.cpp mesh.cpp shaders.cpp
OBJS = $(addsuffix .o, $(basename $(notdir $(SOURCES))))

CXXFLAGS = -std=c++11 -I$(IMGUI_DIR) -I$(IMGUI_DIR)/backends
CXXFLAGS += -g -Wall -Wformat -std=c++20
LIBS = -lglfw -L/usr/lib64 -lGLEW -lGL -lX11 -lGLU

all: $(EXE)
	./$(EXE)

debug: $(EXE)
	./$(EXE)
	rm -f $(EXE) $(OBJS)

$(EXE): $(OBJS)
	$(CXX) $^ -o $@ $(CXXFLAGS) $(LIBS)

%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

%.o: $(IMGUI_DIR)/%.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

%.o: $(IMGUI_DIR)/backends/%.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

clean:
	rm -f $(EXE) $(OBJS) imgui.ini
