.SUFFIXES: .cpp .hpp

# Programs
SHELL 	= bash
CC     	= g++
LD	= ld
RM 	= rm
ECHO	= /bin/echo
CAT	= cat
PRINTF	= printf
SED	= sed
DOXYGEN = doxygen
######################################
# Project Name (generate executable with this name)
TARGET = cs296_base

# Project Paths
PROJECT_ROOT=$(HOME)/cs296_base_code
EXTERNAL_ROOT=$(PROJECT_ROOT)/external
SRCDIR = $(PROJECT_ROOT)/src
OBJDIR = $(PROJECT_ROOT)/obj
BINDIR = $(PROJECT_ROOT)/bin
DOCDIR = $(PROJECT_ROOT)/doc
SCRIPTDIR =$(PROJECT_ROOT)/scripts
INSTALL_PATH=$(PROJECT_ROOT)/install


# Library Paths
BOX2D_ROOT=$(EXTERNAL_ROOT)
GLUI_ROOT=/usr
GL_ROOT=/usr

#Libraries
LIBS = -lBox2D -lglui -lglut -lGLU -lGL

# Compiler and Linker flags
CPPFLAGS =-g -O3 -Wall 
CPPFLAGS+=-I $(BOX2D_ROOT)/include -I $(GLUI_ROOT)/include
LDFLAGS+=-L $(BOX2D_ROOT)/lib -L $(GLUI_ROOT)/lib

######################################

