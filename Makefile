CXX = g++
CXXFLAGS = -std=c++17 -Wall -Isrc

SRCS = main.cpp \
       src/models/Book.cpp \
       src/models/DVD.cpp \
       src/models/Magazine.cpp \
       src/models/LibraryItem.cpp \
       src/models/ItemState.cpp \
       src/models/ItemFactory.cpp \
       src/models/Student.cpp \
       src/policy/FeePolicy.cpp \
       src/events/NotificationCenter.cpp \
       src/events/ConsoleAuditObserver.cpp \
       src/services/Authenticator.cpp \
       src/services/StudentService.cpp \
       src/services/CatalogService.cpp \
       src/services/CirculationService.cpp \
       src/services/LibraryService.cpp \
       src/ui/Console.cpp \
       src/ui/ConsoleUI.cpp

TARGET = library.exe

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

clean:
	del /f /q $(TARGET) 2>nul || exit 0

.PHONY: clean
