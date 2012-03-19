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

ATLASFLAGS    =\
-I ./egammaAnalysisUtils \
-I ./MuonEfficiencyCorrections \
-I ./MuonMomentumCorrections \
-I ./TrigMuonEfficiency \
-I ./PileupReweighting

CXX           =g++
CXXFLAGS      =-g -O2 -fPIC -ansi -Wall $(ROOTCFLAGS) $(ATLASFLAGS)

LD            =g++
LDFLAGS       =-g $(ROOTLDFLAGS) -L.

LIBS          = $(ROOTLIBS) -lTreePlayer
GLIBS         = $(ROOTGLIBS) -lTreePlayer

#############################################################################

OBJS1         =\
egammaAnalysisUtils/Root/CaloIsoCorrection.o \
egammaAnalysisUtils/Root/checkOQ.o \
egammaAnalysisUtils/Root/egammaSFclass.o \
egammaAnalysisUtils/Root/egammaTriggerMatching.o \
egammaAnalysisUtils/Root/EnergyRescaler.o \
egammaAnalysisUtils/Root/IsEMPlusPlusDefs.o

OBJS2         =\
MuonEfficiencyCorrections/Root/AnalysisMuonEfficiencyScaleFactors.o \
MuonEfficiencyCorrections/Root/EtaPhiBinning.o

OBJS3         =\
MuonMomentumCorrections/Root/SmearingClass.o

OBJS4         =\
TrigMuonEfficiency/Root/ElectronTriggerMatching.o \
TrigMuonEfficiency/Root/HSG3TrigLeptonSFTool.o \
TrigMuonEfficiency/Root/LeptonTriggerSF.o \
TrigMuonEfficiency/Root/MuonHypothesis.o \
TrigMuonEfficiency/Root/MuonTriggerMatching.o

OBJS5         =\
PileupReweighting/Root/TPileupReweighting.o

#############################################################################

all: $(OBJS1) $(OBJS2) $(OBJS3) $(OBJS4) $(OBJS5)
	$(AR) -rcs ../libegammaAnalysisUtils.a $(OBJS1)
	$(AR) -rcs ../libMuonMomentumCorrections.a $(OBJS2)
	$(AR) -rcs ../libMuonEfficiencyCorrections.a $(OBJS3)
	$(AR) -rcs ../libTrigMuonEfficiency.a $(OBJS4)
	$(AR) -rcs ../libPileupReweighting.a $(OBJS5)

#############################################################################

clean:
	rm -fr $(OBJS1) $(OBJS2) $(OBJS3) $(OBJS4) $(OBJS5) ../libegammaAnalysisUtils.a ../libMuonMomentumCorrections.a ../libMuonEfficiencyCorrections.a ../libPileupReweighting.a ../libPileupReweighting.a

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