NO_COLOR=\e[0m
OK_COLOR=\e[1;32m
ERR_COLOR=\e[1;31m
WARN_COLOR=\e[1;33m
MESG_COLOR=\e[1;34m
FILE_COLOR=\e[1;37m

OK_STRING="[OK]"
ERR_STRING="[ERRORS]"
WARN_STRING="[WARNINGS]"
OK_FMT="${OK_COLOR}%30s\n${NO_COLOR}"
ERR_FMT="${ERR_COLOR}%30s\n${NO_COLOR}"
WARN_FMT="${WARN_COLOR}%30s\n${NO_COLOR}"
######################################

SRCS := $(wildcard $(SRCDIR)/*.cpp)
INCS := $(wildcard $(SRCDIR)/*.hpp)
OBJS := $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)


.PHONY: all setup doc clean distclean

all: setup $(BINDIR)/$(TARGET)

setup:
	@$(ECHO) "Setting up compilation..."
	@mkdir -p obj
	@mkdir -p bin
	@mkdir -p data
	@mkdir -p plots



exe: all


$(BINDIR)/$(TARGET): $(EXTERNAL_ROOT)/lib/libBox2D.a $(OBJS)
	@$(PRINTF) "$(MESG_COLOR)Building executable:$(NO_COLOR) $(FILE_COLOR) %16s$(NO_COLOR)" "$(notdir $@)"
	@$(CC) -o $@ $(LDFLAGS) $(OBJS) $(LIBS) 2> temp.log || touch temp.err
	@if test -e temp.err; \
	then $(PRINTF) $(ERR_FMT) $(ERR_STRING) && $(CAT) temp.log; \
	elif test -s temp.log; \
	then $(PRINTF) $(WARN_FMT) $(WARN_STRING) && $(CAT) temp.log; \
	else $(PRINTF) $(OK_FMT) $(OK_STRING); \
	fi;
	@$(RM) -f temp.log temp.err

-include $(OBJS:.o=.d)

$(OBJS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@$(PRINTF) "$(MESG_COLOR)Compiling: $(NO_COLOR) $(FILE_COLOR) %25s$(NO_COLOR)" "$(notdir $<)"
	@$(CC) $(CPPFLAGS) -c $< -o $@ -MD 2> temp.log || touch temp.err
	@if test -e temp.err; \
	then $(PRINTF) $(ERR_FMT) $(ERR_STRING) && $(CAT) temp.log; \
	elif test -s temp.log; \
	then $(PRINTF) $(WARN_FMT) $(WARN_STRING) && $(CAT) temp.log; \
	else printf "${OK_COLOR}%30s\n${NO_COLOR}" "[OK]"; \
	fi;
	@$(RM) -f temp.log temp.err



$(EXTERNAL_ROOT)/lib/libBox2D.a:
	@$(ECHO) -n "Compiling Box2D ...  "
	@cd $(PROJECT_ROOT)/external/src/ ; tar zxvf Box2D.tgz
	@cd $(PROJECT_ROOT)/external/src/Box2D ; mkdir build296
	@cd $(PROJECT_ROOT)/external/src/Box2D/build296 ; cmake ../ ; make ; make install




report:
	@latex $(DOCDIR)/report.tex
	@bibtex report.aux
	@latex $(DOCDIR)/report.tex
	@latex $(DOCDIR)/report.tex
	@dvipdf $(PROJECT_ROOT)/report.dvi $(DOCDIR)/report.pdf	
	@$(RM) -rf  $(PROJECT_ROOT)/report.*
	@python3 $(SCRIPTDIR)/g12_gen_html.py



doc:
	@$(ECHO) -n "Generating Doxygen Documentation ...  "
	@$(RM) -rf doc/html
	@$(DOXYGEN) $(DOCDIR)/Doxyfile 2 > /dev/null
	@$(ECHO) "Done"



clean:
	@$(ECHO) -n "Cleaning up..."
	@$(RM) -rf $(OBJDIR) *~ $(DEPS) $(SRCDIR)/*~ $(DOCDIR)/*.log $(DOCDIR)/*.dvi $(DOCDIR)/*.aux 
	@$(RM) -rf $(DOCDIR)/*.pdf $(DOCDIR)/*.ps $(DOCDIR)/*html $(DOCDIR)/html $(BINDIR) $(PROJECT_ROOT)/data $(PROJECT_ROOT)/plots
	@$(RM) -rf $(PROJECT_ROOT)/*.aux $(PROJECT_ROOT)/*.log $(PROJECT_ROOT)/*.bbl $(PROJECT_ROOT)/*.blg $(PROJECT_ROOT)/*.dvi $(PROJECT_ROOT)/*.pdf	
	@$(ECHO) "Done" 





distclean: clean
	@$(RM) -rf $(EXTERNAL_ROOT)/lib/* $(EXTERNAL_ROOT)/include/* $(EXTERNAL_ROOT)/src/Box2D
	@$(RM) -rf $(INSTALL_PATH)



dist: distclean
	@$(RM) -rf ../cs296_g12_project.tar.gz
	@tar zcvf ../cs296_g12_project.tar.gz ../cs296_base_code



install: report doc setup $(BINDIR)/$(TARGET)
	@$(RM) -rf $(INSTALL_PATH)
	@mkdir -p $(INSTALL_PATH)
	@mkdir -p $(INSTALL_PATH)/bin
	@cp $(BINDIR)/$(TARGET) $(INSTALL_PATH)/bin/$(TARGET)
	@cp -r $(DOCDIR) $(INSTALL_PATH)/doc
	@$(RM) -rf $(INSTALL_PATH)/doc/Doxyfile $(INSTALL_PATH)/doc/*.tex $(INSTALL_PATH)/doc/*.fdb_latexmk 
	



plots: setup Rename $(BINDIR)/$(TARGET) 
	@$(ECHO) -n "Generating csv..."
	@python3 $(SCRIPTDIR)/g12_gen_csv.py
	@$(ECHO) -n "Done"	
	@python3 $(SCRIPTDIR)/g12_gen_plots.py
	@mv $(SRCDIR)/main.b $(SRCDIR)/main.c
	@mv $(SRCDIR)/main.cpp $(SRCDIR)/main.b
	@mv $(SRCDIR)/main.c $(SRCDIR)/main.cpp
			


Rename:
	@mv $(SRCDIR)/main.b $(SRCDIR)/main.c
	@mv $(SRCDIR)/main.cpp $(SRCDIR)/main.b
	@mv $(SRCDIR)/main.c $(SRCDIR)/main.cpp
	@$(RM) -rf $(BINDIR)/$(TARGET)
	@$(RM) -rf $(OBJDIR)/*.o








