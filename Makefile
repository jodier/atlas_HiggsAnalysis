#############################################################################

DIR=$(shell pwd)

#############################################################################

CINT          = rootcint
ROOTCONFIG    = root-config

#############################################################################

ROOTLIBS      = $(shell $(ROOTCONFIG) --libs)
ROOTGLIBS     = $(shell $(ROOTCONFIG) --glibs)
ROOTCFLAGS    = $(shell $(ROOTCONFIG) --cflags)
ROOTLDFLAGS   = $(shell $(ROOTCONFIG) --ldflags)

#############################################################################

ATLASFLAGS    = -DSTANDALONE \
-I./tools/PileupReweighting \
-I./tools/egammaAnalysisUtils \
-I./tools/MuonMomentumCorrections \
-I./tools/MuonEfficiencyCorrections \
-I./tools/TrigMuonEfficiency

#############################################################################

CXX           =g++
CXXFLAGS      =-std=c++98 -g -O2 -fPIC -ansi -Wall $(ROOTCFLAGS) $(ATLASFLAGS)

LD            =g++
LDFLAGS       =-g $(ROOTLDFLAGS) -L.

LIBS          = $(ROOTLIBS) -lTreePlayer
GLIBS         = $(ROOTGLIBS) -lTreePlayer

#############################################################################

OBJS1         = core/main.o core/core.o core/config.o core/loader.o core/utils.o

OBJS2         = analysis/higgs_analysis/main.o analysis/higgs_analysis/triggers.o analysis/higgs_analysis/utils.o analysis/higgs_analysis/isLoosePP.o analysis/higgs_analysis/Z_analysis.o analysis/higgs_analysis/H_analysis.o

OBJS3         = analysis/test/main.o

OBJS4         = analysis/z_studies/eff.o

OBJS5         = analysis/z_studies/mass.o

OBJS6         = analysis/z_studies/ZcandPeriod.o

OBJS7         = analysis/l_study/main.o analysis/higgs_analysis/triggers.o analysis/higgs_analysis/utils.o analysis/higgs_analysis/isLoosePP.o

#############################################################################

all: core $(OBJS2) $(OBJS3) $(OBJS4) $(OBJS5) $(OBJS6) $(OBJS7)
#	@cd $(DIR)/tools && make && cd $(DIR)

	$(LD) $(LDFLAGS) -o higgs_analysis $(OBJS2) $(LIBS) -L. -lcore -lPileupReweighting -legammaAnalysisUtils -lMuonMomentumCorrections -lMuonEfficiencyCorrections -lTrigMuonEfficiency
	$(LD) $(LDFLAGS) -o      test      $(OBJS3) $(LIBS) -L. -lcore -lPileupReweighting -legammaAnalysisUtils -lMuonMomentumCorrections -lMuonEfficiencyCorrections
	$(LD) $(LDFLAGS) -o       eff      $(OBJS4) $(LIBS) -L. -lRooFitCore -lRooFit -lPileupReweighting
	$(LD) $(LDFLAGS) -o      mass      $(OBJS5) $(LIBS) -L. -lPileupReweighting
	$(LD) $(LDFLAGS) -o   ZcandPeriod  $(OBJS6) $(LIBS) -L. -lPileupReweighting
	$(LD) $(LDFLAGS) -o     l_study    $(OBJS7) $(LIBS) -L. -lcore -lPileupReweighting -legammaAnalysisUtils -lMuonMomentumCorrections -lMuonEfficiencyCorrections -lTrigMuonEfficiency

#############################################################################

ALL: core $(OBJS2) $(OBJS3) $(OBJS4) $(OBJS5) $(OBJS6) $(OBJS7)
	@cd $(DIR)/tools && make all && cd $(DIR)

	$(LD) $(LDFLAGS) -o higgs_analysis $(OBJS2) $(LIBS) -L. -lcore -lPileupReweighting -legammaAnalysisUtils -lMuonMomentumCorrections -lMuonEfficiencyCorrections -lTrigMuonEfficiency
	$(LD) $(LDFLAGS) -o      test      $(OBJS3) $(LIBS) -L. -lcore -lPileupReweighting -legammaAnalysisUtils -lMuonMomentumCorrections -lMuonEfficiencyCorrections
	$(LD) $(LDFLAGS) -o       eff      $(OBJS4) $(LIBS) -L. -lRooFitCore -lRooFit -lPileupReweighting
	$(LD) $(LDFLAGS) -o      mass      $(OBJS5) $(LIBS) -L. -lPileupReweighting
	$(LD) $(LDFLAGS) -o   ZcandPeriod  $(OBJS6) $(LIBS) -L. -lPileupReweighting
	$(LD) $(LDFLAGS) -o     l_study    $(OBJS7) $(LIBS) -L. -lcore -lPileupReweighting -legammaAnalysisUtils -lMuonMomentumCorrections -lMuonEfficiencyCorrections -lTrigMuonEfficiency

#############################################################################

clean:
#	@cd $(DIR)/tools && make clean && cd $(DIR)

	rm -fr $(OBJS1) $(OBJS2) $(OBJS3) $(OBJS4) $(OBJS5) $(OBJS6) $(OBJS7) libcore.a higgs_analysis test eff mass ZcandPeriod l_study

#############################################################################

CLEAN:
	@cd $(DIR)/tools && make clean && cd $(DIR)

	rm -fr $(OBJS1) $(OBJS2) $(OBJS3) $(OBJS4) $(OBJS5) $(OBJS6) $(OBJS7) libcore.a higgs_analysis test eff mass ZcandPeriod l_study

#############################################################################

core: $(OBJS1)
	ar -rcs libcore.a $(OBJS1) && ranlib libcore.a

#############################################################################

%.o: %.C
	@printf "Building $@\n"
	@$(CXX) $(CXXFLAGS) -c -o $@ $<
	@printf "[ \033[32mOk.\033[0m ]\n"

%.o: %.cc
	@printf "Building $@\n"
	@$(CXX) $(CXXFLAGS) -c -o $@ $<
	@printf "[ \033[32mOk.\033[0m ]\n"

%.o: %.cxx
	@printf "Building $@\n"
	@$(CXX) $(CXXFLAGS) -c -o $@ $<
	@printf "[ \033[32mOk.\033[0m ]\n"

#############################################################################

